#include "hls.h"

/**
 * compare_strings - compare 2 strings
 * @n1: a string
 * @n2: a string
 * Return: an int, -1 0, or +1 of n1 < == or > n2
 */
int compare_strings(char *n1, char *n2)
{
	char *s1, *s2;

	if (!n1 && !n2)
		return (0);
	if (!n1)
		return (-1);
	if (!n2)
		return (1);

	s1 = n1;
	s2 = n2;
	while (*n1 && *n1 == '.')
		++n1;
	while (*n2 && *n2 == '.')
		++n2;
	if (!*n1 && !*n2)
		return (_strcmp(s1, s2));
	if (!*n1)
		return (-1);
	if (!*n2)
		return (+1);
	return (_strcmp(n1, n2));
}

/**
 * _islowercase - check if a char is lowercase
 * @c: a char
 * Return: 1 if it is else 0
 */
int _islowercase(char c)
{
	return (c >= 'a' && c <= 'z');
}

/**
 * _isuppercase - check if a char is uppercase
 * @c: a char
 * Return: 1 if is else 0
 */
int _isuppercase(char c)
{
	return (c >= 'A' && c <= 'Z');
}

/**
 * _strcmp - compare 2 strings a la ls
 * @n1: a string
 * @n2: a string
 * Return: a value negative, 0 or positive if n1 is <,
 * == or > n2.
 */
int _strcmp(char *n1, char *n2)
{
	while (*n1 && *n2)
	{
		if (_islowercase(*n1) && _isuppercase(*n2))
		{
			if (*n1 != *n2 - 'A' + 'a')
				break;
		}
		else if (_islowercase(*n2) && _isuppercase(*n1))
		{
			if (*n2 != *n1 - 'A' + 'a')
				break;
		}
		else if (*n1 != *n2)
		{
			break;
		}
		++n1;
		++n2;
	}
	return (*n1 - *n2);
}

/**
 * compare_fileinfo - compare 2 structs by a string member
 * @f1: a struct
 * @f2: a struct
 * Return: the value of the string comparison
 */
int compare_fileinfo(struct fileinfo *f1, struct fileinfo *f2)
{
	return (compare_strings(f1->name, f2->name));
}
