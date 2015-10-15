#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * Pset2 Caesar Cipher
 * Created by Sarah Connor
 */
 
int main(int argc, char* argv[])
{
    // checks to ensure user inputted a value after program name
    if (argc < 2)
    {
        printf("Program name must be followed by an interger.\n");
        exit(1);
    }
    
    // checks to see if that value is a digit
    if (isdigit((unsigned char) *argv[1]))
    {
        int key = atoi(argv[1]);
		
        if (key < 1)
        {
            printf("Program name must be followed by a positive integer.\n");
            exit(1);
        }
	    
        string ptext = GetString();

        for (int i = 0, n = strlen(ptext); i < n; i++)
        {
            if (isalpha(ptext[i]))
            {
                if (islower(ptext[i]))
                {
                    char ctext = ((ptext[i] - 'a' + key) % 26) + 'a';
                    printf("%c", ctext);
                }
                
                else
                {
                    char ctext = ((ptext[i] - 'A' + key) % 26) + 'A';
                    printf("%c", ctext);
                }
            }
            
            // if the character is not alphabetical, it prints unchanged    
            else
            {
                printf("%c", ptext[i]);
            }
        }
        
        // the program prints a newline after the encrypted code
        printf("\n");
    }

    // if the program sucessfully runs the program returns 0
    return 0;
}
