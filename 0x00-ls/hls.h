#ifndef HLS_H_
#define HLS_H_
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>

#define BASESIZE 8

/**
 * enum sorting - enum for sorting files
 * @sorted: sorted, 0
 * @not_sorted: -f, 1
 * @reverse_sorted: reverse, 2
 */
enum sorting
{
	sorted,
	not_sorted,
	reverse_sorted
};

/**
 * enum skipping - enum if need to skip files
 * @no_dot: default
 * @little: -A
 * @all: list all, -a
 */
enum skipping
{
	no_dot,
	little,
	all
};

/**
 * enum separator - enum to pick separator
 * @space: use space
 * @enter: use \n
 */
enum separator
{
	space,
	enter
};

/**
 * struct ls_options - holds printing options
 * @sort: how to sort files
 * @skip: should some files be skipped
 * @separator: how to separate
 * @long_listing: use long listing
 */
struct ls_options
{
	enum sorting sort;
	enum skipping skip;
	enum separator separator;
	int long_listing;
};

/**
 * struct resizing_array - a resizing array
 * @array: the array
 * @size: size of array
 * @used: number of elements used
 */
struct resizing_array
{
	void **array;
	size_t size;
	size_t used;
};

/**
 * struct fileinfo - holds file information
 * @name: name of file
 * @stat: stat of file
 */
struct fileinfo
{
	char *name;
	struct stat *stat;
};


void print_cwd(struct resizing_array *cwd, struct ls_options *options);


void read_file(char *path);
void print_file_mode(mode_t mode);
void print_date(const time_t *timep);


void parse_command_line(int ac, char **av,
			struct ls_options *options,
			struct resizing_array *files);
void fill_options(struct ls_options *options, char *op);

int resize_array(struct resizing_array *arr);
int fill_array(struct resizing_array *arr, void *value);


struct resizing_array *read_cwd(char *dirp, struct ls_options *options);
char *get_full_path(char *path, char *name);
int skip_file(char *name, struct ls_options *options);
int add_file_to_cwd(char *name, char *full_path, struct resizing_array *cwd);

int _isalpha(char c);
int compare_strings(char *n1, char *n2);
int _islowercase(char c);
int _isuppercase(char c);
int _strcmp(char *n1, char *n2);
int compare_fileinfo(struct fileinfo *f1, struct fileinfo *f2);

void qs_arec(void **array, size_t low, size_t high);
size_t partition(void **array, size_t low, size_t high);
void qs_a(void **array, size_t size);


char *_strdup(char *str);

void *_memset(void *s, char b, unsigned int n);

#endif
