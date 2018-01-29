#include "hls.h"

/**
 * qs_a - implement quick sort
 * @array: an array eventually of fileinfo
 * @size: size of array
 */
void qs_a(void **array, size_t size)
{
	if (!array || !*array || size < 2)
		return;

	qs_arec(array, 0, size - 1);
}

/**
 * qs_arec - quick sort recursion
 * @array: array
 * @low: smallest index to consider
 * @high: highest index to consider
 */
void qs_arec(void **array, size_t low, size_t high)
{
	size_t p;

	if (low >= high)
		return;
	p = partition(array, low, high);
	if (p > 0) /* not necessary, not ready to take it away */
		qs_arec(array, low, p - 1);
	qs_arec(array, p, high);
}

/**
 * partition - quick sort partition
 * @array: array
 * @low: smallest index to consider
 * @high: highest index to consider
 * Return: index for next partition
 */
size_t partition(void **array, size_t low, size_t high)
{
	size_t i, j;
	struct fileinfo  *tmp, *pivot;

	pivot = array[high];
	i = low - 1;
	j = high + 1;
	while (1)
	{
		do {
			--j;
		} while (compare_fileinfo(pivot, (struct fileinfo *)array[j]) < 0);
		do {
			++i;
		} while (compare_fileinfo((struct fileinfo *)array[i], pivot) < 0);
		if (i < j)
		{
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
		else
		{
			return (i);
		}
	}
}
