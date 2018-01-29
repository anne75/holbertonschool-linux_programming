#include "hls.h"

/**
 * main - entrypoint
 * @ac: number of arguments
 * @av: array of arguments
 * Return: an int
 */
int main(int ac, char **av)
{
	struct ls_options options;
	struct resizing_array all_dirs, *cwd;
	size_t i;
	char *def[] = {".", "."};

	if (ac < 2)
	{
		ac = 2;
		av = def;
	}
	_memset((void *) &options, 0, sizeof(options));
	_memset((void *) &all_dirs, 0, sizeof(all_dirs));
	parse_command_line(ac, av, &options, &all_dirs);

	/* loop through arguments */
	for (i = 0; i < all_dirs.used; ++i)
	{
		cwd = read_cwd(all_dirs.array[i], &options);
		if (!cwd)
			continue;
		print_cwd(cwd, &options);
		free(cwd->array);
		free(cwd);
		free(all_dirs.array[i]);
	}
	free(all_dirs.array);
	if (!cwd)
		return (2);
	return (0);
}

/**
 * print_cwd - WIP to print directory
 * @cwd: files
 * @options: printing options
 */
void print_cwd(struct resizing_array *cwd, struct ls_options *options)
{
	size_t i;
	char separator;

	separator = ' ';
	if (!options->sort)
	{
		qs_a(cwd->array, cwd->used);
	}
	if (options->separator)
		separator = '\n';
	for (i = 0; i < cwd->used; ++i)
	{
		printf("%s", ((struct fileinfo **)cwd->array)[i]->name);
		free(((struct fileinfo **)cwd->array)[i]->name);
		free(((struct fileinfo **)cwd->array)[i]->stat);
		free(cwd->array[i]);
		if (i < cwd->used - 1)
			printf("%c", separator);
	}
	printf("\n");
}
