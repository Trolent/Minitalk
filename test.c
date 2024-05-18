#include <stdio.h>

int main()
{
	char *str = "hello";

	str = NULL;

	printf("%p\n", str);

	printf(str);
}
