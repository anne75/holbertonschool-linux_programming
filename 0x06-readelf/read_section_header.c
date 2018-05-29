#include "readelf_header.h"
/* need to add elf header, figure our what error and warn add to line*/
#define FALSE 0
#define TRUE 1

char get_64bit_section_headers(FILE * file, char probe, Elf_header *elf_header)
{
	Elf64_External_Shdr * shdrs;
	Elf_Shdr *   internal;
	unsigned int i;
	unsigned int size = elf_header->e_shentsize;
	unsigned int num = probe ? 1 : elf_header->e_shnum;
	/* PR binutils/17531: Cope with unexpected section header sizes.  */
	if (size == 0 || num == 0)
		return (FALSE);
	if (size < sizeof(* shdrs))
	{
		if (! probe)
			fprint(stderr, "The e_shentsize field in the ELF header is less than the size of an ELF section header\n");
		return (FALSE);
	}
	if (! probe && size > sizeof(* shdrs))
		warn (_("The e_shentsize field in the ELF header is larger than the size of an ELF section header\n"));
	shdrs = (Elf64_External_Shdr *) get_data(NULL, file, elf_header.e_shoff,
						  size, num,
						  probe ? NULL : "section headers");
	if (shdrs == NULL)
		return (FALSE);
	if (section_headers != NULL)
		free(section_headers);
	section_headers = (Elf_Internal_Shdr *) cmalloc(num,
							sizeof(Elf_Internal_Shdr));
	if (section_headers == NULL)
	{
		if (! probe)
			fprintf(stderr, "Out of memory reading %u section headers\n", num);
		return FALSE;
	}
	for (i = 0, internal = section_headers;
	     i < num;
	     i++, internal++)
	{
		internal->sh_name      = BYTE_GET (shdrs[i].sh_name);
		internal->sh_type      = BYTE_GET (shdrs[i].sh_type);
		internal->sh_flags     = BYTE_GET (shdrs[i].sh_flags);
		internal->sh_addr      = BYTE_GET (shdrs[i].sh_addr);
		internal->sh_size      = BYTE_GET (shdrs[i].sh_size);
		internal->sh_entsize   = BYTE_GET (shdrs[i].sh_entsize);
		internal->sh_link      = BYTE_GET (shdrs[i].sh_link);
		internal->sh_info      = BYTE_GET (shdrs[i].sh_info);
		internal->sh_offset    = BYTE_GET (shdrs[i].sh_offset);
		internal->sh_addralign = BYTE_GET (shdrs[i].sh_addralign);
	}
	free(shdrs);
	return (TRUE);
}


char get_32bit_section_headers (FILE * file, char probe, Elf_header *elf_header)
{
	Elf32_External_Shdr * shdrs;
	Elf_Internal_Shdr *   internal;
	unsigned int i;
	unsigned int size = elf_header->e_shentsize;
	unsigned int num = probe ? 1 : elf_header->e_shnum;
	/* PR binutils/17531: Cope with unexpected section header sizes.  */
	if (size == 0 || num == 0)
		return (FALSE);
	if (size < sizeof * shdrs)
	{
		if (! probe)
			error (_("The e_shentsize field in the ELF header is less than the size of an ELF section header\n"));
		return FALSE;
	}
	if (!probe && size > sizeof * shdrs)
		warn (_("The e_shentsize field in the ELF header is larger than the size of an ELF section header\n"));
	shdrs = (Elf32_External_Shdr *) get_data(NULL, file, elf_header->e_shoff,
						  size, num,
						  probe ? NULL : "section headers");
	if (shdrs == NULL)
		return (FALSE);
	if (section_headers != NULL)
		free(section_headers);
	section_headers = (Elf_Internal_Shdr *) cmalloc(num,
							sizeof (Elf_Internal_Shdr));
	if (section_headers == NULL)
	{
		if (!probe)
			error (_("Out of memory reading %u section headers\n"), num);
		return FALSE;
	}
	for (i = 0, internal = section_headers;
	     i < num;
	     i++, internal++)
	{
		internal->sh_name      = BYTE_GET (shdrs[i].sh_name);
		internal->sh_type      = BYTE_GET (shdrs[i].sh_type);
		internal->sh_flags     = BYTE_GET (shdrs[i].sh_flags);
		internal->sh_addr      = BYTE_GET (shdrs[i].sh_addr);
		internal->sh_offset    = BYTE_GET (shdrs[i].sh_offset);
		internal->sh_size      = BYTE_GET (shdrs[i].sh_size);
		internal->sh_link      = BYTE_GET (shdrs[i].sh_link);
		internal->sh_info      = BYTE_GET (shdrs[i].sh_info);
		internal->sh_addralign = BYTE_GET (shdrs[i].sh_addralign);
		internal->sh_entsize   = BYTE_GET (shdrs[i].sh_entsize);
	}
	free(shdrs);
	return TRUE;
}
