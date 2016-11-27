#include <stdio.h>
#include <stdlib.h>
/*15. Scrivere una funzione che restituisca true se la stringa passata come parametro è palindroma, false
altrimenti.*/
#include <stdbool.h>
#include <string.h>
#define DIM 20
_Bool check_stringa_palindroma(char stringa[]);

int main()
{
    char s1[DIM+1] = "albicocche";
    char s2[DIM+2] = "kek";
	printf("check_stringa_palindroma(%s) = %d\n", s1, check_stringa_palindroma(s1));
	printf("check_stringa_palindroma(%s) = %d\n", s2, check_stringa_palindroma(s2));
	return 0;
};

_Bool check_stringa_palindroma(char stringa[])
{
	_Bool palindroma = true;
	int i=0;
	int len=strlen(stringa);
	for (i=0; i<len/2 && palindroma==true; i++)
		if (stringa[i] != stringa[len-i-1])
			palindroma = false;
	return palindroma;
}

