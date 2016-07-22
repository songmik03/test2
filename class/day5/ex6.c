#include <stdio.h>

int main()
{
	int num[] = {3,7,15,6,8,2};

	printf("배열의 갯수 : %d \r\n", sizeof(num)/sizeof(int));


	int sum =0;
	int max = -999999;
	int min = 999999;
	
	for(int i=0;i<sizeof(num)/sizeof(int);i++) {
		//sum = sum+ num[i];
		sum += num[i];

		if(max<num[i]) {
			max=num[i];
			
		}

		if(min>num[i]) {
			min=num[i];
		}

		
		
	}

	printf("max =%d, min=%d \r\n", max, min);
	printf("%d \r\n", sum);

	return 0;
}
