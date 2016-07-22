#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a;
	int *ip;
	ip = (int*)malloc(4); 
	//ip=&a;

	*ip = 10;

	printf("%d \r\n", *ip);

	free(ip);

	return 0;

}
