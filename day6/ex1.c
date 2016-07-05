#include <stdio.h>

int main() 
{

	int ary[5] = {1,2,3,4,5};
	int ary2[5]; //상수 read only 쓸수는 없고 읽기만 가능
	int *pAry;

	pAry = ary;

	printf("%d %d\r\n", pAry[1], *(ary+1));

	//ary2 = ary; x 쓰는건 불가능, 읽기만 가능

	




	return 0;
}
