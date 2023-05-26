#include "main.h"

/* Function to check if a string starts with a specific prefix */
int startsWith(const char *str, const char *prefix)
{
    size_t lenStr = _Strlen(str);
    size_t lenPrefix = _Strlen(prefix);

    if (lenStr < lenPrefix)
	{
        return (0);
	}

    return (_strncmp(str, prefix, lenPrefix) == 0);
}

void intToString(int value, char *str, int size)
{
    int i = 0;
    int isNegative = 0;
	char temp;
	int length;
	int j;

    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    /* Convert each digit in reverse order */
    do
	{
        str[i++] = value % 10 + '0';
        value /= 10;
    }
	while (value > 0 && i < size - 1);

    /* Add the negative sign if necessary */
    if (isNegative)
	{
        str[i++] = '-';
	}

    /* Null-terminate the string */
    str[i] = '\0';

    /* Reverse the string */
    length = i;
    for (j = 0; j < length / 2; j++)
	{
        temp = str[j];
        str[j] = str[length - j - 1];
        str[length - j - 1] = temp;
    }
}


void handleVariableReplacement(char *command)
{
    char *var = command;
	int exit_status;
	char replacement[16];
	size_t var_length;
	size_t replacement_length;
	int pid;
	size_t var_length;
	size_t replacement_length;


    while ((var = strchr(var, '$')) != NULL)
	{
        if (startsWith(var, "$?"))
		{
            exit_status = WEXITSTATUS(system(NULL));
            intToString(exit_status, replacement, 16);

			var_length = _strcspn(var, " \t\n");
			replacement_length = _strlen(replacement);
			_memmove(var + replacement_length, var + var_length, _strlen(var + var_length) + 1);
			_memcpy(var, replacement, replacement_length);
		}
		else if (startsWith(var, "$$"))
		{
			pid = getpid();
			intToString(pid, replacement, 16);
			var_length = _strcspn(var, " \t\n");
			replacement_length = _strlen(replacement);

			_memmove(var + replacement_length, var + var_length, strlen(var + var_length) + 1);
			_memcpy(var, replacement, replacement_length);
		}
		else
		{
			var++;
		}
	}

}
