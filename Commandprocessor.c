#include "main.h"

/**
 * parse_line - Executes parsing of command line identity and arguments.
 * .
 * @line:Pointer to string initialized to NULL  upon function entry.
 * @size:Holder for no. of size_t,initialized to 0.
 * @command_counter:Counter tracking no. of commands in the shell.
 * @av: Running shell's name.
 *
*/

void parse_line(char *line, size_t size, int command_counter, char **av)
{
	int i;
	ssize_t read_len;
	int token_count;
	char **param_array;
	const char *delim = "\n\t ";

	token_count = 0;
	write(STDOUT_FILENO, PROMPT, str_len(PROMPT));
	read_len = getline(&line, &size, stdin);
	if (read_len != -1)
	{
		param_array = tokenize_interface(line, delim, token_count);
		if (param_array[0] == NULL)
		{
			free_resources(2, param_array, line);
			return;
		}
		i = built_in(param_array, line);
		if (i == -1)
			create_child_process(param_array, line, command_counter, av);
		for (i = 0; param_array[i] != NULL; i++)
			free(param_array[i]);
		free_resources(2, param_array, line);
	}
	else
		exit_b(line);
}

/**
 * create_child_process - Generates  a child process to
 * Execute another program.
 * @param_array: An array of string pointers that is NULL terminated.
 * @line:Contents of the input line.
 * @count:Counter tracking of no. of entered commands..
 * @av: Shell's parent program name.
*/

void create_child_process(char **param_array, char *line, int count, char **av)
{
	pid_t child_pid;
	int status;
	int i;
	int check;
	struct stat buf;
	char *tmp_command;
	char *command;

	child_pid = fork();
	if (child_pid == 0)
	{
		tmp_command = param_array[0];
		command = find_command_path(param_array[0]);
		if (command == NULL)
		{


			check = stat(tmp_command, &buf);
			if (check == -1)
			{
				error_printing(av[0], count, tmp_command);
				print_str(": not found", 0);
				free_resources(2, line, tmp_command);
				for (i = 1; param_array[i]; i++)
					free(param_array[i]);
				free(param_array);
				exit(100);
			}



			command = tmp_command;
		}
		param_array[0] = command;
		if (param_array[0] != NULL)
		{
			if (execve(param_array[0],
				param_array, environ) == -1)
				exec_error(av[0], count, tmp_command);
		}
	}
	else
		wait(&status);
}

/**
 * tokenize_interface - Facilitates  with other token
 * functions enhancing their accesibility.
 *
 * @line: Stores raw user input as a string.
 * @delim: Defines constant string containing
 * Delimiter used to tokenize input line
 * @token_count: Keeps track of no. of tokens in a string
 * Return: Stores an array of tokens representing the command
 *
*/

char **tokenize_interface(char *line, const char *delim, int token_count)
{
	char **param_array;

	token_count = count_token(line, delim);
	if (token_count == -1)
	{
		free(line);
		return (NULL);
	}
	param_array = tokenize(token_count, line, delim);
	if (param_array == NULL)
	{
		free(line);
		return (NULL);
	}
	return (param_array);
}

/**
 * tokenize -  Divides string into an array of tokens.
 *
 * @token_count:Integer representing no. of tokens in the array.
 * @line: String separated by a specified delim
 * @delim:Desired delimeter to separate tokens.
 * Return: A NULL terminated array of string pointer,otherwise returns NULL.
 *
*/

char **tokenize(int token_count, char *line, const char *delim)
{
	int i;
	char **buffer;
	char *token;
	char *line_cp;

	line_cp = _strdup(line);
	buffer = malloc(sizeof(char *) * (token_count + 1));
	if (buffer == NULL)
		return (NULL);
	token = strtok(line_cp, delim);
	for (i = 0; token != NULL; i++)
	{
		buffer[i] = _strdup(token);
		token = strtok(NULL, delim);
	}
	buffer[i] = NULL;
	free(line_cp);
	return (buffer);
}

/**
 * count_token - Enumerates tokens within given string.
 *
 * @line:String divided by specified delimeter
 * @delim:Desired delimeter token separation
 *
 * Return:Returns total count of tokens,otherwise -1.
 *
*/

int count_token(char *line, const char *delim)
{
	char *str;
	char *token;
	int i;

	str = _strdup(line);
	if (str == NULL)
		return (-1);
	token = strtok(str, delim);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, delim);
	free(str);
	return (i);
}
