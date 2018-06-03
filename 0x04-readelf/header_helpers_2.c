#include "elf_file_header.h"

/* 2nd part of header helpers, divided for style requirements */

/**
 * print_vma - print an unsigned long int according to some format
 * @vma: unsigned long int
 * @mode: enum value, format to use
 * Return: same as printf, number of bytes written on success
 */
unsigned int print_vma(uint64_t vma, print_mode mode)
{
	unsigned int nc = 0;

	switch (mode)
	{
	case FULL_HEX:
		nc = printf("0x");
		/* Fall through.  */
	case LONG_HEX:
		printf("%08lx", vma);
		return (nc + 16);

	case DEC_5:
		if (vma <= 99999)
			return (printf("%5ld", vma));
		/* Fall through.  */
	case PREFIX_HEX:
		nc = printf("0x");
		/* Fall through.  */
	case HEX:
		return (nc + printf("%lx", vma));

	case DEC:
		return (printf("%ld", vma));

	case UNSIGNED:
		return (printf("%lu", vma));

	default:
		/* FIXME: Report unrecognised mode ?  */
		return (0);
	}
}

/**
 * get_machine_flags - not doing much
 * @e_flags: flag
 * @e_machine: machine number, unused
 * Return: string holding information
 */
char *get_machine_flags(unsigned int e_flags, unsigned int e_machine)
{
	static char buf[1024];

	(void) e_machine;

	buf[0] = '\0';

	if (e_flags)
	{
		strcat(buf, "e_flags non zero");
	}
	return (buf);
}
