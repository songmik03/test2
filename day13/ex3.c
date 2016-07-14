#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"

int main()
{
	_S_MAP_OBJECT ScreenBuf;
	map_init(&ScreenBuf);
	map_new(&ScreenBuf,35,17);
	
	system("clear");
	gotoxy(0,0);
	
	double startx,starty;
	double endx,endy;

	startx = 14; starty = 8;
	endx = 1; endy = 1;

	map_put(&ScreenBuf,(int)startx,(int)starty,1);
	map_put(&ScreenBuf,(int)endx,(int)endy,2);

	double mx,my;
	mx = startx; my = starty;

	double vx =endx - startx; //밑변
	double vy =endy - starty; //높이

	//단위 벡터 구하기--대각선으로 이동
	double c = sqrt(vx*vx + vy*vy);

	vx /=c;
	vy /=c;


////////////////////////////////////////////////////////
	
	//for(int i=0;i<8;i++) {	// i <- 시간 값
	
	while(1)
	{
		mx += vx * 2.0; // 2.0 <- 스피드 값
		my += vy * 2.0;
		
		if((int)mx == endx && (int)my == (int)endy) {
			
			break;
		}

		map_put(&ScreenBuf, (int)mx, (int)my,5);
		map_dump(&ScreenBuf, Default_Tilepalette);
	}
	return 0;	
}
