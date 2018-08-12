#include <stdio.h>
#include <unistd.h>



/**
 * naive_malloc - extend program break
 * @size: number of bytes to extend break with.
 * Return: pointer to allocated space on success or NULL.
 */
void *naive_malloc_header(size_t size)
{
	void *p;
	size_t *chunk_ptr, total_size;

	/* create header to write size of chunk */
	total_size = sizeof(size_t) + size;
	p = sbrk(total_size);
	if (p == (void *) -1 )
		return (NULL);

	chunk_ptr = p;
	*chunk_ptr = total_size;
	p = (void *)((char *)p + sizeof(size_t));
	return (p);
}
