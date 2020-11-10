client_udp: client_udp.c
	gcc -o client_udp $^
server_udp: server_udp.c
	gcc -o server_udp $^

client_tcp: client_tcp.c
	gcc -o client_tcp $^
server_tcp: server_tcp.c
	gcc -o server_tcp $^

clean: rm -f *.o
