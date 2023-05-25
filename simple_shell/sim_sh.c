#include "main.h"

extern char **environ;

/**
 * main - A simple shell that displays a prompt and waits for the user to
 *		  type a command.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line;
	char *args[MAX_ARGS];
	char *token;
	char *path;
	char *dir;
	/* pid_t child_pid; */
	/* int status; */
	size_t command_path_len;
	int c;
	char *command_path, command_len, dir_len;

	/* Retrieve the PATH variable from environ */
	path = _getenv("PATH");
	if (path == NULL)
	{
		perror("Failed to retrieve PATH");
		exit(EXIT_FAILURE);
	}

	while (1)
	{

		line = _getline();

		if (line == NULL)
		{
			break;
		}
		else if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		else
		{
			line[_strlen(line) - 1] = '\0';

			/* Tokenize the line to get individual args */
			token = strtok(line, " ");
			c = 0;
			while (token != NULL && c < MAX_ARGS - 1)
			{
				args[c] = token;
				token = strtok(NULL, " ");
				c++;
			}
			args[c] = NULL;

			/* Check for built-in commands */
			if (_strcmp(args[0], "exit") == 0)
			{
				exit_cmd("exit");
			}
			else if (_strcmp(args[0], "cd") == 0)
			{
				cd_cmd("cd");
			}
			else if (_strcmp(args[0], "env") == 0)
			{
				env_cmd("env");
			}
			else
			{
				/* Iterate over each dir in the PATH */
				dir = strtok(path, ":");
				while (dir != NULL)
				{
					/* Construct the full path of the command */
					dir_len = _strlen(dir);
					command_len = _strlen(args[0]);
					command_path_len = dir_len + command_len + 2;
					command_path = malloc(command_path_len);
					if (command_path == NULL)
					{
						perror("malloc");
						exit(EXIT_FAILURE);
					}
					_strcpy(command_path, dir);
					_strcat(command_path, "/");
					_strcat(command_path, args[0]);

					dir = strtok(NULL, ":");
				}

				if (dir == NULL)
				{
					write(1, "Command not found: ", 20);
					write(1, args[0], _strlen(args[0]));
					write(1, "\n", 1);
				}

				free(line);
				continue; /* Move the continue statement here */
			}

			free(line);
		}
	}

	return (0);
}
