#include "main.h"

/**
 * str_len - Calculate the length of a string.
 * @str: String to find the length of.
 *
 * Return: Length of the string. 0 if string is NULL.
 */

int str_len(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (str[len] != '\0')
		len++;

	return (len);
}

/**
 * double_free -Release memory occupied.
 * @to_be_freed: Address of elements to be released
 *
*/

void double_free(char **to_be_freed)
{
	int index = 0;

	while (to_be_freed[index] != NULL)
	{
		free(to_be_freed[index]);
		index++;
	}

	free(to_be_freed);
}

/**
 * single_free - Free n number of str ptr
 * @n:No. of pointers to free.
 * @...: Variable no. of ptr to be released.
 */

void single_free(int n, ...)
{
	int i;
	char *str;
	va_list args;

	va_start(args, n);

	for (i = 0; i < n; i++)
	{
		str = va_arg(args, char *);

		if (str == NULL)
			str = "(nil)";

		free(str);
	}

	va_end(args);
}

/**
 * error_printing - Prints error message for command unavailble.
 * @av:Running the shell's name
 * @count:No. of commands run on shell.
 * @command: Command not found.
 */

void error_printing(char *av, int count, char *command)
{
	print_str(av, 1);
	print_str(": ", 1);
	print_number(count);
	print_str(": ", 1);
	print_str(command, 1);
}

/**
 * exec_error - Print exec errors.
 * @av: running shell's name
 * @count:No. of commands entered.
 * @tmp_command:Failed command
 *
*/

void exec_error(char *av, int count, char *tmp_command)
{
	error_printing(av, count, tmp_command);
	print_str(": ", 1);
	perror("");
	exit(1);
}

