#include <stdio.h>

int main()
{
	//0111 1111 = 127, 0x7f
	//1000 0000 = 128, 0x80
	//1111 1111 = 255, 0xff
	
	char a = 0xff;
	unsigned char b = 0xff;


	printf("%d \r\n", 0xff);
	printf("%d, %d \r\n", a, b);


	

	return 0;
}
