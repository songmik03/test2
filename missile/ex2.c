#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"

#include "plane.h"
#include "bullet.h"
#include <math.h>

//대각선으로 가기 

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop=1;

_S_MAP_OBJECT gScreenBuffer[2];
_S_MAP_OBJECT gBulletModel;
S_BULLET_OBJECT gBulletObject;
_S_MAP_OBJECT gPlaneModel;
_S_Plane gPlaneObject;
int main()
{
	set_conio_terminal_mode();

	acc_tick = last_tick = 0;
	for(int i=0;i<2;i++) {
		map_init(&gScreenBuffer[i]);
		map_new(&gScreenBuffer[i],50,30);
	}
	map_init(&gBulletModel);
	map_load(&gBulletModel,"missile.dat");
	bullet_init(&gBulletObject,0,0,0,&gBulletModel);
	
	map_init(&gPlaneModel);
	map_load(&gPlaneModel,"plasma.dat");
	Plane_init(&gPlaneObject,&gPlaneModel,20,3); 
	system("clear");
	
	int targetx, targety;


	int fire_x = 24;
	int fire_y = 28;
	
	//double mx,my;
	//mx = fire_x;
	//my = fire_y;

	
	while(bLoop) {

		//타이밍 처리
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + (double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;

		last_tick = cur_tick;

		//실시간 입력
		if(kbhit() != 0) {
			char ch = getch();
			if(ch == 'q') {
				bLoop=0;
				puts("bye~ \r");
			}
			else if(ch == 'j') {

				targety = gPlaneObject.m_nYpos;
				targetx = gPlaneObject.m_nXpos;


				double vx = targetx - fire_x; //밑변
				double vy = targety - fire_y; //높이

				double dist = sqrt(vx*vx + vy*vy);


				vx /= dist;
				vy /= dist;

				printf(" %d %d \r\n", targetx,targety);

				bullet_fire(&gBulletObject,fire_x,fire_y,7.0,vx,vy,10);
		
			}

			/*
			else if(ch == 'a')
			{
				targetx -= 1;
			}
			else if(ch == 'd')
			{
				targetx += 1;
			}
			else if(ch == 'w')
			{
				targety -=1;
			}
			else if(ch == 's')
			{
				targety +=1;
			}
	*/
		
		
		/////////////////////////////////////////////////apply
			Plane_Apply(&gPlaneObject, delta_tick,ch);
		}
		bullet_apply(&gBulletObject,delta_tick,gPlaneObject.m_nXpos);

				//타이밍 계산
		acc_tick += delta_tick;

		if(acc_tick>0.1) { //0.1->f//1.0->s//
			map_drawTile(&gScreenBuffer[0],0,0,&gScreenBuffer[1]);
			bullet_draw(&gBulletObject,&gScreenBuffer[1],gPlaneObject.m_nYpos);
			gotoxy(0,0);
			map_put(&gScreenBuffer[1],fire_x,fire_y,1);
			
			Plane_Draw(&gPlaneObject,&gScreenBuffer[1]);
			//map_put(&gScreenBuffer[1],targetx,targety,5);
			map_dump(&gScreenBuffer[1],Default_Tilepalette);
			acc_tick = 0;
		}

	}
	return 0;
}

