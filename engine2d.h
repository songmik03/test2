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

#endif
