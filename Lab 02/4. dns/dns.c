/**
 * P15/1725/2016
 * NYAGESOA ABIUD ORINA
 * A PROGRAM TO PRINT OUT DNS ENTRIES FROM A GIVEN HOST
/**
 * HOW TO RUN
 * Compile:
 * 1. gcc -o getDNS getDNS.c
 * Run:
 * 2. ./getDNS 'Hostname to find'
*/

#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char *argv[]){
      struct hostent *hostname;
      struct in_addr **addr_list;

    printf("\n____________________________________________________\n");
    printf("Printing out the DNS entries\nin the address you provided");
    printf("\n____________________________________________________\n");
      if(argc <2 ){
            printf("\nProvide hostname to resolve\n");
            return 1;
      }

      //Gets host info
      hostname = gethostbyname(argv[1]);
      
      if (hostname == NULL) {
            herror("\nError in the gethostbyname function");
            return 2;
      }
      else{
          //print the entered hostname
          printf("\nYou entered: %s\n",argv[1]);
      }

      //Print information about this host
      printf("The Domain Name you entered is:\t %s\n", hostname->h_name); //Hostname
      printf("The address is of type:\t %d\n", hostname->h_addrtype); //address type
      printf("The Length of the Address is:\t %d\n", hostname->h_length);       //Length of address
      printf("The IP Address is:\t ");
       addr_list = (struct in_addr **)hostname->h_addr_list;
      for(int i = 0; addr_list[i] != NULL; i++)
      {
            printf("\t%s ", inet_ntoa(*addr_list[i]));
      }      
      printf("\n");
      return 0;    
}





