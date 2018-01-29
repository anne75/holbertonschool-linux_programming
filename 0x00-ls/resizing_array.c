#include "hls.h"

/**
 * resize_array - double the size of an array
 * @arr: pointer to a struct
 * Return: 0 on success, 1 on failure
 */
int resize_array(struct resizing_array *arr)
{
	size_t i;
	void **new_array;

	new_array = malloc((2 * arr->size) * sizeof(*new_array));
	if (!new_array)
		return (1);

	for (i = 0; i < arr->used; ++i)
	{
		new_array[i] = arr->array[i];
	}
	free(arr->array);
	arr->array = new_array;
	arr->size *= 2;
	return (0);
}

/**
 * fill_array - fill a resizing array
 * @arr: struct
 * @value: value to add
 * Return: 0 on success, 1 on failure
 */
int fill_array(struct resizing_array *arr, void *value)
{
	int check;

	if (arr->size == 0)
	{
		arr->array = malloc(BASESIZE * sizeof(*(arr->array)));
		if (!arr->array)
			return (1);
		arr->size = BASESIZE;
		arr->used = 0;
	}

	if (arr->used == arr->size)
		check = resize_array(arr);
	arr->array[arr->used++] = value;
	return (check);
}
