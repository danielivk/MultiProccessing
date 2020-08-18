#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#include "mystrlib.h"

#define STRLEN (80)

														/*	Father sends with p[1] to child in p[0]		*/
														/*	Child sends with p2[1] to Father in p2[0]	*/

int main(int argc, char *argv[])
{
	char str1[STRLEN+1];
	char str2[STRLEN+1];
	int p[2];
	int p2[2];

	int result, flag;
	if(argc == 1)
	{
		if (pipe(p) < 0 || pipe(p2) < 0)
		{
			fprintf(stderr, "Error in Pipe()\n");
			return EXIT_FAILURE;
		}
		
	}	
	

	if (argc == 3)
	{
		int in, out;


		in  = strtol(argv[1], NULL, 10);
		out = strtol(argv[2], NULL, 10);
		read(in, &flag, sizeof(int)); // read flag

		while(flag) // while father is sending information
		{
			read(in, str1, STRLEN); // read str1
			read(in, str2, STRLEN); // read str2
			if(str1 == NULL || str2 == NULL)
				break;
			result = (int)mystrdiff(str1, str2);
			write(out, &result, sizeof(int)); // send the string
			read(in, &flag, sizeof(int)); // read flag
		}
		

		close(in);
		close(out);
		return EXIT_SUCCESS;
	}


	

	
	switch(fork())
	{
		case -1:
			fprintf(stderr, "Error in Fork\n");
			return EXIT_FAILURE;


		case 0:/*Child*/	
			close(p[1]);
			close(p2[0]);
			// send pipe info with argc
			char in[3];
			char out[3];
			sprintf(in, "%d", p[0]);
			sprintf(out, "%d", p2[1]);

			char* strings[] = { argv[0], in, out, NULL }; 
			execve(argv[0], strings, NULL);


			fprintf(stderr, "Failed to execute execve\n");
			return EXIT_FAILURE;


		default:/*Father*/	
			
			close(p[0]);	// for use of child
			close(p2[1]);	// for use of child

			flag = 1;
			while(mygets(str1, STRLEN) != NULL && mygets(str2, STRLEN) != NULL)
			{
				write(p[1], &flag, sizeof(int));	// send the continue flag
				write(p[1], str1, STRLEN);			// send the string
				write(p[1], str2, STRLEN);			// send the string
				read(p2[0], &result, sizeof(int));	// recieve result
				printf("str diff=%d\n", result);	// print result
			}
			flag = 0;
			write(p[1], &flag, sizeof(int));	// send the continue flag
			close(p[1]);
			close(p2[0]);			
			break;
	}
	return EXIT_SUCCESS;
}





