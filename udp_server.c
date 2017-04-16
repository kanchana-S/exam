//udp_server.c
#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
 //the thread function
//void *connection_handler(void *);
//int client_no=0;
 int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c,read_size;
    char client_message[2000];
    struct sockaddr_in server , client;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
   //Create socket
    socket_desc = socket(AF_INET , SOCK_DGRAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
	exit(0);
    }
    puts("Socket created");
     
   //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 5);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    //c = sizeof(struct sockaddr_in);
	//pthread_t thread_id;
	
    /*if((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))<0)
    {
	printf("Error while accepting connection");
	exit(0);
    } 
    
	//client_no++;
    printf("Connection accepted from client...!!!\n");*/ 
    //Receive a message from client
	addr_size=sizeof(serverStorage);
    while( (read_size = recvfrom(socket_desc , client_message , 2000 , 0,(struct sockaddr *)&serverStorage, &addr_size)) > 0 )
    {
        //end of string marker
	client_message[read_size] = '\0';
	
	puts(client_message);
		
		//Send the message back to client
        sendto(socket_desc , client_message , strlen(client_message),0,(struct sockaddr *)&serverStorage, addr_size);
		
		//clear the message buffer
		memset(client_message, 0, 2000);
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
  //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        //puts("Handler assigned");
     
    /*if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }*/
     
    return 0;
}
