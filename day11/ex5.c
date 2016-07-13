#include <stdio.h>
#include <stdlib.h>

#include "../mapEditor/map.h"


int main()
{
	_S_MAP_OBJECT screenBuf;
	map_init(&screenBuf);

	map_new(&screenBuf,16,16);

	map_put(&screenBuf,5,5,1);
	map_put(&screenBuf,4,5,1);
	map_put(&screenBuf,3,5,1);

	
	_S_MAP_OBJECT humanObj;
	map_init(&humanObj);

	map_load(&humanObj,"human.dat");
	puts("\r\n---------------------\r\n");
	//map_drawTile(&humanObj, 5, 5, &screenBuf);
	//map_drawTile_mirror_h(&humanObj,5,5,&screenBuf);
	//map_drawTile_mirror_v(&humanObj,5,5,&screenBuf);
	
	map_drawTile_trn(&humanObj,5,5,&screenBuf);
	map_dump(&screenBuf,Default_Tilepalette);

	return 0;
}
