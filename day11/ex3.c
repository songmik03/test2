#include <stdio.h>
#include <stdlib.h>

#include "map.h"
int main()
{
	_S_MAP_OBJECT map_car;
	map_init(&map_car);

	char tile_palette[] = {'.','#','@','!'};

	map_load(&map_car,"car.dat");
	puts("-------load complete---------\r\n");
	//system("clear");
	map_dump(&map_car,tile_palette);
	
	return 0;
	

}
