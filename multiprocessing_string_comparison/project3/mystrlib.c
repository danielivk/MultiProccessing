
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystrlib.h"

char* mygets(char *str, int len)
{
	// gets input from keyboard and add null terminator at the end of the word instead of \n

	char *retval;
	char *strterm;

	retval = fgets(str, len, stdin);

	strterm = strchr(str,'\n');
	if (strterm != NULL)
	{
		*strterm = '\0';
	} else {
		str[len] = '\0';
	}
	return retval;
}

int mystrdiff(char *str1, char *str2)
{
	// returns the number of different characters between 2 strings
	// examples for mystrdiff(abc, abeg) = 2
	int retval;
	int len, len1, len2;
	int i;

	len1 = strlen(str1);
	len2 = strlen(str2);

	// get max minimum length between the two
	len = (len1 < len2) ? len1 : len2;
	retval = abs(len1 - len2);
	for (i = 0; i < len ; i++)
	{
		if (str1[i] != str2[i])
		{
			retval++;
		}
	}
	return retval;
}


