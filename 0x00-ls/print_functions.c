#include "hls.h"
/*
 * WIP to print files
 */

/**
 * read_file - read lstat
 * @path: path to file
 */
void read_file(char *path)
{
	struct stat file;
	int check;

	check = lstat(path, &file);
	if (!check)
	{
		print_file_mode(file.st_mode);
		print_date(&file.st_mtime);
		puts("");
		printf("I-node dumber: %ld ", (long) file.st_ino);
		printf("Link count: %ld ", (long) file.st_nlink);
		printf("Ownership: UID=%ld GID=%ld ", (long) file.st_uid,
		       (long) file.st_gid);
		printf("File size: %ld bytes\n", (long) file.st_size);
		/*
		 * printf("Last status change: %s", ctime(&file.st_ctime));
		 * printf("Last file access : %s", ctime(&file.st_atime));
		 */
	}
}

/**
 * print_file_mode - print file mode
 * @mode: mode of file
 */
void print_file_mode(mode_t mode)
{
	char details[11];

	switch (mode & S_IFMT)
	{
	case S_IFBLK:
		details[0] = '?'; break;
	case S_IFCHR:
		details[0] = '?'; break;
	case S_IFDIR:
		details[0] = 'd'; break;
	case S_IFIFO:
		details[0] = '?'; break;
	case S_IFLNK:
		details[0] = '?'; break;
	case S_IFREG:
		details[0] = '-'; break;
	case S_IFSOCK:
		details[0] = '?'; break;
	default:
		details[0] = '?'; break;
	}
	details[1] = (mode & S_IRUSR) ? 'r' : '-';
	details[2] = (mode & S_IWUSR) ? 'w' : '-';
	details[3] = (mode & S_IXUSR) ? 'x' : '-';
	details[4] = (mode & S_IRGRP) ? 'r' : '-';
	details[5] = (mode & S_IWGRP) ? 'w' : '-';
	details[6] = (mode & S_IXGRP) ? 'x' : '-';
	details[7] = (mode & S_IROTH) ? 'r' : '-';
	details[8] = (mode & S_IWOTH) ? 'w' : '-';
	details[9] = (mode & S_IXOTH) ? 'x' : '-';
	details[10] = '\0';
	printf("%s ", details);
}

/**
 * print_date - print date for ls
 * @timep: string of detailed timestamp
 */
void print_date(const time_t *timep)
{
	char *date;
	size_t start, end, i;

	date = ctime(timep);
	/*
	 * date format is 3chars for day, space 3chars for months
	 * space 2chars for daynumber space hh:mm:ss space year
	 */
	start = 3 + 1;
	end = 3 + 1 + 3 + 2 + 1 + 2 + 1 + 2;
	for (i = start; i <= end; ++i)
	{
		printf("%c", date[i]);
	}
}
