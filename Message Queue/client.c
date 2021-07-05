#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

key_t upKeyID, downKeyID; // the key of the Queue
int upMsgQID, downMsgQID;
int sendValue, recValue;

struct msgbuff // the message format
{
    long mtype;
    char mtext[256];
};

int main()
{
    /********************Message Queue***********************/

    // create keys for the message queue
    upKeyID = ftok("keyfile", 'U');
    downKeyID = ftok("keyfile", 'D');

    // get the message queues
    upMsgQID = msgget(upKeyID, 0666 | IPC_CREAT);     //create messageSend queue and return id
    downMsgQID = msgget(downKeyID, 0666 | IPC_CREAT); //create messageSend queue and return id

    if (upMsgQID == -1 || downMsgQID == -1) // if messageSend id == -1, it faliled to create the queue
    {
        perror("Error in create");
        exit(-1);
    }
    else
    {
        printf("Client-Server messageSend Queue ID = %d\n", upMsgQID);
        printf("Server-Client messageSend Queue ID = %d\n", downMsgQID);
    }

    /********************Main Loop***********************/
    struct msgbuff messageSend;
    struct msgbuff messageReceived;
    //  header
    int processId = getpid();
    messageSend.mtype = processId % 10000;
    printf("process id = %d, messageSend type = %d\n", processId, messageSend.mtype);
    while (1)
    {
        // get the message from the user
        printf("\nMessage to be sent: ");
        fgets(messageSend.mtext, 256, stdin);

        // send the value to the server
        sendValue = msgsnd(upMsgQID, &messageSend, sizeof(messageSend.mtext), !IPC_NOWAIT);

        if (sendValue == -1)
            perror("Errror in send");
        else
        {
            recValue = msgrcv(downMsgQID, &messageReceived, sizeof(messageReceived.mtext), messageSend.mtype, !IPC_NOWAIT);

            if (recValue == -1)
                perror("Error in receive");
            else
            {
                // print the message
                printf("\nMessage received: %s\n", messageReceived.mtext);
            }
        }
    }
    return 0;
}
