#include "_getline.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


/**
 * read_file - possibly read a file, finds delimeters
 * @file: struct containing information about a file
 * Looks for delimeters in a buffer read from a file.
 * Return: number of chars to use.
 */
int read_file(struct file_data *file)
{
	ssize_t r;
	size_t i;
	char *buffer;

	r = 0;
	if (file->used == 0 || file->start >= file->used)
	{
		memset(file->buffer, 0, READ_SIZE);
		r = read(file->fd, file->buffer, READ_SIZE);
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
			file->delim = buffer[i];
			/*end is actually the new line or EOF*/
		}
		else
		{
			file->end = file->used;
			file->delim = 0;
		}
		r = file->end - file->start;
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
	char *new_array;

	if (arr->size == 0)
	{
		arr->array = malloc(READ_SIZE);
		if (!arr->array)
			return (1);
		arr->size = READ_SIZE;
		arr->used = 0;
		memset(arr->array, 0, arr->size);
	}

	check = 0;
	if ((arr->used >= arr->size) || size >= (arr->size - arr->used))
	{
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
	memcpy(arr->array + arr->used, value, size);
	arr->used += size;
	arr->array[arr->used] = '\0';
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
file_data_t *get_fd(struct file_data **files, const int fd)
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
	/* first time or file not seen */
	file_data = malloc(sizeof(*file_data));
	if (!file_data)
	{
		free_files(*files);
		return (NULL);
	}
	memset(file_data, 0, sizeof(*file_data));
	file_data->fd = fd;
	file_data->next = NULL;
	if (!*files)
		*files = file_data;
	else
		tmp->next = file_data;
	return (file_data);
}


/**
 * fill_line - fill the line to return
 * @line: struct containing line info
 * @file: struct containing file info
 * Return: 0 on success 1 on error and everything needs
 * to be freed -1 if end of file to free the file struct
 */
int fill_line(struct resizing_string *line, file_data_t *file)
{
	int check;
	int r;

	check = 0;

	read_file(file);
	if (!file->used) /* means there is nothing to play with */
		return (-1);
	r = file->end - file->start;
	while (file->delim == 0 && r > 0)
	{
		check = fill_array(line,
				   file->buffer + file->start, r);
		if (check)
			break;
		file->start = file->end + 1;
		r = read_file(file);
	}
	if (!check && r >= 0)
	{
		check = fill_array(line,
				   file->buffer + file->start, r);
	}
	if (file->delim == EOF)
		check = -1;
	file->delim = 0, file->start = file->end + 1;
	file->end = file->used;
	return (check);
}


/**
 * _getline - given a file descriptor returns a file line per line
 * @fd: file descriptor
 * Return: a line (to free by user)
 */
char *_getline(const int fd)
{
	int check;
	static file_data_t *files; /* holds fd + buffer... */
	struct resizing_string line; /* output */
	file_data_t *file, *tmp;

	memset((void *)&line, 0, sizeof(line));
	check = 0;
	if (!READ_SIZE)
		return (NULL);
	if (fd >= 0)
	{
		file = get_fd(&files, fd);
		if (!file)
			check = 1;
		else
			check = fill_line(&line, file);
	}
	if (fd == -1 || check == 1)
	{
		if (files)
			free_files(files), files = NULL;
		if (line.array)
			free(line.array);
		return (NULL);
	}
	if (check == -1)
	{
		if (files == file)
			files = file->next;
		else
		{
			tmp = files;
			while (tmp->next && (tmp->next)->fd != fd)
				tmp = tmp->next;
			tmp->next = file->next;
		}
		free(file);
	}
	line.size = 0, line.used = 0;
	return (line.array);
}
