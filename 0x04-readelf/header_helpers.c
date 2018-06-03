#include "elf_file_header.h"

/**
 * get_elf_class - get 32 or 64 bits processors
 * @elf_class: int holding enum value to discriminate the processors
 * Return: string holding statement
 */
char *get_elf_class(unsigned int elf_class)
{
	static char buff[32];

	switch (elf_class)
	{
	case ELFCLASSNONE: return ("none");
	case ELFCLASS32:   return ("ELF32");
	case ELFCLASS64:   return ("ELF64");
	default:
		snprintf(buff, sizeof(buff), "<unknown: %x>", elf_class);
		return (buff);
	}
}

/**
 * get_data_encoding - get endianess
 * @encoding: int containing enum value
 * Return: string holding statement
 */
char *get_data_encoding(unsigned int encoding)
{
	static char buff[32];

	switch (encoding)
	{
	case ELFDATANONE: return ("none");
	case ELFDATA2LSB: return ("2's complement, little endian");
	case ELFDATA2MSB: return ("2's complement, big endian");
	default:
		snprintf(buff, sizeof(buff), "<unknown: %x>", encoding);
		return (buff);
	}
}

/**
 * get_osabi_name - get OS ABI name
 * @osabi: number containing enum value
 * Return: string holding statement
 */
char *get_osabi_name(unsigned int osabi)
{
	static char buff[32];

	switch (osabi)
	{
	case ELFOSABI_NONE:return ("UNIX - System V");
	case ELFOSABI_HPUX:return ("UNIX - HP-UX");
	case ELFOSABI_NETBSD:return ("UNIX - NetBSD");
	case ELFOSABI_GNU:return ("UNIX - GNU");
	case ELFOSABI_SOLARIS:return ("UNIX - Solaris");
	case ELFOSABI_AIX:return ("UNIX - AIX");
	case ELFOSABI_IRIX:return ("UNIX - IRIX");
	case ELFOSABI_FREEBSD:return ("UNIX - FreeBSD");
	case ELFOSABI_TRU64:return ("UNIX - TRU64");
	case ELFOSABI_OPENBSD:return ("UNIX - OpenBSD");
	default:
		snprintf(buff, sizeof(buff), "<unknown: %x>", osabi);
		return (buff);
	}
}

/**
 * get_file_type - get type of elf file
 * @e_type: enum value
 * Return: string holding information
 */
char *get_file_type(unsigned int e_type)
{
	static char buff[32];

	switch (e_type)
	{
	case ET_NONE:return ("NONE (None)");
	case ET_REL:return ("REL (Relocatable file)");
	case ET_EXEC:return ("EXEC (Executable file)");
	case ET_DYN:return ("DYN (Shared object file)");
	case ET_CORE:return ("CORE (Core file)");
	default:
		if ((e_type >= ET_LOPROC) && (e_type <= ET_HIPROC))
			snprintf(buff, sizeof(buff), "Processor Specific: (%x)", e_type);
		else if ((e_type >= ET_LOOS) && (e_type <= ET_HIOS))
			snprintf(buff, sizeof(buff), "OS Specific: (%x)", e_type);
		else
			snprintf(buff, sizeof(buff), "<unknown>: %x", e_type);
		return (buff);
	}
}

/**
 * get_machine_name - get name of architecture
 * @e_machine: enum value
 * Return: string holding information
 */
char *get_machine_name(unsigned int e_machine)
{
	static char buff[64]; /* XXX */

	switch (e_machine)
	{
	case EM_NONE:return ("None");
	case EM_SPARC:return ("Sparc");
	case EM_386:return ("Intel 80386");
	case EM_860:return ("Intel 80860");
	case EM_SPARC32PLUS:return ("Sparc v8+");
	case EM_SPARCV9:return ("Sparc v9");
	case EM_X86_64:return ("Advanced Micro Devices X86-64");
	default:
		snprintf(buff, sizeof(buff), "<unknown>: 0x%x", e_machine);
		return (buff);
	}
}
