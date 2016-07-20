#include <stdio.h>
#include <string.h>

int array[] = {1,2,3,4,5,6,7,8};
int rangeSize = sizeof(array)/sizeof(int);

void change(int rSize)
{
	int temp[10];
	memcpy(temp,array,sizeof(array));
	
	for(int i=0;i<rSize;i++) {
		array[(rSize-1)-i] = temp[i];
	}

}
int main()
{
	change(rangeSize);	
	
	for(int i=0;i<rangeSize;i++) {
		printf("%d,", array[i]);
	}
	return 0;
}
