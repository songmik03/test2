#include <stdio.h>

int main()
{
	char *ptrArray[5] = {
		"apple", "android", "windows", "lilux", "unix"
	};
	for(int i=0; i<5; i++) {
		puts(ptrArray[i]);
	}
	for(int i=0;i<5;i++) {
		putchar(ptrArray[i][0]);
	}
	puts("");
	
}
