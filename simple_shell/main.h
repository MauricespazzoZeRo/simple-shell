#ifndef MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdarg.h>

#define MAX_ARGS 50
#define MAX_ARG_LEN 100
#define MAX_CMD_LEN (MAX_ARGS * MAX_ARG_LEN)
#define BUFFER_SIZE 1024
#define MAX_ALIASES 100
#define MAX_ALIAS_LENGTH 100

struct Alias {
	char *name;
	char *value;
};

/* extern struct Alias aliases[MAX_ALIASES]; */

extern char **environ;


char* _getline(void);

int _strlen(char *s);

int _Strlen(const char *s);

int _strncmp(const char *s1, const char *s2, size_t n);

int _strcmp(const char *s1, const char *s2);

char *_strchr(char *s, char c);

char *_getenv(const char *name);

char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);

char *_Strcpy(char *dest, const char *src);

char *_strncpy(char *dest, char *src, int n);

void print_aliases();

void print_alias(char *alias_name);

void define_alias(char *alias_name, char *alias_value);

char *alias_cmd(const char *cmd, ...);

void exit_cmd(const char* cmd, ...);

char *env_cmd(const char* cmd);

int setenv_cmd(const char *cmd, ...);

int unsetenv_cmd(const char *cmd, ...);

int cd_cmd(const char* cmd, ...);

char *_strdup(char *str);

int _putenv(char *string);

char *_strstr(const char *haystack, const char *needle);

char *_memcpy(char *dest, char *src, unsigned int n);

int startsWith(const char *str, const char *prefix);

void intToString(int value, char *str, int size);

void handleVariableReplacement(char *command);

void *_memmove(void *dest, const void *src, size_t n);

size_t _strcspn(const char *str, const char *reject);

#endif /* MAIN_H */
