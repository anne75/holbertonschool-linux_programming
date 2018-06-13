#include "elf_file_header.h"

/**
 * read_elf_header - read ELF header
 * @file: ELF file
 * @ehdr: struct to fill with header info
 * Figure out endianness and 32/64bits arch. Read accordingly
 * into a dedicated struct.
 * Return: SUCCESS or FAILURE
 */
int read_elf_header(FILE *file, Elf_header *ehdr)
{
	char is_32bit_elf;

	/* Read in the identity array.  */
	if (fread(ehdr->e_ident, EI_NIDENT, 1, file) != 1)
		return (EXIT_FAILURE);
/* Determine how to read the rest of the header.  */
	switch (ehdr->e_ident[EI_DATA])
	{
	default: /* fall through */
	case ELFDATANONE: /* fall through */
	case ELFDATA2LSB:
		byte_get = byte_get_little_endian;
		break;
	case ELFDATA2MSB:
		byte_get = byte_get_big_endian;
		break;
	}

/* For now we only support 32 bit and 64 bit ELF files.  */
	is_32bit_elf = (ehdr->e_ident[EI_CLASS] != ELFCLASS64);

	if (is_32bit_elf)
		read_32_bit_header(file, ehdr);
	else
		read_64_bit_header(file, ehdr);
	return (EXIT_SUCCESS);
}

/*
 * this function is split in 2 to respect style guidelines of function being
 * less than 40 lines long
 */

/**
 * print_elf_header - print elf header
 * @ehdr: dedicated struct containing header info
 */
void print_elf_header(Elf_header ehdr)
{
	int i;

	printf("ELF Header:\n"), printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%2.2x ", ehdr.e_ident[i]);
	printf("\n  Class:                             %s\n",
	       get_elf_class(ehdr.e_ident[EI_CLASS]));
	printf("  Data:                              %s\n",
		get_data_encoding(ehdr.e_ident[EI_DATA]));
	printf("  Version:                           %d %s\n",
	       ehdr.e_ident[EI_VERSION], (ehdr.e_ident[EI_VERSION] == EV_CURRENT
					  ? "(current)"
					  : (ehdr.e_ident[EI_VERSION] != EV_NONE
					     ? "<unknown: %lx>" : "")));
	printf("  OS/ABI:                            %s\n",
	       get_osabi_name(ehdr.e_ident[EI_OSABI]));
	printf("  ABI Version:                       %d\n",
	       ehdr.e_ident[EI_ABIVERSION]);
	printf("  Type:                              %s\n",
	       get_file_type(ehdr.e_type));
	printf("  Machine:                           %s\n",
	       get_machine_name(ehdr.e_machine));
	printf("  Version:                           0x%lx\n",
	       (unsigned long) ehdr.e_version);
	printf("  Entry point address:               ");
	print_vma((uint64_t) ehdr.e_entry, PREFIX_HEX), putchar('\n');
	printf("  Start of program headers:          ");
	print_vma((uint64_t) ehdr.e_phoff, DEC);
	printf(" (bytes into file)\n  Start of section headers:          ");
	print_vma((uint64_t) ehdr.e_shoff, DEC), printf(" (bytes into file)\n");

	print_elf_header_cont(ehdr);
}

/**
 * print_elf_header_cont - print elf header
 * @ehdr: dedicated struct containing header info
 */
void print_elf_header_cont(Elf_header ehdr)
{
	printf("  Flags:                             0x%lx%s\n",
	       (unsigned long) ehdr.e_flags,
	       get_machine_flags(ehdr.e_flags, ehdr.e_machine));
	printf("  Size of this header:               %ld (bytes)\n",
	       (long) ehdr.e_ehsize);
	printf("  Size of program headers:           %ld (bytes)\n",
	       (long) ehdr.e_phentsize);
	printf("  Number of program headers:         %ld\n",
	       (long) ehdr.e_phnum);
	printf("  Size of section headers:           %ld (bytes)\n",
	       (long) ehdr.e_shentsize);
	printf("  Number of section headers:         %ld\n",
	       (long) ehdr.e_shnum);
	printf("  Section header string table index: %ld\n",
	       (long) ehdr.e_shstrndx);
	if (ehdr.e_shstrndx != SHN_UNDEF && ehdr.e_shstrndx >= ehdr.e_shnum)
		printf(" <corrupt: out of range>\n");
}

/**
 * read_32_bit_header - read 32 bit header file.
 * @file: ELF file
 * @ehdr: elf header struct
 * BYTE_GET contains endianness information.
 * Return: 1 on failure, 0 on success.
 */
int read_32_bit_header(FILE *file, Elf_header *ehdr)
{

	Elf32_Ehdr ehdr32;

	if (fread(&ehdr32.e_type, sizeof(ehdr32) - EI_NIDENT, 1, file) != 1)
		return (1);
	ehdr->e_type      = BYTE_GET(ehdr32.e_type);
	ehdr->e_machine   = BYTE_GET(ehdr32.e_machine);
	ehdr->e_version   = BYTE_GET(ehdr32.e_version);
	ehdr->e_entry     = BYTE_GET(ehdr32.e_entry);
	ehdr->e_phoff     = BYTE_GET(ehdr32.e_phoff);
	ehdr->e_shoff     = BYTE_GET(ehdr32.e_shoff);
	ehdr->e_flags     = BYTE_GET(ehdr32.e_flags);
	ehdr->e_ehsize    = BYTE_GET(ehdr32.e_ehsize);
	ehdr->e_phentsize = BYTE_GET(ehdr32.e_phentsize);
	ehdr->e_phnum     = BYTE_GET(ehdr32.e_phnum);
	ehdr->e_shentsize = BYTE_GET(ehdr32.e_shentsize);
	ehdr->e_shnum     = BYTE_GET(ehdr32.e_shnum);
	ehdr->e_shstrndx  = BYTE_GET(ehdr32.e_shstrndx);
	return (0);
}

/**
 * read_64_bit_header - read 64 bit header file
 * @file: ELF file
 * @ehdr: elf header struct
 * Return: 1 on failure, 0 on success.
 */
int read_64_bit_header(FILE *file, Elf_header *ehdr)
{
	Elf64_Ehdr ehdr64;

	if (fread(&ehdr64.e_type, sizeof(ehdr64) - EI_NIDENT, 1, file) != 1)
		return (1);
	ehdr->e_type      = BYTE_GET(ehdr64.e_type);
	ehdr->e_machine   = BYTE_GET(ehdr64.e_machine);
	ehdr->e_version   = BYTE_GET(ehdr64.e_version);
	ehdr->e_entry     = BYTE_GET(ehdr64.e_entry);
	ehdr->e_phoff     = BYTE_GET(ehdr64.e_phoff);
	ehdr->e_shoff     = BYTE_GET(ehdr64.e_shoff);
	ehdr->e_flags     = BYTE_GET(ehdr64.e_flags);
	ehdr->e_ehsize    = BYTE_GET(ehdr64.e_ehsize);
	ehdr->e_phentsize = BYTE_GET(ehdr64.e_phentsize);
	ehdr->e_phnum     = BYTE_GET(ehdr64.e_phnum);
	ehdr->e_shentsize = BYTE_GET(ehdr64.e_shentsize);
	ehdr->e_shnum     = BYTE_GET(ehdr64.e_shnum);
	ehdr->e_shstrndx  = BYTE_GET(ehdr64.e_shstrndx);
	return (0);
}
