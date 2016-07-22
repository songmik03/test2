#include <stdio.h>

int num1 =7;

void test()
{
	printf("%d\r\n", num1);
}
int main()
{
	int num1 =3;
	//int num1 =4; ---변수 덮어쓰기 안됨.
	{
		int num1=4;
		printf("%d \r\n", num1);
	}

	printf("%d \r\n", num1);
	
	test();

	return 0;
}
