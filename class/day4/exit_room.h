#ifndef __EXIT_ROOM__
#define __EXIT_ROOM__


int buffer_map[64];

int nFSM = 0;

int player_xpos;
int player_ypos;
int player_inven; //0없음 , 1 : 키보유

int key_xpos;
int key_ypos;

void move_player(char cmd)
{  
	int old_xpos = player_xpos;
	int old_ypos = player_ypos;

	switch(cmd)
	{
		case 'i':
			printf("up \r\n");
			player_ypos-=1;	
			break;

		case 'j':
			player_xpos-=1;
			break;

		case 'l':
			player_xpos+=1;
			break;

		case 'k':
			player_ypos+=1;
			break;

	}

	switch(buffer_map[player_xpos+player_ypos*8]) {

		case 0: //공간
			break;

		case 1: //벽
			player_xpos=old_xpos;
			player_ypos=old_ypos;
			break;

		case 2: //문
			printf("MISSION CLEAR\r\n");
			nFSM=2;
			break;

		case 4:
			if(player_inven ==1) {
				setColor(33,40);
				printf("CONGRAT!!!MISSION CLEAR\r\n");
				nFSM=2;
				setColor(0,0);
				

			}

			else {
				printf("-----------------it's locked! Need KEY\r\n");
				player_xpos=old_xpos;
				player_ypos=old_ypos;
			}
			break;

		case 5:
			setColor(34,40);
			printf("키를 얻었다 \r\n");
			player_inven = 1;
			setColor(0,0);	
			

			break;


	}



	/*	if(buffer_map[player_xpos+player_ypos*8]==0) {
		}
		else {
			player_xpos=old_xpos;
			player_ypos=old_ypos;
		}
	*/
		if(player_inven==1) {
			buffer_map[key_xpos+key_ypos*8]=0;
		}

 			
		buffer_map[player_xpos + player_ypos*8]=3;
		
		

	    	


}

#endif
