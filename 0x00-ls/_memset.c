#include "hls.h"

/**
 * _memset - simple version of memset()
 * @s: buffer to modify
 * @b: value to modify buffer with
 * @n: number of bytes pointed to by s to modify with char b
 *
 * Return: pointer to buffer, s
 */
void *_memset(void *s, char b, unsigned int n)
{
	unsigned int i;
	char *tmp;

	i = 0;
	tmp = (char *) s;

	while (i < n)
		*(tmp + i++) = b;

	return (s);
}
