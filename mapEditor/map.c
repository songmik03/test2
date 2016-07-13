#include <stdio.h>
#include <stdlib.h>

#include "map.h"

char Default_Tilepalette[] = {
	'.', //0
	'#', //1
	'@', //2
	'+', //3
	'=', //4
	'^', //5
	'<', //6
	'>', //7
	'|', //8
	'-', //9
	'*'}; //10

void map_init(_S_MAP_OBJECT *pObj)
{
	pObj->m_pBuf = NULL;
}

void map_dump(_S_MAP_OBJECT *pObj,char *pTile_pal)
{
/*	putTile(0,pObj->m_header.m_nHeight,0,pObj->m_header.m_nWidth,pObj->m_header.m_nWidth,pObj->m_pBuf, pTile_pal);
*/
	for(int iy=0;iy<pObj->m_header.m_nHeight;iy++) {
			for(int ix=0;ix<pObj->m_header.m_nWidth;ix++) {
				putchar(pTile_pal[pObj->m_pBuf[iy*pObj->m_header.m_nWidth + ix]]);
			}
			printf("\r\n");
	}
}

void map_new(_S_MAP_OBJECT *pObj, int nWidth, int nHeight)
{
	int nSize =nWidth * nHeight;
	if(pObj->m_pBuf != NULL) {free(pObj->m_pBuf);}

	pObj->m_header.m_nWidth= nWidth; //atoi(strtok(NULL," "));
	pObj->m_header.m_nHeight= nHeight; //atoi(strtok(NULL," "));
	pObj->m_pBuf = malloc(nSize);

	for(int i=0;i<nSize;i++) {
		pObj->m_pBuf[i] = 0;
	}
}

void map_put(_S_MAP_OBJECT *pObj, int x, int y, int nTileIndex)
{
	pObj->m_pBuf[y*pObj->m_header.m_nWidth+x] = nTileIndex;
}

//0:성공
//1:실패
int map_save(_S_MAP_OBJECT *pObj,char *filename)
{
	FILE *pf = fopen(filename,"wb");

	fwrite(&(pObj->m_header),sizeof(pObj->m_header),1,pf);
	int nSize = pObj->m_header.m_nHeight*pObj->m_header.m_nWidth;
	fwrite(pObj->m_pBuf,nSize,1, pf);

	fclose(pf);	
	return 0;
}

int map_load(_S_MAP_OBJECT *pObj, char *filename)
{
	FILE *pf = fopen(filename,"rb");

	fread(&(pObj->m_header),sizeof(_S_MAP_HEADER),1,pf);

	if(pObj->m_pBuf) {
		free(pObj->m_pBuf);
	}
	int nSize = pObj->m_header.m_nHeight * pObj->m_header.m_nWidth;
	pObj->m_pBuf = malloc(nSize);
	fread(pObj->m_pBuf,nSize,1,pf);
	
	for(int i=0;i<nSize;i++) {
		//printf("%d",pObj->m_pBuf[i]);
	}
	fclose(pf);
	return 0;
}
void map_drawTile(_S_MAP_OBJECT *pObj, int xpos, int ypos, _S_MAP_OBJECT *pTarget)
{
	for(int iy=0;iy <pObj->m_header.m_nHeight;iy++) {
		for(int ix=0;ix<pObj->m_header.m_nWidth;ix++) {
			map_put(pTarget,ix+xpos,iy+ypos,pObj->m_pBuf[iy*pObj->m_header.m_nWidth +ix]);
		}
	}
}
void map_drawTile_mirror_h(_S_MAP_OBJECT *pObj, int xpos, int ypos, _S_MAP_OBJECT *pTarget)
{
	for(int iy=0;iy <pObj->m_header.m_nHeight;iy++) {
		for(int ix=0;ix<pObj->m_header.m_nWidth;ix++) {
			map_put(pTarget,xpos-ix,iy+ypos,pObj->m_pBuf[iy*pObj->m_header.m_nWidth +ix]);
		}
	}
}
void map_drawTile_mirror_v(_S_MAP_OBJECT *pObj, int xpos, int ypos, _S_MAP_OBJECT *pTarget)
{
	for(int iy=0;iy <pObj->m_header.m_nHeight;iy++) {
		for(int ix=0;ix<pObj->m_header.m_nWidth;ix++) {
			map_put(pTarget,xpos+ix,ypos-iy,pObj->m_pBuf[iy*pObj->m_header.m_nWidth +ix]);
		}
	}
}
void map_drawTile_trn(_S_MAP_OBJECT *pObj, int xpos,int ypos,_S_MAP_OBJECT *pTarget)
{
	for(int iy=0;iy <pObj->m_header.m_nHeight;iy++) {
		for(int ix=0;ix<pObj->m_header.m_nWidth;ix++) {
			int nPixel = pObj->m_pBuf[iy*pObj->m_header.m_nWidth + ix];

			if(nPixel != 0) {
				map_put(pTarget,ix+xpos,iy+ypos, pObj->m_pBuf[iy*pObj->m_header.m_nWidth + ix]);
			}
		}
	}

}