#include <stdio.h>
#include <stdlib.h>
#include "../engine2d.h"

void drawBox(int xpos, int ypos, int color)
{
	//int xpos, ypos;
	int ix, iy;
	ix=1;
	iy=1;
	//xpos=10;
	//ypos=10;

	setColor(30,color);
	
	while(ix <=6)
	{
		iy=1; //iy초기화

		while(iy <=3)
		{	
			gotoxy(ix+xpos,iy+ypos);
			printf(" ");
			iy++;

		}
		//setColor(30,42+ix);
		ix++;
	}
	setColor(0,0);
}
	
int main()
{
	system("clear");

	drawBox(12,10,41);
	drawBox(10,12,47);

	setColor(30,44);
	gotoxy(0,20);
	printf("                     ");

	setColor(0,0);
	
	return 0;

}
