#include <stdio.h>
#include <string.h>

int main() 
{
	char *pStrCmd = "move position 123,56";

	char *ptr = strstr(pStrCmd, "move");
	
	printf("%s \r\n", ptr);
	
	char pStrTemp[128];

	strncpy(pStrTemp, pStrCmd,4);

	printf("%s \r\n", pStrTemp);

	char *pStrClone;

	//pStrClone = pStrCmd;
	//pStrCmd[0] = 'n';

	pStrClone =strdup(pStrCmd);
	pStrClone[0] = 'a';


	printf("%s \r\n", pStrClone);
	printf("%s \r\n", pStrCmd);


	return 0;
}
