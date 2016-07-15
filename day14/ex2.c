#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _S_ITEM_ {
	
	char m_szName[32];

	int m_nType;
	int m_nValue;

} _S_ITEM_;

_S_ITEM_ item_list[] = {

	{"short sword",0,10},
	{"wood shild",0,5},
	{"dagger",0,6},
	{"sling",0,3},
	{"stuff",0,7}
};


_S_ITEM_*findItem(const char *szName)
{//아이템 이름을 넣어주면->그 아이템의 포인터를 반환해주는 함수

	int item_list_length = sizeof(item_list)/sizeof(_S_ITEM_);
	for(int i=0;i<item_list_length;i++) 
	{
		_S_ITEM_ *pitem = &(item_list[i]);

		if(strcmp(szName,pitem->m_szName)==0)
		{
			return pitem;
		}

	}
}

unsigned long getHashCode(const char *szStr)
{
	int nLength = strlen(szStr);
	
	int nHash = 5381;

	for(int i=0;i<nLength;i++) {
		//printf("%d \r\n", szStr[i]);	
		//nHash += szStr[i];
		int c = szStr[i];
		nHash = ((nHash<<5) + nHash) + c;
	}
	return nHash;
}

int main()
{

	printf("%d %d\r\n", getHashCode("staff"),getHashCode("steff"));
	/*
	//_S_ITEM_ *pitem = findItem("stuff");
	//printf("%s %d \r\n", pitem->m_szName,pitem->m_nValue);
	
	printf("%d %d\r\n",getHashCode("stuff"),getHashCode("step"));

	if(getHashCode("staff") == getHashCode("stepp")) {
		puts("같은 문장입니다\r\n");
	}
	else {
		puts("diff\r\n");
	}

	*/


	return 0;
}
