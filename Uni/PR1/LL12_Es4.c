#include <stdio.h>
#include <stdlib.h>
/*4. scrivere una funzione ricorsiva che calcoli le occorrenze di un carattere c in una stringa S. */
int rec_count_c_in_string(char * stringa, char c);

int main()
{
    char stringa[] = "Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...";
    printf("%d\n", rec_count_c_in_string(stringa, ' '));
    return 0;
}

int rec_count_c_in_string(char * stringa, char c)
{
    if (*stringa == '\0')
        return 0;
    return (*stringa==c) + rec_count_c_in_string(stringa+1, c);
}

