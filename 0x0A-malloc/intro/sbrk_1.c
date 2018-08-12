#include <stdio.h>
#include <unistd.h>


/**
 * main - entrypoint
 *
 * Return: 0
 */
int main(void)
{
	char *ptr;
	void *p;

	/* extend program break by one byte */
	ptr = (char *) sbrk(1);
	printf("Starting break is %p\n", (void *) ptr);
	*ptr = 'H';
	p = sbrk(0);
	printf("After ask address is %p\n", p);
	printf("Adress of char %p - value %c\n", (void *) ptr, *ptr);

	return (0);
}
