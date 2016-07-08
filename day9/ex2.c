#include <stdio.h>
#include "ex2_2.h"
//void foo();

extern int nCount;
int nCount2;

int main()
{
	foo();
	foo();
	nCount = 10;
	nCount2 = 11;
	printf("%d %d \r\n", nCount, nCount2);	
	return 0;
}
