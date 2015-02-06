/*
    C socket server example, handles multiple clients using threads
    Compile
    gcc server.c -lpthread -o server
*/
 
#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread
#include "global_data.h"
#include "measure_data_type.h"
#include "debug_output.h"

typedef struct thread_data_s {
    struct sockaddr_in client_sockaddr;
    uint32_t client_sock;
} thread_data_t;

//the thread function
void *connection_handler(void *);
void *socket_server_func(void*);
 
void *socket_server_func(void*)
{
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;
    thread_data_t thread_data;
     
    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        ERROR("Could not create socket");
    }
    NOTICE("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;    //fixed address
    server.sin_port = htons(server_port);
     
    //Bind
    if(bind(socket_desc,(struct sockaddr*)&server, sizeof(server)) < 0)
    {
        //print the error message
        ERROR("bind failed. Error");
        return NULL;
    }
    NOTICE("bind done");
     
    //Listen, accept maximum 5 client connections
    listen(socket_desc , 5);
     
    //Accept and incoming connection
    NOTICE("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
     
    //Accept and incoming connection
    NOTICE("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	
    while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        NOTICE("Connection accepted");
        thread_data.client_sockaddr = client;
        thread_data.client_sock = client_sock;
         
        if(pthread_create(&thread_id, NULL,  connection_handler, (void*) &thread_data) < 0)
        {
            ERROR("could not create thread");
            return NULL;
        }
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        NOTICE("Handler assigned");
    }
     
    if (client_sock < 0)
    {
        ERROR("accept failed");
        return NULL;
    }
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *thread_data_ptr)
{
    thread_data_t thread_data = *(thread_data_t*)thread_data_ptr;
    //client ip address
    uint32_t client_addr = thread_data.client_sockaddr.sin_addr.s_addr;
    //Get the socket descriptor
    uint32_t sock = thread_data.client_sock;
    int read_size;
    char client_message[2000];
     
    //Receive a message from client
    while((read_size = recv(sock, client_message, 2000, 0)) > 0)
    {
        //end of string marker
		client_message[read_size] = '\0';
        //sampled_record from switch
        sampled_record_t sampled_record = *((sampled_record_t*)client_message);
        
        /*set the data*/
        insert_sampled_record_into_map(client_addr, sampled_record);
		
		//clear the message buffer
		memset(client_message, 0, 2000);
    }
     
    if(read_size == 0)
    {
        NOTICE("Client disconnected");
    }
    else if(read_size == -1)
    {
        NOTICE("recv failed");
    }

    //finish receiving data from the client, insert the client_addr into client_set
    client_set.insert(client_addr);
         
    return 0;
}
