#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"

#define PI 3.141592
// a : 180 == b : PI
// b =  a/180*PI
//center를 중심으로 돌기

int main()
{
	_S_MAP_OBJECT ScreenBuf;
	map_init(&ScreenBuf);
	map_new(&ScreenBuf,35,17);
	
	system("clear");
	gotoxy(0,0);
	
	double target_x = 14;
	double target_y = 4;

	double center_x = 14;
	double center_y = 8;

	map_put(&ScreenBuf,center_x,center_y,5);
	map_put(&ScreenBuf,target_x,target_y,2);

	
	for(int i=0;i<360;i++) {
		double rad =((double)i)/180*PI;
		double tx,ty;
		ty = (target_x-center_x) * cos(rad) - (target_y-center_y)*sin(rad);
		tx = (target_x-center_x) * sin(rad) + (target_y-center_y)*cos(rad);
		tx += center_x;
		ty += center_y;
		map_put(&ScreenBuf,tx,ty,4);
	}
	map_dump(&ScreenBuf, Default_Tilepalette);
	
	return 0;	
}
