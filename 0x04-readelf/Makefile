
# compiler
CC=gcc-4.8

# header files
INCLUDE=include

# flags
CFLAGS = -Wall -Werror -Wextra

# do not mistake rule for files
.PHONY: 0-hreadelf

0-hreadelf:
	$(CC) -I $(INCLUDE) $(CFLAGS) 0-hreadelf.c read_file_header.c header_helpers.c endianess_functions.c -o 0-hreadelf
