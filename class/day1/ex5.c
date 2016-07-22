#include <stdio.h>
#include <stdlib.h>

void setColor(int fore_color, int back_color)
{
    printf("%c[%d;%dm",0x1b,fore_color,back_color);

}

void gotoxy(int x, int y)
{
	printf("%c[%d;%df",0x1b,y,x);
}

int main()
{

	int fore_color;
	fore_color = 31;
	system("clear");
	
    gotoxy(10,0);
	printf("=====================");

	//gotoxy(1,1);
	//printf("!");
	gotoxy(0,2);
	printf("---------!");
	gotoxy(0,3);
	printf("---------!");
	gotoxy(0,4);
	printf("---------!");
	gotoxy(10,5);
	printf("!");
	gotoxy(10,6);
	printf("!");
	gotoxy(0,7);
	printf("---------!");
	gotoxy(0,8);
	printf("---------!");
	gotoxy(0,9);
	printf("---------!");
	gotoxy(10,10);
	printf("!");

		


	gotoxy(18,3);
	//     "\x1b[31m"
    //printf("%c[%dm",0x1b,fore_color);
	setColor(30,43);
	printf("hello");
	
	gotoxy(18,8);

	setColor(31,46);
	printf("world");
	
	setColor(0,0); //reset ansi command

	//gotoxy(20,1);
	//printf("!");
	gotoxy(30,2);
	printf("!---------");
	gotoxy(30,3);
	printf("!---------");
	gotoxy(30,4);
	printf("!---------");
	gotoxy(30,5);
	printf("!");
	gotoxy(30,6);
	printf("!");
	gotoxy(30,7);
	printf("!---------");
	gotoxy(30,8);
	printf("!---------");
	gotoxy(30,9);
	printf("!---------");
	gotoxy(30,10);
	printf("!");






	gotoxy(10,10);
	printf("=====================");

	return 0;

}
