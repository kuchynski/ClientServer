//
// kuchynskiandrei@gmail.com
// 2020
//

#include <sys/socket.h> 
#include <resolv.h> 
#include <arpa/inet.h>
#include <unistd.h> 
#include <stdint.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <errno.h>

#define ADDRESS "127.0.0.1"
#define PORT 1002

#define SOCK_TYPE	SOCK_STREAM

void main()
{
	int i, len, msg_count = 0;
	int socketfd, connfd;
	struct sockaddr_in server_addr, client_addr; 
	int addr_size = sizeof(client_addr);

	if((socketfd = socket(PF_INET, SOCK_TYPE, 0)) < 0) { 
		perror("socket error: "); 
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT); 
	//server_addr.sin_addr.s_addr = INADDR_ANY; //htonl()
	inet_aton(ADDRESS, &server_addr.sin_addr);

	if(bind(socketfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
		perror("bind error: "); 
		close(socketfd);
		return; 
	}

	if(listen(socketfd, 1000) != 0) {
		perror("listen error: "); 
		close(socketfd);
		return; 
	}
	
	len = sizeof(client_addr);
	connfd = accept(socketfd, (struct sockaddr*)&client_addr, &len);
	if(connfd < 0) {
		perror("accept error: "); 
		close(socketfd);
		return; 
	}
	
	for(i = 0; i < 1000000000; i++) {
		uint8_t msg[100]; 
		int msg_size;

		msg_size = recv(connfd, msg, sizeof(msg), 0);
		if(msg_size <= 0) {
			break;
		}
		if(msg_size) {
			msg_count += msg_size;
			//printf("Message: %d %s\n", msg_size, msg); 
		}
	}
	close(socketfd);
	printf("done: %d\n", msg_count);
}


