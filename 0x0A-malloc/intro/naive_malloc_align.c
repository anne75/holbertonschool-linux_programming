#include <stdio.h>
#include <unistd.h>

#define ALIGN 8

/**
 * ask_for_brk -
 *
 *
 */
/* need to return the start address to main */
/* will be called 1st time and when needed */
/* when needed, there will be some adjustments for chunk_ptr */
void *ask_for_brk(long size)
{
	void *brk_ptr;
	size_t *chunk_ptr;

	puts("increase program break");
	brk_ptr = sbrk(size);
	if (brk_ptr == (void *) -1 )
		return (NULL);
	chunk_ptr = brk_ptr;
	*chunk_ptr = size;

	return (brk_ptr);
}


/**
 * get_aligned_size - get size keeping stuff aligned
 *
 */
size_t get_aligned_size(size_t old_size)
{
	size_t new_size;

	if (!old_size)
		return (0);

	new_size = (old_size / ALIGN + 1) * ALIGN;
	return (new_size);
}


/**
 * naive_malloc_align - extend program break
 * @size: number of bytes to extend break with.
 * Return: pointer to allocated space on success or NULL.
 */
void *naive_malloc_align(size_t size)
{
	static void *start_addr;
	static long page_size;
	static size_t number_func_call, i, aligned_size;
	size_t *chunk_ptr, total_size, chunk_size;
	char *tmp, *to_return;

	/* on first call, increase break */
	if (number_func_call == 0)
	{
		page_size = sysconf(_SC_PAGESIZE);
		start_addr = ask_for_brk(page_size);
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
	aligned_size = get_aligned_size(size);
	if (aligned_size + 2 * sizeof(size_t) > total_size)
	{
		puts("Not enough space");
		ask_for_brk(page_size);
		total_size += page_size;
	}

	*chunk_ptr = aligned_size + sizeof(size_t);
	to_return = tmp + sizeof(size_t);
	/* go to the end, write remaining size */
	tmp += aligned_size + sizeof(size_t);
	chunk_ptr = (size_t *)tmp;
	*chunk_ptr = total_size - aligned_size - sizeof(size_t);
	++number_func_call;

	return ((void *)to_return);
}
