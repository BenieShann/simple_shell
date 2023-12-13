#include "main.h"

/**
 * cd_b - changes the cwd.
 * @line:Char ptr that reps  directory path
 */

void cd_b(char *line)
{
	int index;
	const char *delim = "\n\t ":
	char **param_array;
	int token_count:

	token_count = 0;
	param_array = tokenize_interface(line, delim, token_count);

	if (param_array[0] == NULL)
	{
		free_resources(2, param_array, line);
		return;
	}
	if (param_array[1] == NULL)
	{
		index = find_path("HOME", "command_name");
		chdir((environ[index]) + 5);
	}
	else if (_strcmp(param_array[1], "-") == 0)
	{
		print_str(param_array[1], 0);
	} else
	{
		chdir(param_array[1]);
	}
	double_free(param_array);
}

/**
 * env_b - exit shell after releasing allocated resources
 * @line: a character pointer
 */

void env_b(__attribute__((unused))char *line)
{
	int k;
	int s;

	for (s = 0; environ[s] != NULL; s++)
	{
		for (k = 0; environ[s][k] != '\0'; k++)
			write(STDOUT_FILENO, &environ[s][k], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}
/**
 * exit_b - exits shell and frees allocated resources
 * @line: input str from the user
 */

void exit_b(char *line)
{
	free(line);
	printf("\n");
	exit(1);
}

/**
 * check_built_ins - de. appropriate function for execution
 * @str: name of function needed
 * Return: 0 if function is present, -1 otherwise
 */

void (*check_built_ins(char *str))(char *line)
{
	static struct
	{
		const char *name;
		void (*func)(char *line);
	}
	builtins[] = {
		{"exit", exit_b},
		{"env", env_b},
		{"cd", cd_b},
		{NULL, NULL}
	};

	int i;
	for (i = 0; builtins[i].name != NULL; i++)
	{
		if (strcmp(str, builtins[i].name) == 0)
		{
			return (builtins[i].func);
		}
	}
	return (NULL);
}

/**
 * built_in - determines if given command
 * is a built in function
 *
 * @command:array of arg passed to the shell
 * @line:input string from the user
 * Return: 0 if function is found, -1 otherwise
 */

int built_in(char **command, char *line)
{
	void (*func)(char *);

	func = check_built_ins(command[0]);
	if (func == NULL)
		return (-1);

	if (strcmp("exit", command[0]) == 0)
		double_free(command);

	func(line);
	return (0);
}
