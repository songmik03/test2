#include <stdio.h>

int main()
{
	char aStr[] = "world";
	char *pStr = "hello";

	printf("%s %s \r\n", aStr, pStr);

	pStr = aStr;

	printf(" %s \r\n",pStr);

	//aStr = pStr; //배열은 배열. 포인터처럼 자유롭지 x


	return 0;
}

