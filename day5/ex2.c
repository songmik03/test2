#include <stdio.h>

int main()
{
	double a =1.3;
	double b =1.7;
	
	double c;

	double *pa, *pb;

	printf("a = %f, b = %f \r\n", a, b);

	c=a;
	//printf("%f \r\n", c);

	//*&a=b;
	//*&b=c;
	
	//pa=&b;
	//pb=&c;
	

	pa=&a;
	pb=&b;

	c=*pa;

	*pa = b;  //*pa = *pb
	*pb=c;    //*pb = c

	printf("a = %f, b =  %f \r\n", a, b);
	

	return 0;
}
