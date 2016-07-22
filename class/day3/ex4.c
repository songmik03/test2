#include <stdio.h>
#include <stdlib.h>
#include "../engine2d.h"

int main()
{
	system("clear");

	/*int i=0;
	int x=0;

	while(i<20)
	{
		gotoxy(i,i);
		printf("I");
		i++;
	}
	
	while(x<20)
	{
		gotoxy(x,x);
		printf("+");
		x++;
	}
	*/
	int i=0;
	int x=20;

	while(i<20)
	{
		gotoxy(x,i);
		printf("+");
		x--;
	
		setColor(31,27);
		gotoxy(i,i);
		printf("+");
		
		gotoxy(i,10);
		printf("+");
		gotoxy(i,11);
		printf("+");
		i++;


		
	}

	setColor(37,0);
	gotoxy(0,0);
	printf("==================== \r\n");

	gotoxy(0,20);
	printf("==================== \r\n");

	return 0;
}
