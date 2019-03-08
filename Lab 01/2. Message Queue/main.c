
/**
 * P15/1725/2016
 * Abiud Orina
 * 
 * - A program to implement a simple message queue 
 * 
 * 
 * Method
 * Fork 5 processes
 *  if the process is the first one, write something to the message queue
 *  the other processes can read and write and the last one can close the message queue
 * 
 * */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>


//structure to implement message
struct mesg_buffer{
    long mesg_type;
    char mesg_text[100];
}message;


int main()
{
    key_t key; //key shared by processes in order to gain access to the message queue
    pid_t pid;
    int msgid;
    time_t rawtime;
    struct tm * timeinfo;
    char msg[100];
    int i=0;
    int msgflg=0; //action to be taken if the no of bytes in the queue is already equal to  msg_qbytes
                    //the total no of msg on all queues is equal to system imposed limit

    printf("\t_____________________________\n");
    printf("\tMessage Queue implementation\n");
    printf("\t_____________________________\n");

    while(i<5){
        pid = fork(); //creating a child process

        //error occurred
        if(pid<0){
            sprintf(stderr,"Error occurred \"Fork \"");
            return 1;
        }

        //child process
        if(pid==0){
            printf("\n\tprocess %d :\n",getpid());

            struct mesg_buffer{
                long mesg_type;
                char mesg_text[100];
            }message;

            key=ftok(".", 65); //converts a file name to a key value that is unique within the system
            message.mesg_type = 1;
            msgid = msgget(key,IPC_CREAT|0666); //creates a new message queue and returns its identifier

            if(i==0){
                /*write to queue*/
                printf("\t\tWrite something to MQ\n\t\tMSG: ");
                gets(msg);
                sprintf(message.mesg_text,"%s sender: %d",msg,getpid());

		//appends a copy of the message pointed to by &message to the message queue identified by msgid               
		if(msgsnd(msgid,&message, sizeof(message),0)==-1){
                    printf("error by msgsnd()\n");
                }

                exit(0);
            }

            /*read from queue*/
	    //removes message from the msg queue and places it in the buffer pointed to by &mess
            if(msgrcv(msgid,&message, sizeof(message),1,0)<0){
                printf("Error by msgrcv()\n");
                exit(1);
            }
            printf("\t\tprocess %d read ( %s )\n",getpid(),message.mesg_text);

            /*write to queue*/
            printf("\t\tWrite something to MQ\n\t\tMSG: ");
            gets(msg);
            sprintf(message.mesg_text,"%s sender: %d",msg,getpid());
            msgsnd(msgid,&message, sizeof(message),0);
            exit(0);
        }

        //parent process
        else{
            wait(NULL);
        }

        i++;
    }


    //performes control operation specified by cmd
    //IPC_RMID ensures immediate removal of the message queue awakening all waiting reader and writer processes
    msgctl(msgid, IPC_RMID,NULL);
    printf("\nQueue deleted");

    return 0;
}


