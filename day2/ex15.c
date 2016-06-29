#include <stdio.h>

int main()
{
	char ch = 'A';
	char name[80] = "황금박쥐";
	int in=10;
	double db = 16.8;

	printf("정수형 상수 : %d \r\n", -10);
	printf("정수형 변수 : %d \r\n", in);
	printf("정수형 수식 : %d \r\n", in/3);
	
	printf("실수형 상수 : %lf \r\n", 2.5);
	printf("실수형 변수 : %le \r\n", db);
	printf("실수형 수식 : %lf \r\n", db/4);
	
	printf("문자상수형 : %c \r\n", 'F');
	printf("문자변수수형 : %c \r\n", ch);
	printf("문자배열 : %s \r\n", name);
	printf("문자열상수 : %s \r\n", "날아라 태극호");

	return 0;

}
