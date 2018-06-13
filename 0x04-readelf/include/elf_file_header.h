#ifndef _READELF_HEADER_H_
#define _READELF_HEADER_H_

#include "elf.h"
#include <stdio.h>
#include <string.h>
#include "ar.h"      /*use for ARMAG*/
#include <stdint.h>  /*use for int_64t types*/
#include <stdlib.h>  /* abort */


/**
 * struct Elf_header - processor agnostic header (use 64 bits)
 * @e_ident: Magic number and other info
 * @e_type: Object file type
 * @e_machine: Architecture
 * @e_version: Object file version
 * @e_entry: Entry point virtual address
 * @e_phoff: Program header table file offset
 * @e_shoff: Section header table file offset
 * @e_flags: Processor-specific flags
 * @e_ehsize: ELF header size in bytes
 * @e_phentsize: Program header table entry size
 * @e_phnum: Program header table entry count
 * @e_shentsize: Section header table entry size
 * @e_shnum: Section header table entry count
 * @e_shstrndx: Section header string table index
 */
typedef struct Elf_header
{
	unsigned char e_ident[EI_NIDENT];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint64_t e_entry;
	uint64_t e_phoff;
	uint64_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} Elf_header;


/**
 * enum print_mode - how to print and unsigne long int
 * @HEX: hexadecimal
 * @DEC: decimal
 * @DEC_5: ?
 * @UNSIGNED: unsigned
 * @PREFIX_HEX: hexadecimal variant
 * @FULL_HEX: hexadecimal variant
 * @LONG_HEX: hexadecimal variant
 */
/* How to print a vma value.  */
typedef enum print_mode
{
	HEX,
	DEC,
	DEC_5,
	UNSIGNED,
	PREFIX_HEX,
	FULL_HEX,
	LONG_HEX
}
	print_mode;

typedef uint64_t elf_vma;

/* endianness_functions.c */
elf_vma(*byte_get)(elf_vma, int);
elf_vma byte_get_little_endian(elf_vma, int);
elf_vma byte_get_big_endian(elf_vma, int);
#define BYTE_GET(field) byte_get((field), sizeof(field))

/* header_helpers.c and *_2.c */
elf_vma byte_get_signed(const unsigned char *, int);
char *get_elf_class(unsigned int elf_class);
char *get_data_encoding(unsigned int encoding);
char *get_osabi_name(unsigned int osabi);
char *get_file_type(unsigned int e_type);
char *get_machine_name(unsigned int e_machine);
unsigned int print_vma(uint64_t vma, print_mode mode);
char *get_machine_flags(unsigned int e_flags, unsigned int e_machine);

/* read_elf_header.c */
int read_32_bit_header(FILE *file, Elf_header *ehdr);
int read_64_bit_header(FILE *file, Elf_header *ehdr);
int read_elf_header(FILE *file, Elf_header *ehdr);
void print_elf_header(Elf_header ehdr);
void print_elf_header_cont(Elf_header ehdr);

#endif
