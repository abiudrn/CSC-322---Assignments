/**
 * CREATED BY:
 * P15/1725/2016
 * ABIUD ORINA NYAGESOA
 *
 * A UDP CLIENT SERVER MODEL TO IMPLEMENT THE DOCIRCULANT FUNCTION
 *
 * */


// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT    2018
#define MAXLINE 1024

//function prototypes
int printVector(int *genVector, int count);
int *doCirculant(int *genVector, int count);
void printCirculant(int *circulantMatrix, int count);

//*doCirculant function
int *doCirculant(int *genVector, int count){
    printf("\n");
    int *circulantMatrix = (int *)malloc(count * count * sizeof(int));
    for(int  i = 0; i < count; i++)
    {
        for(int j = 0; j < count; j++)
        {
            int num1 = count - i + j;
            int num2 = count;
            //shift the elements
            *(circulantMatrix + i*count + j) = genVector[(num1%num2)];
        }
    }
    return circulantMatrix;
    printf("\nCirculant Matrix Generation complete!\n");
}

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



// Driver code
int main() {
  printf("\n********************************************************\n");
  printf("***                                                  ***\n");
  printf("***           SERVER CODE EXECUTING...               ***\n");
  printf("***                                                  ***\n");
  printf("********************************************************\n");
    int sockfd;
    int buffer[MAXLINE];
    //char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    else{
      perror("Creating socket...");
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    else{
      perror("Binding...");
    }

    puts("Awaiting client interation");
    puts("Connected!");
    printf("********************************************************\n");

    //STEPS
    //Initialize variables
    int len;
    int circulantMatrix;

    //read vector length from client
    int vector_size = recvfrom(sockfd,len,1000,0,(struct sockaddr *)&cliaddr, sizeof(cliaddr));
    if (vector_size <0 ) {
      perror("Size receive");
    }else{perror("Size receive");}

    len = vector_size;
    printf("Vector size is : %d \n",len);

    int genVector[len];

    //read the vector from the client
    int rec1 = recvfrom(sockfd,  genVector,1000,0,(struct sockaddr **)&cliaddr, sizeof(cliaddr));
    if (rec1 == -1) {
      perror("Vector receive");
    }else{perror("Vector receive");}

    //display the read vector from the client
     //print the read vector
    printf("\nThe read vector is:\n");
    for (int i = 0; i < rec1; i++) {
      printf("%d\n",genVector[i]);
    }

    //perform the circulant
    printf("\n");
    circulantMatrix = doCirculant(genVector,len);

    //display the generated circulant matrix
    printCirculant(circulantMatrix,len);

    //send the generated circulant matrix to the client
    if(sendto(sockfd,genVector,1000,MSG_CONFIRM,(struct sockaddr *)&cliaddr, sizeof(cliaddr))){
      perror("Sending 2D CM to client ");
    }
    else{
      perror("Send:");
    }

    //close the socket
    close(sockfd);
    printf("socket closed successfully");

    return 0;
}

