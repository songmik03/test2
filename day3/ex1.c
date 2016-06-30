#include <stdio.h>

int main()
{
	char cmd;

	printf("input: (z) or (d)\r\n");
	scanf("%c", &cmd);

	/*if (cmd =='z')
	{
		printf("질럿 생산 \r\n");
	}
	else if (cmd == 'd')
	{
		printf("드래곤 생산 \r\n");
	}
	else
	{
		printf("잘못된 입력 방법\r\n");
	}
	*/

	switch(cmd)
	{
		case 'z':
		printf("질럿\r\n");
		break;

		case 'd':
		printf("dragon \r\n");
		break;
		
		default:
		printf("잘못된 입력 방식 \r\n");

		break;
	}
}
