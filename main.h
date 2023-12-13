#ifndef main_h
#define main_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>

#define PROMPT "simple_shell $ "


/**
 * struct builtin_d - defines builtins functions
 * @built: Name of build in command
 * @f: Pointer to the right builtin function
 *
*/

typedef struct builtin_d
{
	char *built;
	void (*f)(char *);
} builtin_t;

extern char **environ;

int str_len(char *);
int count_token(char *, const char *);
char **tokenize(int, char *, const char *);
char **tokenize_interface(char *, const char *, int);
void create_child_process(char **, char *, int, char **);
void parse_line(char *, size_t, int, char **);
void double_free(char **);
char *find_command_path(char *);
char *find_command_path(char *command);
char *find_path(char *env_var, char *command);
char *search_directories(char **, char *);
char *build_path(char *, char *);
void free_resources(int, ...);

char **tokenize_path(char *env_var);
char *search_directories(char **path_tokens, char *command);
char *build_path(char *directory, char *command);

/*BUILTIN FUNCTIONS*/

int built_in(char **, char *);
void exit_b(char *);
void env_b(char *);
void cd_b(char *);
void (*check_built_ins(char *))(char *);

int _strcmp(char *, char *);
char *_strdup(char *);
int print_number(int);
int _write_char(char);
void print_str(char *, int);

void exec_error(char *, int, char *);
void error_printing(char *, int, char *);

#endif
