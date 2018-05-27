#include <Python.h>
#include <stdio.h>
#include <locale.h>
#include <object.h>
#include <string.h>
#include <wchar.h>

/* Only print strings that are compact */

#define TYPE(ob) (((PyObject *)(ob))->ob_type)
#define SIZE(ob) (((PyVarObject *)(ob))->ob_size)
#define ASCII(op) (((PyASCIIObject *)op)->state.ascii)
#define COMPACT(op) (((PyASCIIObject *)(op))->state.compact)
/* pointer to the raw unicode buffer for compact objects */
#define DATA(op)                     \
	(ASCII(op) ?                   \
	 ((void *)((PyASCIIObject *)(op) + 1)) :		\
	 ((void *)((PyCompactUnicodeObject *)(op) + 1)))



/**
 * is_type - check if string is list
 * @s: a string
 * @type: type to check for
 * Return: 1 if true 0 otherwise
 */
int is_type(const char *s, const char *type)
{
	unsigned int i;

	if (strlen(s) != strlen(type))
		return (0);
	for (i = 0; *(s + i) && *(s + i) == *(type + i); ++i)
		;
	if (i == strlen(s))
		return (1);
	return (0);
}


/**
 * print_python_string - print strings in python
 * @p: pyObject
 */
void print_python_string(PyObject *p)
{
	Py_ssize_t size, i;
	int nb_bytes;
	void *data;
	unsigned char *one_byte_string;
	unsigned short *two_byte_string;

	setbuf(stdout, NULL); /*remove stdout buffering*/
	setlocale(LC_ALL, "");
	puts("[.] string object info");
	if (is_type(TYPE(p)->tp_name, "str"))
	{
		nb_bytes = PyUnicode_KIND(p);
		size = PyUnicode_GET_LENGTH(p);
		printf("kind: %d size: %lu\n", nb_bytes, size);
		if (ASCII(p) && COMPACT(p))
		{
			puts("  type: compact ascii");
			printf("  length: %lu\n", size);
			printf("  value: %s\n", (char *)(DATA(p)));
		}
		else if (COMPACT(p))
		{
			puts("  type: compact unicode object");
			printf("  length: %lu\n", size);
			printf("  value: ");
			data = DATA(p);
			if (nb_bytes == 1)  /* PyUnicode_1BYTE_KIND */
			{
				one_byte_string = (unsigned char *) data;
				for (i = 0;  i < size; ++i)
					printf("%lc",
					       (wint_t) one_byte_string[i]);
			}
			else if (nb_bytes == 2)
			{
				two_byte_string = (unsigned short *) data;
				for (i = 0;  i < size; ++i)
					printf("%lc",
					       (wint_t) two_byte_string[i]);
			}
			else
			{
				printf("WIP");
			}
			putchar('\n');
		}

	}
	else
	{
		puts("  [ERROR] Invalid String Object");
	}
}
