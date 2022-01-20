# TCP-Socket-Programming-using-Multithreaded-Server
Multithreaded ECHO server using TCP  

You are required to design a Multi-Threaded Echo Server and a Simple client. The server uses a TCP protocol to connect to clients. Server will be listening for clients to connect to it and as soon as a client connects, it assigns a separate thread for further processing. The thread will be responsible to receive the data from the client and echo it to the client until the client sends the "DISCONNECT" command. The server can handle maximum 3 clients at a time. 
Client will be a simple program which after connecting to the server will take the input from the user and send it to the server, then outputs the response on the terminal received from the server. It will do the same until user enters “DISCONNECT”. Upon entering “DISCONNECT” the client shall close the socket and exit.
Following are the steps which Server should perform:
1.	Receives a connection request from client and pass the socket descriptor returned by the accept() to the thread and goes back to listen for more connections for clients< 4. If the fourth client tries to connect then server sends the client message that “Server Full”

2.	Meanwhile this is what the thread do
o	Receive what the client sends.
o	Echo back what client sends.
o	If client has sent “DISCONNECT” then close the socket and quit.

3.	Receive more data from the same client.
You should cater 3multiple clients that will be sending connection requests to server.
Following are the steps which Clients should perform:
1.	Take input from the user.
2.	Send input to the server
3.	If input is “DISCONNECT” then close the socket and exit otherwise continue to step 4.
4.	Wait for server’s response.
5.	Print the server’s repose.
6.	Go back to step 1.
