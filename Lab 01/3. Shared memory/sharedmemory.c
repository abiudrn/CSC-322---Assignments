/********************************************************************************************
*P15/1725/2016
*NYAGESOA ABIUD ORINA
********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/shm.h>

#define SHMSZ     27

void memWriter()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    /*name the shared memory segment "6548"
     *Create the segment
     *Attach the segent to our data space
     */
    key = 6548;
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*Put some data for other process to read*/
    s = shm;
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;

    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while (*shm != '*')
     sleep(1);
    exit(0);
}

void memReader()
{
    int shmid;
    key_t key;
    char *shm, *s;

    /*Get the segment named "6548", created by the server.
     */
    key = 6548;

    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now read what the server put in the memory.
     */
    for (s = shm; *s != NULL; s++)
        putchar(*s);
    putchar('\n');

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    *shm = '*';

    exit(0);
}

int main(void)
{
     pid_t  pid;
     for (int i = 0; i < 5; ++i)
     {              

          pid = fork();

          if (pid<0){
               printf("Failed to fork process!\n");
               exit(EXIT_FAILURE);
          }

          else if (pid == 0){
               printf("Child process is reading\n");
               memReader();
          } 

          else {
               
               printf("Parent process is writing\n");
               memWriter();
          }
     wait(NULL);
     }
}
