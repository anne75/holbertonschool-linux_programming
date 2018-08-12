#include <stdio.h>
#include <unistd.h>


/**
 * ask_for_brk - return next brk address
 * @size: size by which to extend prgm break
 * Return: pointer to new address
 */
void *ask_for_brk(long size)
{
	void *brk_ptr;
	size_t *chunk_ptr;

	brk_ptr = sbrk(size);
	if (brk_ptr == (void *) -1)
		return (NULL);
	chunk_ptr = brk_ptr;
	*chunk_ptr = size;

	return (brk_ptr);
}


/**
 * naive_malloc - extend program break
 * @size: number of bytes to extend break with.
 * Return: pointer to allocated space on success or NULL.
 */
void *naive_malloc(size_t size)
{
	static void *start_addr;
	static long page_size;
	static size_t number_func_call, i;
	size_t *chunk_ptr, total_size, chunk_size;
	char *tmp, *to_return;
	void *new_addr;

	/* on first call, increase break */
	if (number_func_call == 0)
	{
		page_size = sysconf(_SC_PAGESIZE);
		start_addr = ask_for_brk(page_size);
		if (!start_addr)
			return (NULL);
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

	/* not enough space*/
	if (size + 2 * sizeof(size_t) > total_size)
	{
		new_addr = ask_for_brk(page_size);
		if (!new_addr)
			return (NULL);
		total_size += page_size;
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
