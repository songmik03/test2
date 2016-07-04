#include <stdio.h>
#include <stdlib.h>
#include "../engine2d.h"
#include "exit_room.h"

/*
 1-벽              #
 2-열린문          M
 3-플레이어        A
 4-잠긴문          m
 5-잠김해제장치    K

 */

int world_map[]={
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,5,0,0,0,4,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1



};

//int player_inven; //0 없음, 1 : 키보유


int main()
{
	char cmd;
	int bLoop =1;

	while(bLoop) {

		switch(nFSM) {
			case 0:
				printf("main menu\r\n");
				printf("select => p / x \r\n");

				break;

			case 1:
			
				printf("명령을 선택하세요.\r\n i(up),j(left),l(right),\r\n k(down),s(show map), x(exit)\r\n");
				break;

			case '2':
				break;
		
		}

	//	버퍼 초기화	
		for(int i=0;i<64;i++) {

			buffer_map[i] = world_map[i];
			}	

			scanf("%c", &cmd);
			getchar();

			if(nFSM == 0) {

				switch(cmd) {
					case 'p': 
						nFSM=1; //게임 스타트
						player_inven =0;
						player_xpos=1;
						player_ypos=5;

						printf("게일을 시작합니다");
						break;

					case 'x':
						bLoop =0;
						printf("---------------------------bye\r\n");
						break;
				}
			}

			else if(nFSM == 1) {
				move_player(cmd);
			

				switch(cmd) {
					case 'x':
						bLoop=0;
						printf("--------------------------bye\r\n");
					
						break;

					case 's':
						map_drawAll(buffer_map);
						break;
				}
			}
			else if(nFSM == 2) {
				nFSM=0;
			}

			


	}


	return 0;
}
