#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid;

void *doSomething(void *arg)
{
	int nCount=0;
	while(1)
	{
		printf("%d sec\r",nCount);

		//puts("test");
		sleep(1);
		nCount++;
	}
	return NULL;
}

int main()
{
	int err;
	err = pthread_create(&tid,NULL,&doSomething,NULL);
	if(err != 0) {
		printf("\r\n cannot create thread : [%s] \r\n",strerror(err));

	}
	else {
		printf("\r\n sucessfully built!\r\n");
	}
	
	char ch = getchar();

	//doSomething(NULL);
	printf("u press %c key \r\n", ch);

	return 0;
}
