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
    int fd1, fd2, fd3;
    char *line1;
    char *line2;
    char *line3;
    int i;

    fd1 = open("tests/alice2.txt", O_RDONLY);
    fd2 = open("tests/quote2.txt", O_RDONLY);
    fd3 = open("tests/daffodils2.txt", O_RDONLY);
    printf("---------alice (first 5 lines)-----------\n");
    i = 0;
    while ((line1 = _getline(fd1)))
    {
        printf("%s\n", line1);
        free(line1);
        i++;
        if (i == 5)
        {
            break;
        }
    }
    printf("----------quote (first 5 lines)----------\n");
    i = 0;
    while ((line2 = _getline(fd2)))
    {
        printf("%s\n", line2);
        free(line2);
        i++;
        if (i == 5)
        {
            break;
        }
    }
    printf("-----------daffodil (first 5 lines)---------\n");
    i = 0;
    while ((line3 = _getline(fd3)))
    {
        printf("%s\n", line3);
        free(line3);
        i++;
        if (i == 5)
        {
            break;
        }
    }
    printf("---------alice (END)-----------\n");
    while ((line1 = _getline(fd1)))
    {
        printf("%s\n", line1);  
        free(line1);
    }   
    printf("fd1[%d] fd2[%d] fd3[%d]\n", fd1, fd2, fd3);
    close(fd1);
    close(fd2);
    close(fd3);
    _getline(-1);
    printf("---------daffodils (FULL-TEXT)-----------\n");
    fd1 = open("tests/daffodils2.txt", O_RDONLY);
    while ((line1 = _getline(fd1)))
    {
        printf("%s\n", line1);      
        free(line1);
    }   
    close(fd1);
    _getline(-1);
    return (EXIT_SUCCESS);
}

