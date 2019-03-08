/**
 * CREATED BY:
 * P15/1725/2016
 * ABIUD ORINA NYAGESOA
 *
 * A CLIENT SERVER MODEL TO IMPLEMENT THE DOCIRCULANT FUNCTION
 *
 * */
// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

//define port for communication
#define PORT 2018

//function prototype
void printCirculant(int *circulantMatrix, int count);

//printCirculant function
void printCirculant(int *circulantMatrix, int count){
    printf("\n");
    printf("The 2D Circulant Matrix is:\n");
    for(int i = 0; i < count; i++)
    {
        for(int j = 0; j < count; j++)
        {
            printf("%d\t", *(circulantMatrix + i*count + j));
        }
        printf("\n");
    }
}

//initialize main
int main(int argc, char const *argv[])
{
    printf("\n********************************************************\n");
    printf("***                                                  ***\n");
    printf("***           CLIENT CODE EXECUTING...               ***\n");
    printf("***                                                  ***\n");
    printf("********************************************************\n");
    int sock;
    struct sockaddr_in address;
    struct sockaddr_in serv_addr;
    //int buffer[1024]= {0};

    //Create a sock fd and socket and check
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    else{
      perror("Socket creation");
    }

    //fill memory with zeros
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    else{
      perror("Address convert");
    }

    //connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnect Failed \n");
        return -1;
    }
    else{
      perror("Connect");
    }

    printf("\n********************************************************\n");
    //PERFORM THE MAIN FUNCTION

    //define variables
    int vecsize;


    //read vector size from the user
    printf("\nEnter vector  size: ");
    scanf("%d", &vecsize);

    int circulantMatrix[vecsize][vecsize];

    int genVector[vecsize]; //= malloc(vecsize);

    //read vector from the user
    printf("\n");
    for(int i = 0; i < vecsize; i++)
    {
        printf("Enter element %d: ",i);
        scanf("%d", &genVector[i]);
    }

    //print the entered vector
    printf("\n");
    printf("Here is the vector you entered:\n");
    for(int i = 0; i < vecsize; i++)
    {
        printf("%d",genVector[i]);
        printf("\n");
    }
    printf("\n");

    //send the vector size to allow it read the vector
    int sent = send(sock,&vecsize,sizeof(vecsize),0);
    if (sent < 0){
      perror("Error sending vector size...");
    }
    else{
      perror("Sending vector size to server...");
    }

    if((send(sock,genVector,sizeof(genVector),0))==-1){
      perror("Sending vector to server...");
    }

    printf(" The sizeof genVector is %d\n", sizeof(genVector));

    //receive the 2D CM from the server

    int circ_read = read(sock, circulantMatrix, sizeof(circulantMatrix));
    if(circ_read == -1){
      perror("Error Reading CM from server");
    }
    else{
      perror("Reading CM from server");
    }

    printf("\nThe size of the circulant read is %d", sizeof(circulantMatrix));

    //print the 2D CM
    //printCirculant(circulantMatrix,vecsize*vecsize*sizeof(int));
    printf("\n");
    for (int i = 0; i < vecsize; i++) {
      for (int j = 0; j < vecsize; j++) {
        printf("%d\t" ,circulantMatrix[i][j] );
      }
      printf("\n");
    }

    //close the socket
    close(sock);
    return 0;
}
