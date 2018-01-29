#include <stdlib.h>
#include <stdio.h>

#include "hls.h"


/**
 * parse_command_line - split command line in options and directorties
 * @ac: int
 * @av: array of strings
 * @options: strcut for options
 * @files: resizing array for the files
 */
void parse_command_line(int ac, char **av, struct ls_options *options,
			struct resizing_array *files)
{
	int i;
	char *file;

	for (i = 1; i < ac; ++i)
	{
		if (av[i][0] == '-')
		{
			fill_options(options, ++av[i]);
		}
		else
		{
			file = strdup(av[i]);
			fill_array(files, (void *) file);
		}
	}
}

/**
 * fill_options - fill the options struct
 * @options: struct
 * @op: string of options
 */
void fill_options(struct ls_options *options, char *op)
{
	int l, i;

	l = strlen(op);

	for (i = 0; i < l; ++i)
	{
		switch (op[i])
		{
		case 'a':
			options->skip = 2; break;
		case'A':
			options->skip = 1; break;
		case 'f':
			options->sort = 1; break;
		case 'l':
			options->long_listing = 1; break;
		case '1':
			options->separator = 1; break;
		}
	}
}
