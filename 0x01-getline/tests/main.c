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
	int fd, i;
    char *line;

    fd = open("tests/alice2.txt", 0);
    i = 0;
    while ((line = _getline(fd)) && i++ < 10)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
