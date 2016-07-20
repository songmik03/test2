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
#include <math.h>

#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "packet.h"

pthread_t tid;

//invader game

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;


_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;
_S_Plane gPlayerObject;


void *InputThread(void *arg)
{
	while(1)
	{
		char ch = getch();
		if(ch == 'q') {
			bLoop=0;
			puts("bye~ \r");
		}
		gPlayerObject.pfApply(&gPlayerObject,0,ch);
	}


	return NULL;
}

int main()
{
	{
		int err=pthread_create(&tid,NULL,&InputThread,NULL);
		if(err != 0) {
			printf("err : %s \r\n",strerror(err));
		}
		else{
			printf("thread successfully created \r\n");
		}
	}
	
	for(int i=0;i<2;i++) {
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],35,16);

		
	}

	map_init(&gPlayerModel);
	map_load(&gPlayerModel, "plasma.dat");


	Plane_init(&gPlayerObject,&gPlayerModel,15,10);
	gPlayerObject.m_nFSM = 1;	


	system("clear");
	set_conio_terminal_mode();
	acc_tick = last_tick = 0;

	while(bLoop) {

		//타이밍 처리
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + (double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;

		last_tick = cur_tick;
		
		//타이밍 계산
		acc_tick += delta_tick;

		if(acc_tick>0.1) {
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);
			gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuf[1]);

			map_dump(&gScreenBuf[1],Default_Tilepalette);
			acc_tick = 0;
		}
	}
	return 0;
}

