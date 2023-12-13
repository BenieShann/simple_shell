#include "main.h"

/**
 * main - entry point.
 * @ac:no. of param passed.
 * @av:program
 *
 * Return: 0
*/

int main(__attribute__((unused)) int ac, char **av)
{
	char *line;
	size_t size;
	int command_counter;

	command_counter = 0;
	signal(SIGINT, SIG_IGN);
	do {
		command_counter++;
		line = NULL;
		size = 0;
		parse_line(line, size, command_counter, av);
	} while (1);
	return (0);
}
