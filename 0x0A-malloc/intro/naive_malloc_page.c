#include <stdio.h>
#include <unistd.h>



/**
 * naive_malloc_page - extend program break
 * @size: number of bytes to extend break with.
 * Return: pointer to allocated space on success or NULL.
 */
void *naive_malloc_page(size_t size)
{
	static void *start_addr;
	static long page_size;
	static size_t number_func_call, i;
	size_t *chunk_ptr, total_size, chunk_size;
	char *tmp, *to_return;

	/* on first call, increase break */
	if (number_func_call == 0)
	{
		puts("first call");
		page_size = sysconf(_SC_PAGESIZE);
		start_addr = sbrk(page_size);
		if (start_addr == (void *) -1 )
			return (NULL);
		chunk_ptr = start_addr;
		*chunk_ptr = page_size;
	}
	/* go to the first free address */
	tmp = start_addr;
	for (i = 0; i < number_func_call; ++i)
	{
		chunk_ptr = (size_t *)start_addr;
		chunk_size = *chunk_ptr;
		tmp += chunk_size;
	}
	/* there: 8 bytes remaining space available */
	chunk_ptr = (size_t *)tmp;
	total_size = *chunk_ptr;

	/* not enough space, for now too bad */
	printf("remaining size is: %lu, I need: %lu\n", total_size, size + 2 * sizeof(size_t));
	if (size + 2 * sizeof(size_t) > total_size)
	{
		puts("Not enough space");
		return (NULL);
	}

	*chunk_ptr = size + sizeof(size_t);
	to_return = tmp + sizeof(size_t);
	/* go to the end, write remaining size */
	tmp += size + sizeof(size_t);
	chunk_ptr = (size_t *)tmp;
	*chunk_ptr = total_size - size - sizeof(size_t);
	++number_func_call;

	return ((void *)to_return);
}
