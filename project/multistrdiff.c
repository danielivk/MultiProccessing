#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#include "mystrlib.h"

#define STRLEN (80)
#define childFileName "./mystrdiff"
							/*	Father splits via fork and the childs executes mystrdiff and returns the result via exit status	*/
int main(int argc, char *argv[])
{
	char str1[STRLEN+1], str2[STRLEN+1];

	while(mygets(str1, STRLEN) != NULL && mygets(str2, STRLEN) != NULL)
	{
		switch (fork())
		{
			case -1:
				printf("Error in Fork");								// if fork returns -1 then it failed.
				exit(EXIT_FAILURE);
			case 0:
				;
				char* strings[] = { childFileName, str1, str2, NULL };	// store str1 and str2 in argv for execve
				execve(childFileName, strings, NULL);					// compute in child proccess	
				printf("Error in Execve");								// if we reach this point it means execve has failed.
				exit(EXIT_FAILURE);
			default:
				;
				int waitstatus, result;
				wait(&waitstatus);										// wait for child to finish computing
				result = WEXITSTATUS(waitstatus);						// get exit status from child
				printf("\nStr Diff =  %d\n", result);					// print result
				break;
		}
	}
	return EXIT_SUCCESS;
}





