#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/mman.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include "mystrlib.h"

#define STRLEN (80)

											/*	Usage of mmap to communicate between Father and child	*/
int main(int argc, char *argv[])
{

	int* result, *flag;
	char* str1, *str2;

	flag	= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);			// share loop flag
	result	= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);			// share result
	str1	= mmap(NULL, STRLEN * sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // share str1
	str2	= mmap(NULL, STRLEN * sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // share str2

	if (flag == MAP_FAILED || result == MAP_FAILED || str1 == MAP_FAILED || str2 == MAP_FAILED)
	{
		return EXIT_FAILURE;
	}

	*flag = 1; // set loop flag to true
	switch(fork())
	{
		case -1: // if fork fails it returns -1
			fprintf(stderr, "Error in Fork\n");
			return EXIT_FAILURE;



		case 0:/*Child*/
			
			while(*flag != -1)						// if flag is -1 the program ends
			{			
				while((*flag) == 1)					// if flag == 1 wait for signal from father
					/*WAITING*/;			

				*result = mystrdiff(str1, str2);	// change shared result 
				*flag = 1;							// signal Father that result has been changed
			}
			break;
							
		
		default:/*Father*/
			while(mygets(str1, STRLEN) != NULL && mygets(str2, STRLEN) != NULL)
			{
				*flag = 0;			// after input is gathered from user into str1 and str2 set flag to 0
				while((*flag) == 0) // wait for child to compute and change flag to 1
					/*WAITING*/;
			
				printf("str diff = %d\n", *result); // after waiting the result is ready to be printed by Father to the user.
				fflush(stdin);
			}
			*flag = -1; // signal child that the program ended
			break;
	}

	if (munmap(flag, sizeof(int)) == -1 || munmap(result, sizeof(int)) == -1 || munmap(str1, STRLEN) == -1 || munmap(str2, STRLEN) == -1)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}





