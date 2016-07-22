#include <stdio.h>

void exchange(int *pa, int *pb)
{
	int c;

	c=*pa;

	*pa=*pb;
	*pb=c;

}


int main()
{
	int a=10, b=20;

	printf("%d %d \r\n", a, b);
	
	exchange(&a, &b);
	
	printf("%d %d \r\n", a, b);

	
	return 0;
}
