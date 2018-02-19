#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char *s1 = "Hello World";
	char *s2;

	s2 = strdup(s1);
	while (1)
	{
		printf("%s\n", s2);
		sleep(2);
	}
	return (0);
}
