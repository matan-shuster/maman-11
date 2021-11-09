#include <stdio.h>
#include <ctype.h>
#include <string.h>
/*Global variables */
char longstring[81];
char shortstring[81];

void contract(char s1[],char s2[])
{
    int i = 0;
    int j = 1;
    int g = 0;
    while (s1[i] != '\0')
    {
        if((s1[j] - s1[i] == 1) && ((isalnum(s1[j]) && isalnum(s1[i]))))
        {
            s2[g] = s1[i];
            g++;
            j++;
            i++;
            int counter = 0;
            while((s1[j] - s1[i] == 1) && ((isalnum(s1[j]) && isalnum(s1[i]))) && (s1[j] != '\0'))
            {
                counter++;
                j++;
                i++;
            }
            if(counter >= 1){
            s2[g] = '-';
            g++;
            }
            s2[g] = s1[i];
        }
        else
        {
            s2[g] = s1[i];
            g++;
            s2[g] = s1[j];
            i++;
            j++;
        }
    }
    i = 0;
    while(s2[i] != '\0')
    {
        shortstring[i] = s2[i];
        i++;
    }
}
void main() {
    printf("Please enter a string\n");
    fgets(longstring, 81,stdin);
    contract(longstring,shortstring);
    printf("This is the string you've entered: %s", longstring);
    printf("this is the shortened string: %s\n",shortstring);
}