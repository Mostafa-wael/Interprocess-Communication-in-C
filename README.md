# Interprocess-Communication-in-C
Message Queues
---
Two processes: client and server, communicate via two message queues "Up" and "Down".
1. The client reads a message from the standard input and sends it to the server via the Up
queue, then waits for the server's answer on the Down queue. The server is specialized
in reversing strings. Therefore, if the client sends the message "Hello World" via the Up message
queue, the server will read the message, reverse it, and send "dlroW olleH" via the
Down queue. When the client receives the message from the server, it prints it out, assuming the maximum size of any message is 256 bytes.
2. Multiple clients are be able to connect to the up and down queues. However, what
happens if one client puts a message to reverse on the system and another client is
waiting for its response from the queue.this is handled using “typed messages”. Each client has a particular client number
based on the last 4 digits of its process ID. This 4- digit numberis used as the client
identifier and is the message type so that each client can always be sure to receive
the message that it is waiting on to be converted.
3. The server and client are running forever using a while loop, however you can
terminate the program using CTRL+C (SIGINT).

Shared Memory & Semaphores
---
Replicate the previous code but using shared memory and semaphores ONLY. 
1. The client reads a message from the standard input and writes it to the shared memory
where it will be reversed by the server. When the server is done with reversing the string,
the client prints the reversed string.
2. The serveris able to handle up to N clients simultaneously. (N can be any arbitrary number of clients).
3. The server and client are running forever using a while loop, however you can
terminate the program using CTRL+C (SIGINT). 
