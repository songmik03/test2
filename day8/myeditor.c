#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myeditor.h"

int main()
{
	puts("myeditor version 1.0");

	_S_STR_LINE *pHeader = NULL;

	int bLoop = 1;

	while(bLoop)
	{
		char *pTemp;
		char strCmd[128];
		gets(strCmd);
	

		pTemp = strtok(strCmd," ");

		if(!strcmp(pTemp,"exit")) {
			bLoop=0;
		}
		else if(!strcmp(pTemp,"push")) {
			//push 원하는 문자열
			pTemp = strtok(NULL," ");
			
			char *pstr = (char *)malloc(strlen(pTemp)+1);
			strcpy(pstr,pTemp);
			
			_S_STR_LINE *pLine = (_S_STR_LINE *)malloc(sizeof(_S_STR_LINE));
			pLine->m_szStr = pstr;
			pLine->m_pNext = NULL;
			if(pHeader == NULL) {
				pHeader = pLine;
			}
			else {
				//끝까지 찾아들어가기
				_S_STR_LINE *pNext =(_S_STR_LINE *)pHeader;

				while(pNext != NULL) {
					//마지막이라면...
					if(pNext->m_pNext == NULL) {
						pNext->m_pNext =pLine;
						pNext = NULL;

					}
					else {
						//더 있다면...
						pNext = pNext->m_pNext;
					}
				}
			}

		}
		else if(!strcmp(pTemp,"pop")) { //day5/ex12.c 지우기

		}
		else if(!strcmp(pTemp,"del")) {
			_S_STR_LINE *_pGarbage = pHeader;
			pHeader = pHeader->m_pNext;

			free(_pGarbage->m_szStr);
			free(_pGarbage);
			
		}
		else *pHeader if(!strcmp(pTemp,"ins")) {
			//ins 2 hello --문법
			int nIndex = atoi(strtok(NULL, " "));
			pTemp = strtok(NULL," ");
			printf("line %d, %s 추가 \r\n",nIndex, pTemp);
			
		}
		else if(!strcmp(pTemp,"rm")) {
			//rm 2 --문법
			int nIndex = atoi(strtok(NULL, " "));

		}
		else if(!strcmp(pTemp,"set")) {
			//set 1 new string
			int nIndex = atoi(strtok(NULL," "));
		}

		else if(!strcmp(pTemp,"dump")) {
			
			puts("======================");
			_S_STR_LINE *pLine = pHeader;

			while(pLine != NULL) {

				puts(pLine->m_szStr);
				pLine = pLine->m_pNext;
			}
			
			puts("======================");
		}

	}

	return 0;
}
