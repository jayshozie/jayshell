/* Jayshell - A shell interpreter that no one should use in their right mind.
Copyright (C) 2025  Emir Baha Yıldırım

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

#include "execute.h"
#include "builtins.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int plumber(CMD *curr, int fd_in, int fd_out)
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
	if (curr->file_in != NULL) {
		if ((fd_in = open(curr->file_in, O_RDONLY)) == -1) {
			status = errno;
			fprintf(stderr,
				"[ERROR] Couldn't open file '%s'. errno: %d\n",
				curr->file_in, status);
			return status;
		} else {
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
	}
	/* output redirection */
	if (curr->file_out != NULL) {
		if (curr->append_mode) {
			flags = O_WRONLY | O_CREAT | O_APPEND;
		} else {
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		}

		fd_out = open(curr->file_out, flags, 0644);
		if (fd_out == -1) {
			status = errno;
			fprintf(stderr,
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

int __worker_builtin(builtin_func func, CMD *curr, int fd_in, int fd_out)
{
	int status = 0;
	int saved_stdout;
	int saved_stdin;

	/* save stdin and stdout */
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);

	if ((status = plumber(curr, fd_in, fd_out)) == 0) {
		status = func(curr);
	}

	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	return status;
}

pid_t __worker_extern(CMD *curr, int fd_in, int fd_out)
{
	int status = 0;
	pid_t pid = fork();
	if (pid == 0) {
		if ((status = plumber(curr, fd_in, fd_out)) != 0) {
			exit(status);
		}

		if (execvp(curr->args[0], curr->args) == -1) {
			status = errno;
			if (status == ENOENT) {
				fprintf(stderr,
					"[ERROR] Command '%s' not found. errno: %d\n",
					curr->args[0], status);
			}
			exit(status);
		}
	}
	return pid;
}

int exec_cmds(CMD *head)
{
	builtin_func builtin;
	int cmd_count = 0;
	int fork_count = 0;
	int status = 0;
	int fd_in = STDIN_FILENO;
	int next_fd_in = STDIN_FILENO;
	int fd_out = STDOUT_FILENO;
	CMD *curr = head;

	/* get the number of nodes in the linked list */
	while (curr != NULL) {
		cmd_count++;
		curr = curr->next;
	}

	/* use the number of nodes to malloc an array of pids */
	pid_t *pids = malloc(cmd_count * sizeof(pid_t));

	/* restart iterating over the list */
	curr = head;
	while (curr != NULL) {
		if (curr->args[0] == NULL) {
			break;
		}
		if (curr->type == PIPE) {
			int pipedes[2];
			if (pipe(pipedes) != 0) {
				status = errno;
				fprintf(stderr,
					"[ERROR] Couldn't create pipe. errno: %d\n",
					status);
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
			status = __worker_builtin(builtin, curr, fd_in, fd_out);
		} else {
			pids[fork_count++] =
				__worker_extern(curr, fd_in, fd_out);
		}

		if (fd_in != STDIN_FILENO) {
			close(fd_in);
		}
		if (fd_out != STDOUT_FILENO) {
			close(fd_out);
		}

		fd_in = next_fd_in;

		curr = curr->next;
	}

	int tmp = 0;
	for (int i = 0; i < fork_count; i++) {
		waitpid(pids[i], &tmp, 0);
		if (WIFEXITED(tmp)) {
			status = WEXITSTATUS(tmp);
		}
	}

	free(pids);

	return status;
}
