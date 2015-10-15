#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

// program turns names into uppercase initials

int main(int argc, char* argv[])
{
    string name = GetString();
    int i;
    int n = strlen(name);
    
    /**
     * Prints first letter inputted and then runs through
     * the rest of the string and prints the first letter
     * after a space.
     */
    printf("%c", toupper(name[0]));
    
    for (i = 0; i < n; i++)
    {
        if (isspace(name[i])) 
        {
            i++;
            printf ("%c", toupper(name[i]));
        }
    }
    printf("\n");
    return 0;
}
