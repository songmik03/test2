#include <stdio.h>

int main()
{
	int num1;

	printf("input:");
	scanf("%d", &num1);
	
	if(num1>5)
	{
		printf(">5 \r\n");
	}

	else if(num1>3)
	{
		printf(">3 \r\n");
	}
	else
	{
		printf("<5 \r\n");
	}
	
	return 0;

}
