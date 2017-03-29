#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stampa_insuccesso(int * insucc, int n)
{
	int i;
	for (i=0; i<n; i++)
		printf("%3d", insucc[i]);
	printf("\n");
}

int * insuccesso(const char * pat)
{
    int i,j;
    int n = strlen(pat);
	int * insucc = calloc(sizeof(int), n);
	if (insucc==NULL)
		exit(EXIT_FAILURE);
    insucc[0] = -1;
    // analisi dei prefissi
    for (j = 1; j <= n-1; j++)
    {
        i = insucc[j-1];
        while (pat[j] != pat[i+1] && i>=0)
            i = insucc[i];
        if (pat[j] == pat[i+1])
            insucc[j] = i+1;
        else
            insucc[j] = -1;
    }
    return insucc;
}

int KMP_match(const char * stringa, const char * pat)
{
    int * insucc = insuccesso(pat);// array insuccesso
    int i = 0;
    int j = 0;
    int lenS = strlen(stringa);
    int lenP = strlen(pat);
	stampa_insuccesso(insucc, lenP);
    while (i < lenS && j < lenP)
    {
        if (stringa[i] == pat[j])
        {
            i = i+1;
            j = j+1;
        }
        else if (j == 0)
            i = i+1;
        else
            j = insucc[j-1]+1;
    }
	free(insucc);

    if (j == lenP)
        return i-lenP;
    return -1;
}

int KMP_cyclic_match_ok(const char * stringa, const char * pat)
{
	int i=0, j=0, c=0;
	int lenS=strlen(stringa), lenP=strlen(pat);
	int * insucc = NULL;
	if (lenS!=lenP)
		return -1;
	insucc = insuccesso(pat);
	stampa_insuccesso(insucc, lenP);

	for (i=0; i<lenP; i++)
	{
		while (j>0 && pat[i]!=stringa[j])
			j=insucc[j-1];

		if (pat[i]==stringa[j])
			j++;
	}

	for (i=0; i<lenP && j<lenS; i++)
	{
		while (j>0 && pat[i]!=stringa[j])
			j=insucc[j-1];

		if (pat[i]==stringa[j])
			j++;
	}
	if (j>=lenS)
		return i;

	return -1;
}

int KMP_cyclic_match(const char * stringa, const char * pat)
{
	int i=0, j=0, c=0;
	int lenS=strlen(stringa), lenP=strlen(pat);
	int * insucc = NULL;
	if (lenS!=lenP)
		return -1;
	insucc = insuccesso(pat);
	stampa_insuccesso(insucc, lenP);

    while (j < lenP)// && !(i==lenP-1 && j==0))
    {
		printf("i=%d, j=%d\n", i, j);
		printf("stringa[i]=%c, pat[j]=%c\n", stringa[i], pat[j]);
        if (stringa[i] == pat[j])
        {
            i = i+1;
            j = (j+1);//%lenS;
        }
        else if (j == 0)
            i = i+1;
        else
            j = (insucc[j-1]+1);//%lenS;
		i%=lenP;
    }
	free(insucc);

	printf("XXi=%d, j=%d\n", i, j);
    if (j == lenP)
        return lenP-i;

	return -1;
}

int main(void)
{
	//printf("ACACACACACAGT has ACACAGT %d\n", KMP_match("ACACACACACAGT", "ACACAGT"));
	//printf("ACACACACACAGT has ACACAJT %d\n", KMP_match("ACACACACACAGT", "ACACAJT"));
	//printf("ACACACACACAGT==CAGTACACACACA %d\n", KMP_cyclic_match("ACACACACACAGT", "CAGTACACACACA"));
	//printf("ACACACACACAGT==CAGTACACACACA %d\n", KMP_cyclic_match("ACACACACACAGT", "CAXTACACACACA"));
	printf("asd==asd %d\n", KMP_cyclic_match("asd", "asd"));
	printf("asd==das %d\n", KMP_cyclic_match("asd", "das"));
	printf("asd==sda %d\n", KMP_cyclic_match("asd", "sda"));
	printf("asd==daz %d\n", KMP_cyclic_match("asd", "daz"));
	//printf("ciaone==neciao %d\n", KMP_cyclic_match("ciaone", "neciao"));
	////printf("ciaone==leciao %d\n", KMP_cyclic_match("ciaone", "leciao"));
	return 0;
}


