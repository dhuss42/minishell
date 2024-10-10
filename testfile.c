#include <stdio.h>
#include "executor.h"

// int main()
// {
// 	printf("helloWorld\n");
// 	return (0);
// }

int main()
{
	int fd;

	fd = open("out1", O_WRONLY | O_CREAT);
	write (fd, "Amsel?", 6);
	return (0);
}
