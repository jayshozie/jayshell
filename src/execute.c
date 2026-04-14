/* Jayshell - A shell interpreter that no one should use in their right mind.
Copyright (C) 2025, 2026  Emir Baha Yıldırım

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <execute.h>
#include <builtins.h>

static inline int plumber(CMD *curr, int fd_in, int fd_out)
{
	int status = 0;
	int flags = 0;

	/* pipe checks */
	if (fd_in != STDIN_FILENO) {
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO) {
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}

	/* input redirection */
	if (curr->file_in) {
		if ((fd_in = open(curr->file_in, O_RDONLY)) == -1) {
			status = errno;
			(void)fprintf(stderr,
						  "[ERROR] Couldn't open file '%s'. errno: %d\n",
						  curr->file_in, status);
			return status;
		} else {
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
	}
	/* output redirection */
	if (curr->file_out) {
		if (curr->append_mode)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;

		fd_out = open(curr->file_out, flags, 0644);
		if (fd_out == -1) {
			status = errno;
			(void)fprintf(stderr,
						  "[ERROR] Couldn't open file '%s'. errno: %d\n",
						  curr->file_out, status);
			return status;
		} else {
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
	}

	return status;
}

static inline int __worker_builtin(builtin_func func, CMD *curr, int fd_in,
								   int fd_out)
{
	int status = 0;
	int saved_stdout;
	int saved_stdin;

	/* save stdin and stdout */
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);

	if ((status = plumber(curr, fd_in, fd_out)) == 0)
		status = func(curr);

	if (saved_stdin >= 0) {
		dup2(saved_stdin, STDIN_FILENO);
	}
	close(saved_stdin);
	if (saved_stdout >= 0) {
		dup2(saved_stdout, STDOUT_FILENO);
	}
	close(saved_stdout);

	return status;
}

static inline pid_t __worker_extern(CMD *curr, int fd_in, int fd_out)
{
	int status = 0;
	pid_t pid = fork();
	if (pid == 0) {
		if ((status = plumber(curr, fd_in, fd_out)) != 0)
			exit(status);

		if (execvp(curr->args[0], curr->args) == -1) {
			status = errno;
			if (status == ENOENT) {
				(void)fprintf(stderr,
							  "[ERROR] Command '%s' not found. errno: %d\n",
							  curr->args[0], status);
			}
			exit(status);
		}
	}
	return pid;
}

static inline bool should_skip(CMD *prev, int prev_exit_status)
{
	if (prev) {
		CON t = prev->type;
		if ((t == OP_AND && prev_exit_status != 0) ||
			(t == OP_OR && prev_exit_status == 0))
			return true;
		else
			return false;
	} else {
		return false;
	}
}

int exec_cmds(CMD *head)
{
	builtin_func builtin;
	pid_t *pids = NULL;
	int cmd_count = 0, fork_count = 0, exit_status = 0;
	int fd_in = STDIN_FILENO;
	int next_fd_in = STDIN_FILENO;
	int fd_out = STDOUT_FILENO;
	CMD *curr = head, *prev = NULL;

	/* get the number of nodes in the linked list */
	while (curr) {
		cmd_count++;
		curr = curr->next;
	}

	/* use the number of nodes to malloc an array of pids */
	if ((cmd_count * sizeof(pid_t)) > 0)
		pids = malloc(cmd_count * sizeof(pid_t));

	/* restart iterating over the list */
	curr = head;
	while (curr) {
		if (should_skip(prev, exit_status)) {
			/* skip */
			prev = curr;
			curr = curr->next;
			continue;
		}
		if (!curr->args[0]) {
			break;
		}
		if (curr->type == OP_PIPE) {
			int pipedes[2];
			if (pipe(pipedes) != 0) {
				exit_status = errno;
				(void)fprintf(stderr,
							  "[ERROR] Couldn't create pipe. errno: %d\n",
							  exit_status);
				break;
			}
			fd_out = pipedes[1];
			next_fd_in = pipedes[0];
		} else {
			fd_out = STDOUT_FILENO;
			next_fd_in = STDIN_FILENO;
		}

		builtin = get_builtin(curr->args[0]);
		if (builtin) {
			if (!prev || prev->type != OP_PIPE) {
				exit_status = __worker_builtin(builtin, curr, fd_in, fd_out);
			} else {
				int status = 0;
				pid_t pid = fork();
				if (pid == 0) {
					status = plumber(curr, fd_in, fd_out);
					if (status != 0)
						exit(status);
					status = __worker_builtin(builtin, curr, fd_in, fd_out);
					exit(status);
				}
				exit_status = status;
			}
		} else {
			pids[fork_count++] = __worker_extern(curr, fd_in, fd_out);
		}

		if (curr->type != OP_PIPE) {
			int tmp = 0;
			for (int i = 0; i < fork_count; i++) {
				waitpid(pids[i], &tmp, 0);
				if (WIFEXITED(tmp)) {
					curr->exit_status = WEXITSTATUS(tmp);
					exit_status = curr->exit_status;
				}
			}
			fork_count = 0;
		}

		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);

		fd_in = next_fd_in;

		prev = curr;
		curr = curr->next;
	}

	if (pids)
		free(pids);
	return exit_status;
}
