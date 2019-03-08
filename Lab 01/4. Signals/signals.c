/********************************************************************************************
*P15/1725/2016
*NYAGESOA ABIUD ORINA
********************************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <string.h>
#include <time.h>
#include <signal.h>


//Code for signal handler
void signalHandler(int sig){
     //There is a zombie child waiting
     //check
     //signal(sig, SIG_IGN);
     printf("Child Process: %d is done\n",getpid());
     exit(0);
}
/* Code for the chi;d process*/
void  ChildProcess(int wfd,int x,int a,int b){
        
     int ans=a+b;
     if(write(wfd,&ans,sizeof(ans))>0){
          printf("Child write successful\n");
     }
     
     for (int i = 0;; i++)
        {
             sleep(1);
        }
        exit(0);
}

int main(void)
{    
     printf("\n----------------Parent Process Executing...---------------\n");  

     pid_t  pid;

     //Install the signal handler
     //signal(SIGUSR1, signalHandler);

     //Declare int of file descriptors.
     int fd[2],fd2[2]; 
     for (int i = 0; i < 10; ++i)
     {
               /**
                    Create pipes for the two sets of file descriptors
                    Create a new child process using the fork() system call
                    Check if the piping was successful
               e*/

          if (pipe(fd) <0 )
          {
               perror("Failed to allocate pipes\n");
               exit(EXIT_FAILURE);
               }

               if (pipe(fd2)<0)
               {
               perror("Failed to allocate pipes\n");
               exit(EXIT_FAILURE);
          }
          
          pid = fork(); //Spawn child process

          if (pid<0){
               printf("Failed to fork process!\n");
               exit(EXIT_FAILURE);
          }

          else if (pid == 0){
               printf("\n----------------Child Process Executing...---------------\n");  
               /**
                    Means that the forked process is a child process
                    Close all the file descriptors that we don't need
                    Initialize a buffer array of type char
                    Read data from the pipe and check if any data 
                    was read
               */
               signal(SIGQUIT, signalHandler);
               close(fd[0]);
               close(fd2[1]);
               char buf;
               int a,b;
               if(read(fd2[0],&a,4)>0&&read(fd2[0],&b,4)>0){
                    printf("Child read %d and %d\n",a,b);
               }
               else{
                    perror("Child failed to read data!\n");
                    exit(EXIT_FAILURE);
               }
               /*
               Display the read data
               Close all the file descriptors that we used then...
               Call the child process to execute its code
               */
               //write(fd[1],"The answer is :",sizeof("The answer is :"));

               close(fd2[0]);
               ChildProcess(fd[1],i,a,b);               
          } 

          else {
               /*
               Means that the forked process is the process
               Close all the file descriptors that we don't need
               Initialize a buffer array of type char
               Write data from the pipe and check if any data was read
               If  which means that it is the parent process
               */  
               close(fd2[0]);
               close(fd[1]);
               int buf;
               int a=1000,b=1234;
               write(fd2[1],&a,sizeof(a));
               write(fd2[1],&b,sizeof(b));
               close(fd2[1]);

               if(read(fd[0],&buf,4)>0){
                    printf("Parent received %d | The answer is %d\n",buf,buf);
               }
               else{
                    perror("Parent failed to write data!\n");
                    exit(EXIT_FAILURE);
               }

               kill(pid,SIGQUIT);
               printf("Parent | pid: %d DONE!\n",getpid()); 
               close(fd[0]);
          }
     }
return 0;
}