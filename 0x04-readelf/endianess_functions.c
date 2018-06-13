#include "elf_file_header.h"


/**
 * byte_get_little_endian - extract info stored in little endian
 * @ffield: data to read.
 * @size: extend of information to extract.
 * Return: unsigned 64bit int
 */
elf_vma byte_get_little_endian(elf_vma ffield, int size)
{
	unsigned char *field;

	field = (unsigned char *) &ffield;
	switch (size)
	{
	case 1:
		return ((elf_vma) *field);
	case 2:
		return  ((unsigned int) (field[0]))
			|    (((unsigned int) (field[1])) << 8);
	case 3:
		return  ((unsigned long) (field[0]))
			|    (((unsigned long) (field[1])) << 8)
			|    (((unsigned long) (field[2])) << 16);
	case 4:
		return  ((elf_vma) (field[0]))
			|    (((elf_vma) (field[1])) << 8)
			|    (((elf_vma) (field[2])) << 16)
			|    (((elf_vma) (field[3])) << 24);
	case 5:
		return  ((elf_vma) (field[0]))
			|    (((elf_vma) (field[1])) << 8)
			|    (((elf_vma) (field[2])) << 16)
			|    (((elf_vma) (field[3])) << 24)
			|    (((elf_vma) (field[4])) << 32);
	case 6:
		return  ((elf_vma) (field[0]))
			|    (((elf_vma) (field[1])) << 8)
			|    (((elf_vma) (field[2])) << 16)
			|    (((elf_vma) (field[3])) << 24)
			|    (((elf_vma) (field[4])) << 32)
			|    (((elf_vma) (field[5])) << 40);
	case 7:
		return  ((elf_vma) (field[0]))
			|    (((elf_vma) (field[1])) << 8)
			|    (((elf_vma) (field[2])) << 16)
			|    (((elf_vma) (field[3])) << 24)
			|    (((elf_vma) (field[4])) << 32)
			|    (((elf_vma) (field[5])) << 40)
			|    (((elf_vma) (field[6])) << 48);
	case 8:
		return  ((elf_vma) (field[0]))
			|    (((elf_vma) (field[1])) << 8)
			|    (((elf_vma) (field[2])) << 16)
			|    (((elf_vma) (field[3])) << 24)
			|    (((elf_vma) (field[4])) << 32)
			|    (((elf_vma) (field[5])) << 40)
			|    (((elf_vma) (field[6])) << 48)
			|    (((elf_vma) (field[7])) << 56);
	default:
		printf("Unhandled data length: %d\n", size);
		abort();
	}
}

/**
 * byte_get_big_endian - extract info stored in big endian
 * @ffield: data to read.
 * @size: extend of information to extract.
 * Return: unsigned 64bit int
 */
elf_vma byte_get_big_endian(elf_vma ffield, int size)
{
	unsigned char *field;

	field = (unsigned char *) &ffield;
	switch (size)
	{
	case 1:
		return (*field);
	case 2:
		return (((unsigned int) (field[1])) | (((int) (field[0])) << 8));
	case 3:
		return ((unsigned long) (field[2]))
			|   (((unsigned long) (field[1])) << 8)
			|   (((unsigned long) (field[0])) << 16);
	case 4:
		return ((unsigned long) (field[3]))
			|   (((unsigned long) (field[2])) << 8)
			|   (((unsigned long) (field[1])) << 16)
			|   (((unsigned long) (field[0])) << 24);
	case 5:
		return ((elf_vma) (field[4]))
			|   (((elf_vma) (field[3])) << 8)
			|   (((elf_vma) (field[2])) << 16)
			|   (((elf_vma) (field[1])) << 24)
			|   (((elf_vma) (field[0])) << 32);
	case 6:
		return ((elf_vma) (field[5]))
			|   (((elf_vma) (field[4])) << 8)
			|   (((elf_vma) (field[3])) << 16)
			|   (((elf_vma) (field[2])) << 24)
			|   (((elf_vma) (field[1])) << 32)
			|   (((elf_vma) (field[0])) << 40);
	case 7:
		return ((elf_vma) (field[6]))
			|   (((elf_vma) (field[5])) << 8)
			|   (((elf_vma) (field[4])) << 16)
			|   (((elf_vma) (field[3])) << 24)
			|   (((elf_vma) (field[2])) << 32)
			|   (((elf_vma) (field[1])) << 40)
			|   (((elf_vma) (field[0])) << 48);
	case 8:
		return ((elf_vma) (field[7]))
			|   (((elf_vma) (field[6])) << 8)
			|   (((elf_vma) (field[5])) << 16)
			|   (((elf_vma) (field[4])) << 24)
			|   (((elf_vma) (field[3])) << 32)
			|   (((elf_vma) (field[2])) << 40)
			|   (((elf_vma) (field[1])) << 48)
			|   (((elf_vma) (field[0])) << 56);
	default:
		printf("Unhandled data length: %i\n", size);
		abort();
	}
}
