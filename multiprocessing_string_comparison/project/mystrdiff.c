#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <unistd.h> 
#include "mystrlib.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s [str1] [str2]\n", argv[0]);
		exit (-1);
	}
	return mystrdiff(argv[1], argv[2]); // return the result via exit status of the childs main()
}