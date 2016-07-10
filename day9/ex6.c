#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char *m_szName;
	void *node[8];
}_S_AREA;

int main()
{
	_S_AREA town = {
		"town",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};
	_S_AREA dungeon_1 = {
		"dungeon-1",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};
	_S_AREA park = {
		"park",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};
	_S_AREA store = {
		"store",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};


	town.node[0] = &park;
	town.node[1] = &store;
	
	dungeon_1.node[0] = &park;
	
	park.node[0] = &town;
	park.node[1] = &dungeon_1;

	store.node[0] = &town;

	_S_AREA *pCurrentArea = &town;

	int bLoop = 1;
	system("clear");
	printf("======================================\r\n");
	printf("======================================\r\n");

	printf("캐릭터의 이름 : ");
	char pName[80];
	gets(pName);
	printf("======================================\r\n");
	printf("======================================\r\n");
	
	printf("%s는 town에 서 있습니다.\r\n",pName);
	printf("현위치 확인을 위한 명령어 : look\r\n");
	printf("이동 명령어 : move (park / store)\r\n");
	printf("끝내기 : exit\r\n");

	while(bLoop) {
		char szCmd[32];
		gets(szCmd);
		char *pTemp = strtok(szCmd," ");

		if(!strcmp(pTemp,"look")) {
			printf("++++++++++++++++++++++++++++++++++++++++\r\n");
			printf("%s는 현재 %s에 서 있습니다. \r\n",pName, pCurrentArea->m_szName);
			printf("++++++++++++++++++++++++++++++++++++++++\r\n");

			if(pCurrentArea->m_szName == "town") {
				printf("이동 가능한 지역 : store / park\r\n");	
				printf("끝내기 : exit\r\n");
			}
			else if(pCurrentArea->m_szName == "park") {
				printf("이동 가능한 지역 : town / dungeon-1\r\n");
				printf("끝내기 : exit\r\n");
			}
			else if(pCurrentArea->m_szName == "store") {
				printf("이동이 가능한 지역 : town\r\n");
			}
			else if(pCurrentArea->m_szName == "dungeon-1") {
				printf("이동이 가능한 지역 : park\r\n");
				printf("끝내기 : exit\r\n");
			}
			printf("-----------------------------------------\r\n");
		}
		else if(!strcmp(pTemp,"move")) {
			char *pszArea = strtok(NULL,"");

			printf("이동합니다. \r\n");
			for(int i=0;i<8;i++) {
				_S_AREA *pNode = pCurrentArea->node[i];
				if(pNode == NULL) break;
				//puts(pNode->m_szName);
				if(!strcmp(pNode->m_szName,pszArea)) {
					system("clear");
					printf("======================================\r\n");
					printf("======================================\r\n");

					printf("%s로 이동성공!\r\n",pszArea);
					pCurrentArea = pNode;
				}
			}
		}
		else if(!strcmp(pTemp,"exit")) {
			bLoop = 0;
		}
	}

}
