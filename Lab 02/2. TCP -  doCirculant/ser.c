/**
 * CREATED BY:
 * P15/1725/2016
 * ABIUD ORINA NYAGESOA
 *
 * A CLIENT SERVER MODEL TO IMPLEMENT THE DOCIRCULANT FUNCTION
 *
 * */

// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

//define the port
#define PORT 2018

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


int main(int argc, char const *argv[])
{
  printf("\n********************************************************\n");
  printf("***                                                  ***\n");
  printf("***           SERVER CODE EXECUTING...               ***\n");
  printf("***                                                  ***\n");
  printf("********************************************************\n");

    //initialize variables
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    //int buffer[1024] = {0};
    //char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    else{
      perror("Socket");
    }

    // Forcefully attaching socket to the port 2018
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    else{
      perror("Attachment to port");
    }

    address.sin_family = AF_INET;address.sin_addr.s_addr = INADDR_ANY;address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 2018
    if (bind(server_fd, (struct sockaddr *)&address,addrlen)<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    else{
      perror("Bind");
    }

    //listen for connections
    puts("Listening for connections...");
    if (listen(server_fd, 5) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    else{
      perror("listen");
    }

    //accept connections
    if ((new_socket = accept(server_fd, (struct sockaddr *) &address,(socklen_t*)&addrlen))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else{
      perror("Connection");
    }

    printf("\n********************************************************\n");
    //PERFORM THE MAIN FUNCTION
    //define variables
    int vecsize;
    int *circulantMatrix;

    //read vecsize from the client
    read(new_socket,&vecsize,sizeof(vecsize));

    //print the size of the vector read from the server
    printf("\nThe vector size is : %d\n", vecsize );

    int genVector[vecsize];//malloc(vecsize*4);

    //read the vector from the client
    int x = read(new_socket,genVector,sizeof(genVector));

    printf("X is %d and size of genVector is %d \n",x, sizeof(genVector) );

    //print the read vector
    printf("\nThe read vector is:\n");
    for (int i = 0; i < vecsize; i++) {
      printf("%d\n",genVector[i]);
    }

    //perform the circulant matrix and add it to an array
    printf("\n");
    circulantMatrix = doCirculant(genVector,vecsize);

    //print the circulant matrix
    printCirculant(circulantMatrix,vecsize);

    //send the 2D CM to the client
    if(send(new_socket,circulantMatrix,1000,0)){
      perror("Sending 2D CM to client ");
    }
    else{
      perror("Send:");
    }

    //close socket
    close(new_socket);
    return 0;

}
