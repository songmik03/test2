#include <stdio.h>
#include <string.h>

int main()
{
	char *pStr = "hello world";
	char strTemp[128];
	
	strcpy(strTemp, pStr);
	
	strTemp[0]='R';

	printf("원본 %s \r\n", pStr);
	printf("%s 을 복사\r\n",strTemp);

	printf("문자열의 길이는 %d \r\n", strlen(strTemp));

	int cmp = strcmp("hello world", "healo world"); //문자열 비교 = 사전적 순서 비교

	printf("%d \r\n", cmp);

	
	char *pstr2 = ", hi world";

	strcat(strTemp, pstr2);
	printf("%s \r\n", strTemp);

	//printf("%s \r\n", strcat(strTemp, pstr2));
	







}
