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

typedef struct {
	char *name;
	char *value;
} Alias;

Alias aliases[MAX_ALIASES];

typedef char* (*CmdFunc)(const char* cmd, ...);


extern char **environ;


char* _getline(void);

int _strlen(char *s);

int _strncmp(const char *s1, const char *s2, size_t n);

int _strcmp(const char *s1, const char *s2);

char *_strchr(char *s, char c);

char *_getenv(const char *name);

char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);

char *_strncpy(char *dest, char *src, int n);

CmdFunc get_cmd(const char *cmd);

void print_aliases();

void print_alias(char *alias_name);

void define_alias(char *alias_name, char *alias_value);

char *alias_cmd(const char *cmd, ...);

void exit_cmd(const char* cmd, ...);

char *env_cmd(const char* cmd);

char *setenv_cmd(const char *cmd, ...);

char *unsetenv_cmd(const char *cmd, ...);

char *cd_cmd(const char* cmd, ...);

char *_strdup(char *str);

int _putenv(char *string);

#endif /* MAIN_H */
