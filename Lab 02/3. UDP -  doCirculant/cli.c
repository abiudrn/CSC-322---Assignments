/**
 * CREATED BY:
 * P15/1725/2016
 * ABIUD ORINA NYAGESOA
 *
 * A UDP CLIENT SERVER MODEL TO IMPLEMENT THE DOCIRCULANT FUNCTION
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//define variables
#define PORT    2018
#define MAXLINE 1024
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

//Initialize main
int main() {
  printf("\n********************************************************\n");
  printf("***                                                  ***\n");
  printf("***           CLIENT CODE EXECUTING...               ***\n");
  printf("***                                                  ***\n");
  printf("********************************************************\n");
    //declare variables
    int sockfd;
    //int buffer[MAXLINE];
    struct sockaddr_in servaddr;
    //char *hello = "Hello from client";


    // Create socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    else{
      perror("Socket creation");
    }

    //fill memory with zeros
    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    puts("Awaiting interation from client");
    printf("********************************************************\n");


    //STEPS
    //Initialize variables
    int len;

    //Read the vector length from the user
    printf("\n");
    printf("Enter vector length: ");
    scanf("%d",&len);

    //read in the vector from the user
    int genVector[len];
    printf("\n");
    for (int i = 0; i < len; i++) {
      printf("Enter element %d: ", i );
      scanf("%d", &genVector[i]);
    }

    //display the read vector
    printf("\n");
    printf("You entered the vector as:\n");
    for (int i = 0; i < len; i++) {
      printf("%d\n", genVector[i]);
    }

    //send the vector array length to the server
    //sendto(sockd, inputVector, arraylen * sizeof(int), 0, (struct sockaddr *)&srv_addr, sizeof(srv_addr)
    int send1 = sendto(sockfd,genVector,1000,MSG_CONFIRM,(struct sockaddr *)&servaddr, sizeof(servaddr));
    if (send1 == -1) {
      perror("Sending length...");
    }
    else{perror("Send");}

    //send the vector array to the server
    printf("\n");
    int send2 = sendto(sockfd,genVector,1000,MSG_CONFIRM,(const struct sockaddr *) &servaddr, sizeof(servaddr));
    if (send2 == -1) {
      perror("Sending vector...");
    }else{("Send");}

    //read the CM from the server
    int circulantMatrix[len][len];

    int circ_read = recvfrom(sockfd, circulantMatrix, 1000,0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    if(circ_read == -1){
      perror("Error Reading CM from server");
    }
    else{
      perror("Reading CM from server");
    }

    //display the read CM to the user

    printCirculant(circulantMatrix,len);  

    //close the socket
    close(sockfd);
    return 0;

}


