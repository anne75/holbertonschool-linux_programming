#include "elf_file_header.h"


/**
 * main - entrypoint to read elf header
 * @ac: number of command line args
 * @av: array of command line args
 * Return: suxxess or failure.
 */
int main(int ac, char **av)
{
	Elf_header ehdr;
	FILE *file;

	if (ac != 2)
	{
		printf("Usage: %s elf-filename\n", av[0]);
		return (EXIT_FAILURE);
	}


	file = fopen(av[1], "r");

	if (read_elf_header(file, &ehdr) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	fclose(file);
	print_elf_header(ehdr);

	return (EXIT_SUCCESS);
}
