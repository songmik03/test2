#include <stdio.h>

int main()
{
	int num[]={3,6,4,5,7};
	
	int *pNum=num;
	
	int sum;
	int max=-99999;
	int min=99999;

	printf("%d, %d \r\n", *(pNum+1), num[1]);
	
	for(int i=0; i<sizeof(num)/sizeof(int);i++) {
		printf("%d. \r\n", *(pNum+i));

		sum+=*(pNum+i);
		
		if(max<*(pNum+i)) {
			max=*(pNum+i);
		}

		if(min>*(pNum+i)) {
			min=*(pNum+i);
		}


	}

	printf("max =%d,\r\n min = %d, \r\n sum =%d", max, min, sum);



	return 0; 
}
