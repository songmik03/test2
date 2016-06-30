#include <stdio.h>
#include <stdlib.h>
#include "../engine2d.h"

int main()
{

	int bLoop =1;
	char cmd;
	int xpos, ypos;

	xpos=1;
	ypos=1;
	
	int orc_xpos, orc_ypos;
	orc_xpos=10;
	orc_ypos=10;
	
	while(bLoop){
		scanf("%c",&cmd);
		switch(cmd) {
			case 'u':
			ypos-=1;
			break;

			case 'd':
			ypos+=1;
			break;

			case 'r':
			xpos+=1;
			break;

			case 'l':
			xpos-=1;
			break;

			case 'q':
			bLoop=0;
			break;

			
		}
		
		system("clear");
		//주인공 출력
		drawBox(xpos,ypos,44,1);
	    //몸 ai
		if(orc_xpos > xpos) {
			orc_xpos-=1;

		}
		else if(orc_xpos< xpos) {
			orc_xpos+=1;
		}
		else {
		}

		//몹 출력
		drawBox(orc_xpos,orc_ypos,42,3);
	
		gotoxy(0,20);
		printf("--u:up d:down r:right l:left--\r\n");
	

	}


	return 0;	

}
