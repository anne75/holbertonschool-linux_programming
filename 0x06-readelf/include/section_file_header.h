#ifndef _READELF_SECTION_HEADER_H_
#define _READELF_SECTION_HEADER_H_

#include "elf.h"
#include <stdio.h>
#include <string.h>
#include "ar.h"      /*use for ARMAG*/
#include <stdint.h>  /*use for int_64t types*/
#include <stdlib.h>  /* abort */

/* Section header */

typedef struct {
	unsigned charsh_name[4];/* Section name, index in string tbl */
	unsigned charsh_type[4];/* Type of section */
	unsigned charsh_flags[4];/* Miscellaneous section attributes */
	unsigned charsh_addr[4];/* Section virtual addr at execution */
	unsigned charsh_offset[4];/* Section file offset */
	unsigned charsh_size[4];/* Size of section in bytes */
	unsigned charsh_link[4];/* Index of another section */
	unsigned charsh_info[4];/* Additional section information */
	unsigned charsh_addralign[4];/* Section alignment */
	unsigned charsh_entsize[4];/* Entry size if section holds table */
} Elf32_External_Shdr;

typedef struct {
	unsigned charsh_name[4];/* Section name, index in string tbl */
	unsigned charsh_type[4];/* Type of section */
	unsigned charsh_flags[8];/* Miscellaneous section attributes */
	unsigned charsh_addr[8];/* Section virtual addr at execution */
	unsigned charsh_offset[8];/* Section file offset */
	unsigned charsh_size[8];/* Size of section in bytes */
	unsigned charsh_link[4];/* Index of another section */
	unsigned charsh_info[4];/* Additional section information */
	unsigned charsh_addralign[8];/* Section alignment */
	unsigned charsh_entsize[8];/* Entry size if section holds table */
} Elf64_External_Shdr;

typedef struct
{
	unsigned int sh_name;/* Section name, index in string tbl */
	unsigned int sh_type;/* Type of section */
	uint64_t sh_flags;/* Miscellaneous section attributes */
	uint64_t sh_addr;/* Section virtual addr at execution */
	file_ptr sh_offset;/* Section file offset */
	uint64_t sh_size;/* Size of section in bytes */
	unsigned int sh_link;/* Index of another section */
	unsigned int sh_info;/* Additional section information */
	uint64_t sh_addralign;/* Section alignment */
	uint64_t sh_entsize;/* Entry size if section holds table */

	/* The internal rep also has some cached info associated with it. */
	asection *bfd_section;/* Associated BFD section.  */
	unsigned char *contents;/* Section contents.  */
} Elf_Shdr;


typedef uint64_t elf_vma;

#endif
