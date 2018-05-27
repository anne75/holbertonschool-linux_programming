#include <Python.h>
#include <stdio.h>
#include <object.h>
#include <longintrepr.h>
#include <longobject.h>


#define SIZE(ob) (((PyVarObject *)(ob))->ob_size)
#define ABS(x) ((x < 0) ? (-x) : (x))

/**
 * print_python_int - print a Python int object
 * @p: PyObject
 * Works if the int object fits in an unsigned long int
 */
void print_python_int(PyObject *p)
{
	unsigned long int result, previous;
	Py_ssize_t size;
	PyLongObject *number;
	char sign;

	setbuf(stdout, NULL); /*remove stdout buffering*/
	if (PyLong_Check(p))
	{
		number = (PyLongObject *)p;
	}
	else
	{
		puts("Invalid Int Object");
		return;
	}
	size = SIZE(number);
	sign = (size < 0) ? 1 : 0;
	switch (size)
	{
	case 0:
		puts("0"); return;
	case -1:
		result = number->ob_digit[0]; break;
	case 1:
		result = number->ob_digit[0]; break;
	default:
		result = 0;
		size = ABS(size);
		while (--size >= 0)
		{
			previous = result;
			result = (result << PyLong_SHIFT) |
				number->ob_digit[size];
			if ((result >> PyLong_SHIFT) != previous)
			{
				puts("C unsigned long int overflow");
				return;
			}
		}
	}
	if (sign)
		printf("-%lu\n", result);
	else
		printf("%lu\n", result);
}
