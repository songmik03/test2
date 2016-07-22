#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../engine/engine2d.h"

char *pMapBuf;
char chrTable[] = {'.','#','@','*'};

int main()
{
	int width, height;
	FILE *pf;
	pf = fopen("./ex2.data.txt","r");
	
	char buf[256];

	fgets(buf,256,pf);
	puts(buf);

	char *pTemp = strtok(buf, ",");
	//puts(pTemp);
	width = atoi(pTemp);
	pTemp = strtok(NULL,",");
	//puts(pTemp);
	height = atoi(pTemp);
	
	/*fgets(buf,256,pf);
	puts(buf);
	fgets(buf,256,pf);
	puts(buf);*/

	pMapBuf = (char *)malloc(width*height);
	
	int ix,iy;
	for(iy=0;iy<height;iy++) {
		fgets(buf,256,pf);
		pTemp = strtok(buf,",");
		pMapBuf[iy*width+0] = atoi(pTemp);
		for(ix=1;ix<width;ix++) {
			pTemp = strtok(NULL, ",");
			pMapBuf[iy*width +ix] = atoi(pTemp);
	
		}
	}
	putTile(0,height,0,width,width,pMapBuf,chrTable);

	free(pMapBuf);
	fclose(pf);

}
