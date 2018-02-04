#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../_getline.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(void)
{
	int fd;
    char *line;

    puts("file1");
    fd = open("tests/emptyfile.txt", 0);
    while ((line = _getline(fd)))
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);

    puts("file2");
    fd = open("tests/main-1.c", 0);
    while ((line = _getline(fd)))
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);

    /* puts("file3"); */
    /* fd = open("tests/oups", 0); */
    /* while ((line = _getline(fd))) */
    /* { */
    /*     printf("%s\n", line); */
    /*     free(line); */
    /* } */
    /* close(fd); */


    return (0);
}
