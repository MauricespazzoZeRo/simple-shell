#include "main.h"

int main()
{
	char *line;

	printf("Enter some text:\n");
	while ((line = _getline()) != NULL)
	{
		printf("s@h$> %s\n", line);
		free(line);
	}
	return (0);
}
