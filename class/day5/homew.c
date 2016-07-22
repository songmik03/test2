#include <stdio.h>

int main()
{
	char cmd;
	int bLoop;
	char buffer[64];

	char *pBuff;

	pBuff = buffer;

	int nTailIndex =0;
	int headIndex =0;
	

	printf(" %d %d \r\n",*pBuff, buffer);
	
	for(int i=0; i<64; i++) {  //버퍼 0으로 초기화
		buffer[i] = 0;
	}

	bLoop=1;
	while(bLoop) {
		
		scanf("%c", &cmd);
		getchar();

		switch(cmd) {
			case 'a'://add
			printf("what :");
			scanf("%c",&cmd);
			getchar();

			pBuff[nTailIndex]=cmd;
			nTailIndex++;
			break;

			case 'd'://delete
			nTailIndex--;
			pBuff[nTailIndex] = 0x00;
			break;

			case 'f'://앞에서 부터 지우기
			for(int i=0;i<nTailIndex-1;i++) {
				pBuff[i]=pBuff[i+1];
			}
			nTailIndex--;
			pBuff[nTailIndex]=0x00;
			
			break;

			case 's':
			printf("%s \r\n",pBuff);
			break;

			case 'q':
			printf("quit \r\n");
			bLoop=0;
			break;
		}

	}




	return 0; 
}
