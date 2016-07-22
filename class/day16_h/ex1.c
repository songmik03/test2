#include <stdio.h>
#include <string.h>

int array[] = {1,2,3,4,5,6,7,8};
int rangeSize = sizeof(array)/sizeof(int);
int temp[10];

int main()
{
	
	memcpy(temp,array,sizeof(array));


	for(int i=0;i<rangeSize;i++) {
		array[(rangeSize-1)-i] = temp[i];
	}
	
	for(int i=0;i<rangeSize;i++) {
		printf("%d,", array[i]);
	}
	return 0;
}
