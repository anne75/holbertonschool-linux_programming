#ifndef _GETLINE_H_
#define _GETLINE_H_

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_SIZE 8
#define EOF (-1)

/**
 * struct resizing_string - holds information about a file line
 * @array: string containing the characters
 * @used: number of elements used in the array
 * @size: size of array
 */
struct resizing_string
{
	char *array;
	size_t used;
	size_t size;
};

/**
 * struct file_data - details about a file being read
 * @fd: file descriptor
 * @delim: if a delimeter was found when reading the buffer
 * @buffer: buffer in which to read the file
 * @used: number of elements used in the buffer
 * @start: starting point for filling a line
 * @end: ending point to fill a line
 * @next: next element in linked list
 */
struct file_data
{
	int fd;
	int delim;
	char buffer[READ_SIZE];
	size_t used;
	size_t start;
	size_t end;
	struct file_data *next;
};


int read_file(struct file_data *file);
int fill_array(struct resizing_string *arr, char *value, size_t size);
void free_files(struct file_data *files);
struct file_data *get_fd(struct file_data **files, int fd);
char *_getline(int fd);

#endif
