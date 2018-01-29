#include "hls.h"


/*wip, use first lstat call*/
/**
 * read_cwd - collect all files in a directory
 * @dirp: path to directory
 * @options: print options
 * Return: struct holding the files, a resizing array
 */
struct resizing_array *read_cwd(char *dirp, struct ls_options *options)
{
	DIR *dir;
	struct dirent *read;
	char *full_path;
	struct resizing_array *cwd;
	int check;
	struct stat dirp_info;

	check = lstat(dirp, &dirp_info);
	if (check)
		return (NULL);
	dir = opendir(dirp);
	if (dir == NULL)
	{
		/*dir does not exist or file*/
		printf("ls: cannot access %s: No such file or directory\n",
		       dirp);
		return (NULL);
	}
	cwd = malloc(sizeof(*cwd));
	if (!cwd)
		return (NULL);
	while ((read = readdir(dir)) != NULL)
	{
		if (!skip_file(read->d_name, options))
		{
			full_path = get_full_path(dirp, read->d_name);
			if (!full_path)
			{
				break;
			}
			check = add_file_to_cwd(read->d_name,
						full_path, cwd);
			if (check)
			{
				break;
			}
		}
	}
	closedir(dir);
	return (cwd);
}

/**
 * get_full_path - join 2 strings to make a path
 * @path: path to directory
 * @name: file name
 * Return: full path
 */
char *get_full_path(char *path, char *name)
{
	char *result;

	if (!path && !name)
		return (NULL);
	if (!path)
	{
		result = _strdup(name);
	}
	else if (!name)
	{
		result = _strdup(path);
	}
	else
	{
		result = malloc(sizeof(char) *
				(strlen(path) + strlen(name) + 2));
		if (result)
		{
			result[0] = '\0';
			strncat(result, path, strlen(path));
			result[strlen(path)] = '/';
			result[strlen(path) + 1] = '\0';
			strncat(result, name, strlen(name) + 1);
		}
	}
	return (result);
}

/**
 * skip_file - check to see if a file needs to be printed
 * @name: name of file
 * @options: printing options
 * Return: 1 for true, 0 for false
 */
int skip_file(char *name, struct ls_options *options)
{
	if (!name || !options)
		return (1);
	if (!options->skip && *name == '.')
	{
		return (1);
	}
	else if (options->skip == 1)
	{
		if (*name == '.')
		{
			if (*(name + 1) == '\0')
				return (1);
			else if ((*name + 1) == '.' &&
				 (*name + 2) == '\0')
				return (1);
		}
	}
	return (0);
}

/**
 * add_file_to_cwd - add a file to the array
 * @name: name of file
 * @full_path: path to file
 * @cwd: struct holding all the files
 * Return: 0 on success, 1 on failure
 */
int add_file_to_cwd(char *name, char *full_path, struct resizing_array *cwd)
{
	int check;
	struct stat *filep;
	struct fileinfo *info;

	filep = malloc(sizeof(*filep));
	if (!filep)
		return (1);
	check = lstat(full_path, filep);
	if (check)
	{
		free(full_path);
		free(filep);
		return (1);
	}
	free(full_path);
	info = malloc(sizeof(*info));
	if (!info)
	{
		free(filep);
		return (1);
	}
	info->name = _strdup(name);
	if (!info->name)
	{
		free(filep);
		free(info);
		return (1);
	}
	info->stat = filep;
	fill_array(cwd, (void *)info);
	return (0);
}
