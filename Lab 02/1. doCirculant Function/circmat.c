/**
 * CREATED BY:
 * P15/1725/2016
 * ABIUD ORINA NYAGESOA
 * 
 * A PROGRAM TO IMPLEMENT THE DOCIRCULANT FUNCTION
 * 
 * */

#include <stdio.h>
#include <stdlib.h>

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

//main
int main()
{
    printf("\n********************************************************\n");
    printf("***                                                  ***\n");
    printf("***     CIRCULANT MATRIX FUNCTION IMPLEMENTATION     ***\n");
    printf("***                                                  ***\n");
    printf("********************************************************\n");

    int len;
    int *circulantMatrix;

    //read vector size from the user
    printf("\nEnter vector  size: ");
    scanf("%d", &len);
    int *genVector = malloc(len);

    //read vector from the user    
    printf("\n");
    for(int i = 0; i < len; i++)
    {
        printf("Enter element %d: ",i);
        scanf("%d", &genVector[i]);
    }

    //print the entered vector
    printf("\n");
    printf("Here is the vector you entered:\n");
    for(int i = 0; i < len; i++)
    {
        printf("%d",genVector[i]);
        printf("\n"); 
    }

    //generate the circulant matrix
    printf("\n********************************************************\n");
    if(circulantMatrix = doCirculant(genVector,len)){
         perror("circulant function");
    }

     printf("\n********************************************************\n");
    //print the circulant matrix
    printf("\nPrinting the Circulant Martix\n");
    printCirculant(circulantMatrix,len);
    return 0;
}
