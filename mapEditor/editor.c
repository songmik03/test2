#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../engine/engine2d.h"
#include "map.h"

_S_MAP_OBJECT MapObject;

//-----------------------------------------------------------
int main() 
{
	int bLoop=1;

	MapObject.m_header.m_nSkima = 1;
	MapObject.m_pBuf = NULL;	
	//char TilePalette[] = {'.','#','@','%'};
	puts("text TileMap Editor v1.1");

	while(bLoop)
	{
		char szCmd[32];
		gets(szCmd);
		char *pTemp = strtok(szCmd," ");

		if(!strcmp(pTemp,"exit")) {
			bLoop=0;
			if(MapObject.m_pBuf) {
				free(MapObject.m_pBuf);
			}
		}
		else if(!strcmp(pTemp, "dump")) {
			map_dump(&MapObject,Default_Tilepalette);
		}
/////////////////////////////////////////////////////////////////

		else if(!strcmp(pTemp,"new")) {
			//new 8 4

			int nWidth = atoi(strtok(NULL," "));
			int nHeight = atoi(strtok(NULL," "));
			map_new(&MapObject,nWidth,nHeight);
		}
		else if(!strcmp(pTemp,"put")) {
			//put x y 1(tile_index)
			int x,y,tile_index;

			x = atoi(strtok(NULL, " "));
			y = atoi(strtok(NULL," "));
			tile_index = atoi(strtok(NULL," "));
			
			map_put(&MapObject,x,y,tile_index);	
					 
		}
		else if(!strcmp(pTemp,"hline")) {
			//hline 1 1
							
			int xpos,tile_index;

			xpos = atoi(strtok(NULL," "));
			tile_index = atoi(strtok(NULL," "));
			
			for(int iy=0;iy<MapObject.m_header.m_nHeight;iy++) {
				MapObject.m_pBuf[iy*MapObject.m_header.m_nWidth+xpos] = tile_index;
			}
		}
		else if(!strcmp(pTemp,"vline")) {
			//vline 1 1
			
			int ypos, tile_index;

			ypos = atoi(strtok(NULL," "));
			tile_index = atoi(strtok(NULL," "));

			for(int ix=0;ix<MapObject.m_header.m_nWidth;ix++) {
				MapObject.m_pBuf[ix+ypos*MapObject.m_header.m_nWidth] = tile_index;
			}
		}
/////////////////////////////////////////////////////////////////
		
		else if(!strcmp(pTemp,"save")) {
			//save filename
			
			char *pTemp = strtok(NULL," ");
			map_save(&MapObject,pTemp);
				
			puts("saved!");
		}
		else if(!strcmp(pTemp,"load")) {
			//load filename
			char *pTemp = strtok(NULL," ");
			map_load(&MapObject,pTemp);

			puts("loaded!");
		}
/////////////////////////////////////////////////////////////////
		
		else if(!strcmp(pTemp,"tridraw_1")) {
			//tridraw_1 1(tile_index)
			int tile_index = atoi(strtok(NULL," "));
			int nHeight = MapObject.m_header.m_nHeight;
			int nWidth = MapObject.m_header.m_nWidth;

			for(int iy=0;iy<nHeight;iy++) {
				for(int ix=0;(ix<iy && ix<nWidth);ix++) {

					MapObject.m_pBuf[ix+iy*nWidth] = tile_index;
				}
			}
		}
		else if(!strcmp(pTemp,"draw_cross")) {
			//draw_cross 1 2 1 (x y tile_index)
			int xpos = atoi(strtok(NULL," "));
			int ypos = atoi(strtok(NULL," "));
			int tile_index = atoi(strtok(NULL," "));
			int nWidth = MapObject.m_header.m_nWidth;

			MapObject.m_pBuf[xpos+ypos*nWidth] = tile_index;
			MapObject.m_pBuf[(xpos+1)+ypos*nWidth] = tile_index;
			MapObject.m_pBuf[(xpos-1)+ypos*nWidth] = tile_index;
			MapObject.m_pBuf[xpos+(ypos+1)*nWidth] = tile_index;
			MapObject.m_pBuf[xpos+(ypos-1)*nWidth] = tile_index;

			

		}



	}

	return 0;
}
