//
// kuchynskiandrei@gmail.com
// 2020
//

#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define ADDRESS "127.0.0.1"
#define PORT 1001 // порт сервера для связи свой клиент получит от ОС автоматически

#define SOCK_TYPE	SOCK_DGRAM
//#define SOCK_TYPE	SOCK_STREAM // tcp

void main()
{
	uint8_t msg[1000] = {0x34, 0x34, 0x34, 0x38};
	int socketfd;
	struct sockaddr_in server_addr;
	int i;
	
	if((socketfd = socket(PF_INET, SOCK_TYPE, 0)) < 0) {
		perror("Socket error: "); 
		return;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	inet_aton(ADDRESS, &server_addr.sin_addr);
	
	for(i = 0; i < 10000000; i++) {
		int ret = sendto(socketfd, msg, sizeof(msg), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
		if(ret < 0) {
			perror("Send error:"); 
			break;
		}
	}
	
	close(socketfd);
}
