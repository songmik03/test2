#include <stdio.h>

int main()
{
	char *code ="☞";
	printf("☞\r\n");
	printf("%s\r\n",code);
	printf("%x, %x \r\n", code[0],code[1]);
	printf("");
	return 0;
}
