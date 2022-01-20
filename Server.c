/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <pthread.h>

int count = -1;
void *T_echo(void *id) {
	int *socketnum=(int *)id;
	printf("received id %d \n",*socketnum);

	char server_message[2000], client_message[2000];

	if (recv(*socketnum, client_message, sizeof(client_message),0) < 0) {
            printf("Receive Failed. Error!!!!!\n");                
    }

    printf("Client Message: %s\n",client_message);

    if(strcmp(client_message, "disconnect") == 0)
    {
        if (send(*socketnum, server_message, strlen(client_message), 0) < 0)
	    {
		    printf("Send Failed. Error!!!!!\n");
		}
        printf( "disconnecting \n");
        close(*socketnum);
        count--;
        pthread_exit(NULL);
    }

    //Send the message back to client
    
    strcpy(server_message, client_message);
    if (send(*socketnum, server_message, strlen(client_message),0) < 0)
	{
		printf("Send Failed. Error!!!!!\n");        
	}
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
  
}

int main(void)
{
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;         
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;               /* Address family = Internet */
        server_addr.sin_port = htons(2000);               // Set port number, using htons function to use proper byte order */
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");    /* Set IP address to localhost */
		
		// BINDING FUNCTION
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)    // Bind the address struct to the socket.  /
	                            	//bind() passes file descriptor, the address structure,and the length of the address structure
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        //Put the socket into Listening State
        
        if(listen(socket_desc, 1) < 0)                               //This listen() call tells the socket to listen to the incoming connections.
     // The listen() function places all incoming connection into a "backlog queue" until accept() call accepts the connection.
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
        //Accept the incoming Connections
        
        client_size = sizeof(client_addr);
		
        //creating thread id
        pthread_t tid[100];
        int i = 0;
        
    while(1)
    {	
    	count++;
    	
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);          
        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return -1;
        }
       
        printf("\nSending id %d\n",client_sock);
        if (count >= 3) {
            printf("\nServer is Full. \n");
            if (send(client_sock, "full", strlen("full"), 0) < 0) {
			    printf("Send Failed. Error!!!!!\n");
			}
            return -1;
        }
        else {
           
       		pthread_create(&tid[i], NULL, T_echo, (void*)&client_sock); 
       		printf("Count of clients -> %d\n", count);
			i++;
       		
        }
        //printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		        
    }   
     	
     	//Closing the Socket
        close(socket_desc);
        return 0;       
}
