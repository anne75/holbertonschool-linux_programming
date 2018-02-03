#include "_getline.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


/**
 * read_file - possibly read a file, finds delimeters
 * @file: struct containing information about a file
 * Looks for delimeters in a buffer read from a file.
 * Return: number of chars read.
 */
int read_file(struct file_data *file)
{
	ssize_t r;
	size_t i;
	char *buffer;

	if (file->used == 0 || file->start >= file->used)
	{
		memset(file->buffer, 0, BUFSIZE);
		r = read(file->fd, file->buffer, BUFSIZE);
		if (r >= 0)
			file->used = r;
		else
			file->used = 0;
		file->start = 0;
		file->end = 0;
	}
	i = file->start;
	buffer = file->buffer;
	if (file->used > 0)
	{
		while (i < file->used &&
		       (buffer[i] != '\n' && buffer[i] != EOF))
			++i;
		if (buffer[i] == '\n' || buffer[i] == EOF)
		{
			file->end = i;
			file->delim = 1;
			/*end is actually the new line or EOF*/
		}
		else
		{
			file->end = file->used;
			file->delim = 0;
		}
	}
	return (r);
}

/**
 * fill_array - fill a resizing array
 * @arr: struct containing char *array to fill
 * @value: value to add
 * @size: size of value to insert
 * Return: 0 on success, 1 on failure
 */
int fill_array(struct resizing_string *arr, char *value, size_t size)
{
	int check;
	/* size_t i; */
	char *new_array;

	/* puts("fill_array"); */
	if (arr->size == 0)
	{
/*		puts("create new array");*/
		arr->array = malloc(BUFSIZE);
		if (!arr->array)
			return (1);
		arr->size = BUFSIZE;
		arr->used = 0;
		memset(arr->array, 0, arr->size);
	}

	check = 0;
	if ((arr->used >= arr->size) || size >= (arr->size - arr->used))
	{
		/* puts("resize array"); */
		new_array = malloc((2 * arr->size));
		if (!new_array)
		{
			free(arr->array);
			return (1);
		}
		memcpy(new_array, arr->array, arr->used);
		free(arr->array);
		arr->array = new_array;
		arr->size *= 2;
	}
	/* printf("copy array in fill_array: "); */
	memcpy(arr->array + arr->used, value, size);
	arr->used += size;
	return (check);
}

/**
 * free_files - free the files linked list
 * @files: head of linked list
 */
void free_files(struct file_data *files)
{
	struct file_data *tmp;

	while (files)
	{
		tmp = files;
		files = files->next;
		free(tmp);
	}
}

/**
 * get_fd - Given a file descriptor, find or create the matching struct
 * @files: head of files linked list
 * @fd: a file descriptor
 * Return: pointer to file
 */
struct file_data *get_fd(struct file_data **files, int fd)
{
	struct file_data *file_data, *tmp;

	if (!files)
		return (NULL);
	tmp = *files;
	if (*files)  /* look for fd in files */
	{
		while (tmp->next && tmp->fd != fd)
			tmp = tmp->next;
		if (tmp->fd == fd)
			return (tmp);
	}
	puts("new fd");
	/* first time or file not seen */
	file_data = malloc(sizeof(*file_data));
	if (!file_data)
	{
		free_files(*files);
		return (NULL);
	}
	file_data->fd = fd;
	file_data->used = 0;
	file_data->end = 0;
	file_data->start = 0;
	file_data->next = NULL;
	if (!*files)
		*files = file_data;
	else
		tmp->next = file_data;
	return (file_data);
}

/**
 * _getline - given a file descriptor returns a file line per line
 * @fd: file descriptor
 * Return: a line (to free by user)
 */
char *_getline(int fd)
{
	int check, r;
	static struct file_data *files; /* holds fd + buffer... */
	struct resizing_string line; /* output */
	struct file_data *file;

	memset((void *)&line, 0, sizeof(line)), check = 0;
	if (fd >= 0)
	{
		file = get_fd(&files, fd);
		r = read_file(file);
		if (!file->used)
			return (NULL);
		while (!file->delim && file->used)
		{
			check = fill_array(&line,
					   file->buffer + file->start,
					   file->end - file->start);
			if (check)
				break;
			file->start = file->end + 1;
			r = read_file(file);
		}
		if (!check && r > 0)
		{
			check = fill_array(&line,
					   file->buffer + file->start,
					   file->end - file->start);
		}
		file->delim = 0, file->start = file->end + 1;
		file->end = file->used;
	}
	if (fd == -1 || check || r < 0)
	{
		free_files(files), files = NULL;
		if (line.array)
			free(line.array);
		return (NULL);
	}
	line.size = 0, line.used = 0;
	return (line.array);
}
