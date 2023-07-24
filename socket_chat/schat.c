#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h> //atoi
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <poll.h>

int main(int argc, char *argv[]) {
	int connection;
	if(argc < 3){
		int port;
		if(argc == 1){
                	// start by getting a random port from the ephemeral port range
                	srandom(getpid()); // random seed based on this process's OS-assigned ID
                	port = 0xc000 | (random()&0x3fff); // random element of 49152–65535
                }else{
                	port = atoi(argv[1]);//otherwise set the port to given value
                }
                printf("Port: %d\n", port);
		
		//construct the sockaddr_in struct that will store our connection information
		struct sockaddr_in ipOfServer;
        	memset(&ipOfServer, 0, sizeof(struct sockaddr_in));
        	ipOfServer.sin_family = AF_INET;
        	ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
        	ipOfServer.sin_port = htons(port);
		//set up the listener
		int listener = socket(AF_INET, SOCK_STREAM, 0);			
		bind(listener, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));
		listen(listener, 20);
	
		system("host $HOSTNAME");
		printf("The system is now listening on %d\n", port);
		printf("Waiting for a connection... \n");
		//only listen once on our server	
		connection = accept(listener, (struct sockaddr*)NULL, NULL);
        	close(listener);		
	}else if(argc == 3){
	        const char *ip = argv[1];
                puts(ip);
                int port = atoi(argv[2]);
                printf("Port: %d\n", port);
		//create socket. Check if error occured
		connection = socket(AF_INET, SOCK_STREAM, 0);
                if(connection < 0){
                        perror("ERROR creating socket");
                        return 1;
                }
		
		//connect to remote server
		struct sockaddr_in server_address;
                memset(&server_address, 0, sizeof(server_address));
                server_address.sin_family = AF_INET;
                server_address.sin_port = htons(port);
                if (inet_pton(AF_INET, ip, &server_address.sin_addr) <= 0) {
                        perror("Error converting IP");
                        close(connection);
                        return 1;
                }
		//check if the connection worked, this will also set connection to our connected socket
                if (connect(connection, (struct sockaddr *)&server_address, sizeof(server_address))<0){
                        perror("error connecting to server");
                        close(connection);
                        return 1;
                }				
	}else{
		puts("too many arguments. Invalid inputs");
		return -1;
	}
	
        //set up our pollfd socket, this is what our poll() function will need to run
	struct pollfd fds[2];
        fds[0].fd = STDIN_FILENO;
        fds[0].events = POLLIN;
        fds[1].fd = connection;
        fds[1].events = POLLIN;
	//forevewr loop and for both the server and the client poll bot the connection and stdout
      	for(;;){
        	int ret = poll(fds, 2, 60000);
                if (fds[0].revents & POLLIN) {
                        char stdBuffer[4096];
                        ssize_t bytes_read = read(STDIN_FILENO, stdBuffer, 4096);
                        if (bytes_read > 0){
                                write(connection, stdBuffer, bytes_read);
                        }
                }

                if (fds[1].revents & POLLIN) {
                        char otherBuffer[4096];
                        ssize_t bytes_in = read(connection, otherBuffer, 4096);
                        if (bytes_in > 0) {
                                write(STDOUT_FILENO, otherBuffer, bytes_in);
                        }
                }

        }
	//polite
	close(connection);
	return 0; 
} 

                                                                                                                                                                            
