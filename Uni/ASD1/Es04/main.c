#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * insuccesso(const char * pat)
{
	int j, i;
	int n = strlen(pat);
	int * insuccesso = calloc(sizeof(char), n);
	insuccesso[0] = -1;
	for (j=1; j<=n-1; j++)
	{
		i = insuccesso[j-1];
		while (pat[j] != pat[i+1] && i>=0)
			i = insuccesso[i];

		if (pat[j] == pat[i+1])
			insuccesso[j] = i+1;
		else
			insuccesso[j] = -1;
	}
	return insuccesso;
}

int KMP_match(const char * stringa, const char * pat)
{
	int * insucc = insuccesso(pat);
	int i=0, j=0;
	int lenS=strlen(stringa), lenP=strlen(pat);

	while (i<lenS && j<lenP)
	{
		if (stringa[i]==pat[j])
			i+=1, j+=1;
		else if (j==0)
			i+=1;
		else
			j = insucc[j-1]+1;
	}
	free(insucc);

	if (j==lenP)
		return i-lenP;
	return -1;
}

int * insuccesso_ciclico(const char * pat)
{
	int j, i;
	int n = strlen(pat);
	int * insuccesso = calloc(sizeof(char), n);

	for (i=1, j=0; i<n; i++)
	{
		while (j>0 && pat[i]!=pat[j])
			j=insuccesso[j-1];

		if (pat[i]==pat[j])
			j++;
		insuccesso[i]=j;
	}
	return insuccesso;
}

int KMP_cyclic_match(const char * stringa, const char * pat)
{
	int j, i;
	int lenS=strlen(stringa), lenP=strlen(pat);
	int * insucc = NULL;
	if(lenS!=lenP)
		return -1;
	insucc = insuccesso_ciclico(pat);

	for (i=0, j=0; i<lenP; i++)
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
	free(insucc);

	if (j>=lenS)
		return i;
	return -1;
}

int main(void)
{
	printf("ACACACACACAGT has ACACAGT %d\n", KMP_match("ACACACACACAGT", "ACACAGT"));
	printf("ACACACACACAGT has ACACAJT %d\n", KMP_match("ACACACACACAGT", "ACACAJT"));
	printf("asd==das %d\n", KMP_cyclic_match("asd", "asd"));
	printf("asd==das %d\n", KMP_cyclic_match("asd", "das"));
	printf("asd==das %d\n", KMP_cyclic_match("asd", "das"));
	printf("asd==sda %d\n", KMP_cyclic_match("asd", "sda"));
	printf("asd==daz %d\n", KMP_cyclic_match("asd", "daz"));
	printf("ciaone==neciao %d\n", KMP_cyclic_match("ciaone", "neciao"));
	printf("ciaone==neziao %d\n", KMP_cyclic_match("ciaone", "neziao"));
	printf("ciaone==leciao %d\n", KMP_cyclic_match("ciaone", "leciao"));
	return 0;
}


