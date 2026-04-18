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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser.h>
#include <shell_defs.h>

/*
 * Gets the entire args of a command, expands the tilde (~), if and only if it's
 * the first character in an argument.
 */
char **expand_tilde(char **args)
{
	uint8_t i = 0;
	char *remainder;
	uint16_t dirsize;
	char *home = getenv("HOME");
	while (args[i]) {
		if (args[i][0] == '~' && home) {
			dirsize = strlen(home) + strlen(args[i]);
			remainder = malloc(dirsize);
			(void)snprintf(remainder, dirsize, "%s%s", home, args[i] + 1);
			free(args[i]);
			args[i] = remainder;
		}
		i++;
	}
	return args;
}

/*
 * Gets the character array, returns tokens.
 */
char **lexer(const char *line)
{
	char **tokens = malloc(ARGS_SIZE * sizeof(char *));
	char buf[1024];
	char c;
	uint64_t buf_idx = 0;
	uint64_t tok_idx = 0;
	uint64_t lin_idx = 0;

	while (line[lin_idx] != '\0') {
		c = line[lin_idx];
		/* whitespace */
		if (c == ' ' || c == '\t') {
			/* end of token, flush the buffer into the new token  */
			if (buf_idx > 0) {
				/* TODO
				 * Find a way to get the buffer flusher out of these blocks.
				 *
				 * WHY?
				 * Block repetition
				 *
				 * HOW?
				 * Function maybe?
				 */
				buf[buf_idx] = '\0';
				tokens[tok_idx] = strdup(buf);
				tok_idx++;
				buf_idx = 0;
			}
			lin_idx++;
		}
		/* special characters */
		else if (c == '|' || c == '>' || c == '<' || c == ';' || c == '&' ||
				 c == '\'' || c == '"') {
			/* TODO
			 * There has to be a better way to check whether c is a special
			 * character. Not sure how this can be generalized and taken out of
			 * this specific line, but we have to find it.
			 *
			 * WHY?
			 * We'll have to check for the exact same characters in the parser
			 * too. So, code repetition.
			 *
			 * HOW?
			 * Separate function, maybe? An enum doesn't work, because we need a
			 * specific set of integers, not any integer. What we need is a
			 * Python/Bash style associative array, or a function that checks
			 * for the specific characters we're looking for.
			 */
			if (buf_idx > 0) {
				/* flush buffer */
				buf[buf_idx] = '\0';
				tokens[tok_idx] = strdup(buf);
				tok_idx++;
				buf_idx = 0;
			}

			if (c == '>' && line[lin_idx + 1] == '>') {
				/* >> append mode path */
				tokens[tok_idx] = malloc(sizeof(">>"));
				strlcpy(tokens[tok_idx], ">>", 3 * sizeof(char));
				tok_idx++;
				/* skip the next character in line */
				lin_idx += 2;
			} else if (c == '&' && line[lin_idx + 1] == '&') {
				tokens[tok_idx] = malloc(sizeof("&&"));
				strlcpy(tokens[tok_idx], "&&", 3 * sizeof(char));
				tok_idx++;
				lin_idx += 2;
			} else if (c == '|' && line[lin_idx + 1] == '|') {
				tokens[tok_idx] = malloc(sizeof("||"));
				strlcpy(tokens[tok_idx], "||", 3 * sizeof(char));
				tok_idx++;
				lin_idx += 2;
			} else if (c == '\'') {
				uint64_t tracker = lin_idx;
				bool illegal_string = false;

				/* find the next ['] char */
				while (line[++tracker] != '\'' && line[tracker] != '\0')
					;
				if (line[tracker] == '\0')
					illegal_string = true;

				uint64_t str_len = tracker - lin_idx - 1; /* end quote */
				tracker = lin_idx + 1;
				tokens[tok_idx] = malloc((str_len + 1) * sizeof(char));

				uint64_t i = 0;
				while (i < str_len)
					tokens[tok_idx][i++] = line[tracker++];
				tokens[tok_idx++][i] = '\0';

				if (illegal_string)
					lin_idx += str_len + 1; /* only the starting quote */
				else
					lin_idx += str_len + 2; /* start and end quotes */
			} else if (c == '"') {
				uint64_t tracker = lin_idx;
				bool illegal_string = false;

				/* find the next ["] char */
				while (line[++tracker] != '"' && line[tracker] != '\0')
					;
				if (line[tracker] == '\0')
					illegal_string = true;

				uint64_t str_len = tracker - lin_idx - 1; /* end quote */
				tracker = lin_idx + 1;
				tokens[tok_idx] = malloc((str_len + 1) * sizeof(char));

				uint64_t i = 0;
				while (i < str_len)
					tokens[tok_idx][i++] = line[tracker++];
				tokens[tok_idx++][i] = '\0';

				if (illegal_string)
					lin_idx += str_len + 1; /* only the starting quote */
				else
					lin_idx += str_len + 2; /* start and end quotes */
			} else {
				/* output > and input < redirection path */
				tokens[tok_idx] = malloc(2);
				tokens[tok_idx][0] = c;
				tokens[tok_idx][1] = '\0';
				tok_idx++;
				lin_idx++;
			}
		} else {
			/* regular characters */
			buf[buf_idx] = c;
			buf_idx++;
			lin_idx++;
		}
	}

	/* last check to see if we have some unwritten characters in the buffer */
	if (buf_idx > 0) {
		buf[buf_idx] = '\0';
		tokens[tok_idx] = strdup(buf);
		tok_idx++;
	}

	/*
	 * Add a single NULL at the end of the array, because exec's require the
	 * last element in the array to be a NULL
	 */
	tokens = realloc(tokens, (tok_idx + 1) * sizeof(char *));
	tokens[tok_idx] = NULL;
	return tokens;
}

/*
 * ['bat', '-H', '/home/user/project/main.c', '|', 'grep', '-i' ,'printf']
 *
 * should turn into
 *
 * CMD first->append_mode = false
 *          ->file_in = NULL // it gets it from its argument
 *          ->file_out = fd[1]
 *          ->args = ['bat', '-H', 'home/user/project/main.c']
 *          ->type = CON_PIPE (enum CON, CON_PIPE = 1)
 *          ->next = second
 *
 * CMD second->append_mode = false
 *           ->file_in = fd[0]
 *           ->file_out = NULL // stdout
 *           ->args = ['grep', '-i', 'printf']
 *           ->type = CON_NONE (enum CON, CON_NONE = 0)
 *           ->next = NULL
 */

/*
 * Helper function that initializes a CMD struct for you to fill up.
 */
CMD *init_cmd(CMD *cmd)
{
	cmd->args = malloc(ARGS_SIZE * sizeof(char *));
	cmd->args[0] = NULL;
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	cmd->append_mode = false;
	cmd->type = OP_NONE;
	cmd->exit_status = 0;
	cmd->next = NULL;

	return cmd;
}
/*
 * Gets the tokens, returns the head of the linked list of commands.
 * Check include/parser.h enum CON and struct CMD
 */
CMD *parser(char **tokens)
{
	CMD *head = malloc(sizeof(CMD));
	CMD *curr = NULL;
	CMD *next = NULL;
	uint64_t arg_idx = 0;
	uint64_t i = 0;
	char c;

	init_cmd(head);
	curr = head;

	while (tokens[i]) {
		c = tokens[i][0];

		/* check for connector */
		if (c == '|' || c == ';') {
			next = malloc(sizeof(CMD));
			init_cmd(next);
			curr->next = next;
			curr->args[arg_idx] = NULL; /* end the command */

			if (c == '|') {
				if (tokens[i][1] == '|')
					curr->type = OP_OR;
				else
					curr->type = OP_PIPE;
			} else {
				curr->type = OP_SEQ;
			}

			i++;
			arg_idx = 0;
			curr = curr->next;
		}
		/* check for redir */
		else if (c == '>' || c == '<') {
			switch (c) {
			case '>':
				if (tokens[i][1] == '>')
					curr->append_mode = true;
				curr->file_out = strdup(tokens[++i]);
				i++;
				break;
			case '<':
				curr->file_in = strdup(tokens[++i]);
				i++;
				break;
			default:
				(void)fprintf(
					stderr,
					"[ERROR] Parser failed at 'check for redirection'.\n");
				exit(1);
			}
		} else if (c == '&' && tokens[i][1] == '&') {
			next = malloc(sizeof(CMD));
			init_cmd(next);
			curr->next = next;
			curr->args[arg_idx] = NULL;
			curr->type = OP_AND;

			i++;
			arg_idx = 0;
			curr = curr->next;
		} else {
			/* regular argument */
			curr->args[arg_idx++] = strdup(tokens[i++]);
		}
	}
	curr->args[arg_idx] = NULL;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return head;
}

/*
 * Free's the linked list.
 */
void free_cmds(CMD *head)
{
	uint64_t i;
	CMD *curr = head;
	CMD *next = NULL;

	while (curr) {
		i = 0;
		next = curr->next;

		while (curr->args[i])
			free(curr->args[i++]);
		free(curr->args);
		free(curr->file_in);
		free(curr->file_out);
		free(curr);

		curr = next;
	}
}
