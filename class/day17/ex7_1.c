#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <math.h>
#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "packet.h"

typedef struct _S_PACKET_BASE {
	unsigned short header;
	unsigned short req_type;
} _S_PACKET_BASE;

typedef struct _S_PACKET_REQ_SETPOS {
	_S_PACKET_BASE m_base;
	unsigned int index;
	float m_fxpos;
	float m_fypos;
} _S_PACKET_REQ_SETPOS;

typedef struct _S_PACKET_REQ_GETPOS {
	_S_PACKET_BASE m_base;
	unsigned int m_nIndex;
} _S_PACKET_REQ_GETPOS;




typedef struct _S_PACKET_RCV_POS {
	unsigned short header;
	unsigned short m_nIndex;
	float m_fxpos;
	float m_fypos;
	char words;

} _S_PACKET_RCV_POS;


pthread_t tid;
int bLoop =1;

int socket_desc;
char read_buffer[2000];

void *InputThread(void *arg)
{
	while(1)
	{

		
		_S_PACKET_REQ_GETPOS packet_req_getpos = {{1004,201},0};

		if(send(socket_desc,
					&packet_req_getpos,
					sizeof(packet_req_getpos),0) < 0) {
			puts("send failed");
		}
		puts("send success");

		if(recv(socket_desc,read_buffer,2000,0) < 0) {
			puts("recv failed");
		}

		_S_PACKET_RCV_POS *recv_pos = (_S_PACKET_RCV_POS *)read_buffer;

		printf("%d , %d ,%f,%f \r\n",recv_pos->header,recv_pos->m_nIndex,
				recv_pos->m_fxpos,
				recv_pos->m_fypos);


		sleep(1);

	}
	return NULL;
}


int main()
{
	{
		int err = pthread_create(&tid,NULL,&InputThread,NULL);
		if(err != 0) {
			printf("err : %s \r\n",strerror(err));
		}
		else {
			printf("thread create success \r\n");
		}
	}

	struct sockaddr_in server;

	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1)
	{
		puts("err create socket");
	}
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	if(connect(socket_desc,(struct sockaddr *)&server,sizeof(server)) < 0) {
		puts("connect error");
		return 1;
	}


	return 0;

}
