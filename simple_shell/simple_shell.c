#include "main.h"

/**
 * my_shell - A simple shell that displays a prompt and waits for the user to
 *			  type a command.
 *
 *
 *
 *
 */

int main()
{
	char* get_line;
	char *line = NULL;
	char* args[MAX_ARGS];
	pid_t child_pid;
	int status;
	char* token;
	int c;
	char* path; /* Handle path */
	char* dir;

	/* Retrieve the PARH variable from environ */
	path = _getenv("PATH");
	if (path == NULL)
	{
		perror("Failed to receive PATH");
		exit(EXIT_FAILURE);
	}

	for ( ; ; ) /* Infinte for loop to continually display prompt */
	{
		write(1, "simple_shell ", 13);
		fflush(stdout);

		get_line = _getline();

		if (get_line == NULL) /* Encounters EOF */
		{
			break;
		}
		else if (get_line[0] == '\0') /* Encounters empty line */
		{
			free(get_line);
			continue;
		}
		else
		{
			line = get_line;

			line[_strlen(line)-1] = '\0'; /* remove the newline character */

			/* Tokenize the line to get individual args */
			token = strtok(line, " ");
			c = 0;
			while (token != NULL && i < MAX_ARGS)
			{
				args[c] = token;
				token = strtok(NULL, " ");
				c++;
			}
			/* Set the last element to NULL to terminate the args list */
			args[c] = NULL;

			/* Iterate over each dir in the PATH */
			dir = strtok(path, "/");

			child_pid = fork();
			if (child_pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}

			else if (child_pid == 0) /* Child process */
			{
				execve(args[0], args, NULL);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else /* parent process */
			{
				wait(&status); /* wait for child process to terminate */
			}

			free(get_line);
		}
	}

	free(line);
	return (0);
}
