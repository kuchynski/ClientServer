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
#define PORT 1001

#define SOCK_TYPE	SOCK_DGRAM
//#define SOCK_TYPE	SOCK_STREAM //tcp

void main()
{
	int i;
	uint8_t msg[10000]; 
	int msg_size;
	int socketfd, newsockfd;
	struct sockaddr_in server_addr, client_addr; 
	int addr_size = sizeof(client_addr);

	if((socketfd = socket(PF_INET, SOCK_TYPE, 0)) < 0) { 
		perror("socket error: "); 
		return;
	}

	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(PORT); 
	//server_addr.sin_addr.s_addr = INADDR_ANY;
	inet_aton(ADDRESS, &server_addr.sin_addr);

	if(bind(socketfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) { 
		perror("bind error: "); 
		return; 
	}
	
	for(i = 0; i < 10000000; i++) {
		msg_size = recvfrom(socketfd, msg, sizeof(msg), 0, (struct sockaddr*)&client_addr, &addr_size);
		if(msg_size <= 0) {
			printf("error %d\n", errno);
			break;
		}
		//printf("Message: %d\n", msg_size); 
		//printf("Client:\n"); 
		//for(i = 0; i < msg_size; i++) 
		//	printf("%dn", msg[i]); 
	}
	close(socketfd);
}


