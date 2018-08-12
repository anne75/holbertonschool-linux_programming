#include <stdio.h>
#include <unistd.h>



/**
 * naive_malloc - extend program break
 * @size: number of bytes to extend break with.
 * Return: pointer to allocated space on success or NULL.
 */
void *naive_malloc(size_t size)
{
	void *p;

	p = sbrk(size);
	if (p == (void *) -1 )
		return (NULL);

	return (p);
}
