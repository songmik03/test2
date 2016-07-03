#ifndef __ENGINE_2D__

#define __ENGINE_2D__

void setColor(int fore_color, int backg_color)
{
	printf("%c[%d;%dm", 0x1b, fore_color, backg_color);
}

void gotoxy(int x, int y)
{
	printf("%c[%d;%df",0x1b,y,x);
}


int drawBox(int nXpos, int nYpos, int nColor, int nSize)
{
	int ix, iy;
	
	setColor(30, nColor);

	ix=0;
	for(iy=0; iy<=nSize ;iy++) {
		for(ix=0; ix<=nSize; ix++){

			gotoxy(ix+nXpos,iy+nYpos);
			printf(" ");
		}

	}

	setColor(0,0);
}

//------------------------------타일맵 엔진
void map_printCell(int rawdata)
{
	
		switch(rawdata) {
			
			case 0:
			//setColor(37,41);
			printf(" ");
			//setColor(0,0);
			break;

			case 1:
			setColor(30,47);
			printf("+");
			setColor(0,0);
			break;

			case 2:
			printf("M");
			break; 

			case 3:
			setColor(33,40);
			printf("A");
			setColor(0,0);
			break;

			case 4:
			setColor(31,40);
			printf("=>");
			setColor(0,0);
			break;

			case 5:
			setColor(34,40);
			printf("K");
			setColor(0,0);
			break;

			default:
			printf(" ");
			break;
			
		}
	
}


void map_drawAll(int *pMap)
{
	int ix, iy;
	for(iy=0;iy<8;iy++) {
		for(ix=0;ix<8;ix++) {
			map_printCell(pMap[ix+iy*8]);
		}
		printf("\r\n");
	}
}


#endif
