#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../engine/engine2d.h"
#include "r_game.h"

char screen_buffer[10*10];

struct timespec work_timer;
double acc_tick,last_tick;


double rock_acc_tick;
int rock1_pos_x,rock1_pos_y;
int rock2_pos_x,rock2_pos_y;

//int rock_pos_table[8] = {1,3,2,3,4,5,2,7};

char rock_pos[2][8] = {
	{1,3,2,3,4,5,2,7},
	{7,5,7,1,6,3,1,3}
};

int wall_xpos[2] = {0,9};
int wall_ypos[10] = {0,1,2,3,4,5,6,7,8,9};

int rock_cur_table_index =0;
int bLoop=1;

int car_posx, car_posy;

static int nFSM = 0;
static int nStep = 0;

void rg_PlayGame(double delta_tick)
{	
	int old_car_posx = car_posx;
	int old_car_posy = car_posy;

	switch(nStep) {
		case 0:
			nStep++;
			system("clear");
			break;

		case 1:
			//사용자 입력처리
			if (kbhit() != 0) {
				char ch = getch();
				if(ch == 'q') {
					bLoop =0;
				}
				else if(ch == 'a') {
					car_posx -=1;

				}
				else if(ch == 'd') {
					car_posx +=1;

				}
				else if(ch == 'w') {
					car_posy -=1;
				}

				else if(ch == 's') {
					car_posy +=1;

				}
			}
			//바위 움직이기
			rock_acc_tick += delta_tick;

			if(rock_acc_tick>0.5) {
				rock_acc_tick =0;
				rock1_pos_y +=1;
				rock2_pos_y +=1;
				//화면 끝 도달..

				if(rock1_pos_y>=10 && rock2_pos_y>=10) {
					rock1_pos_y =0;
					rock2_pos_y =0;
					rock_cur_table_index++;
					rock_cur_table_index %= 8;
					rock1_pos_x = rock_pos[0][rock_cur_table_index];
					rock2_pos_x = rock_pos[1][rock_cur_table_index];
				}
			}

			for(int i=0;i<100;i++) { //스크린버퍼 초기화
				screen_buffer[i]=0;
			}
			//벽
			for(int i=0;i<2;i++) {
				for(int a=0;a<10;a++) {
					screen_buffer[wall_ypos[a]*10+wall_xpos[i] ]= 3;
			}
			}
			//자동차 그리기
			screen_buffer[car_posy*10+car_posx] = 2;
			//바위 그리기
			screen_buffer[rock1_pos_y*10+rock1_pos_x] = 1;
			screen_buffer[rock2_pos_y*10+rock2_pos_x] = 1;

			acc_tick += delta_tick;
			if(acc_tick> 0.1 || bLoop == 0) {
				acc_tick = 0;
				drawGame(10,10,screen_buffer);
			}
			
				//게임 로직(판정)
			for(int ii=0;ii<2;ii++) {
				for(int aa=0;aa<10;aa++) {
					if(wall_xpos[ii] == car_posx && wall_ypos[aa] == car_posy) {
						car_posx = old_car_posx;
						car_posy = old_car_posy;
					}
				}
			}
			if((rock1_pos_y == car_posy && rock1_pos_x == car_posx) || (rock2_pos_y == car_posy && rock2_pos_x == car_posx)) 
			{
				bLoop=0;
				//drawGame(screen_buffer);
				printf("game over \n");
				/*puts(" yes or no");
				if(kbhit() !=0) {
					char ch =getch();
					if(ch == 'y') {
						printf("yes!");
						//bLoop=0;
						nFSM=0;
					}
					else if(ch =='n') {
						printf("bye");
						bLoop=0;
					}
				}*/
			}

		
			break;
	}
}
void rg_apply_mainTitle()
{
	switch(nStep) {
		case 0:
			puts("press to start");
			nStep =1;
			break;

		case 1:
			//사용자 입력처리
			if (kbhit() != 0) {
				char ch = getch();
				nFSM =1;
				nStep = 0;
			}
			break;


	}

}
int main()
{

	for(int i=0;i<100;i++) { //스크린버퍼 초기화
		screen_buffer[i]=0;
	}
	set_conio_terminal_mode();

	acc_tick = last_tick = 0;
	system("clear");

	car_posy = 7;
	car_posx = 4;

	rock1_pos_y = 0;
	rock2_pos_y = 0;
	rock1_pos_x = rock_pos[0][rock_cur_table_index];
	rock2_pos_x = rock_pos[1][rock_cur_table_index];
	
	while(bLoop) {

		//타이밍 처리
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + (double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;

		last_tick = cur_tick;

		if(nFSM == 0) { //타이틀 메뉴 상태

			rg_apply_mainTitle(delta_tick);
		}
		else if(nFSM == 1) { //게임 플레이 상태
			rg_PlayGame(delta_tick);
		}
		else {
		}
	}

	return 0;
}
