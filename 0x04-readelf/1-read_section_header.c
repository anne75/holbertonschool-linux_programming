#include "readelf_header.h"


int main()
{
	Elf_header ehdr;
	Elf_Shdr section_headers;
	FILE file;

/* read header to get section header location */

	if (ac != 2)
	{
		printf("Usage: %s elf-filename\n", av[0]);
		return (EXIT_FAILURE);
	}


	file = fopen(av[1], "r");

	if (read_elf_header(file, &ehdr) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	is_32bit_elf = (ehdr.e_ident[EI_CLASS] != ELFCLASS64);


	fclose(file);

	return (EXIT_SUCCESS);
}
