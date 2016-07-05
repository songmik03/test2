#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	//char *ptr = "move position 30,20";
	char *ptr = strdup("move position 30,20");

	char *ptrTemp;
	
	ptrTemp = strtok(ptr, " "); //공백 문자가 나오면 잘라내라

	printf("%s \r\n", ptrTemp);
	printf("%s \r\n", strtok(NULL," "));
	
	ptrTemp = strtok(NULL, ",");
	printf("%d \r\n", atoi(ptrTemp));
	//printf("%s \r\n", strtok(NULL," "));
	ptrTemp = strtok(NULL, ",");
	printf("%d \r\n", atoi(ptrTemp));
	

	return 0;
}
