#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * Pset2 Vigenere Cipher
 * Created by Sarah Connor
 */
 
int main(int argc, char* argv[])
{
       
    // checks to ensure user inputted a value after program name
    if (argc < 2)
    {
        printf("Program name must be followed by a string.\n");
        exit(1);
    }
    
    // checks to see if that value is a string
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha((unsigned char) argv[1][i]))
        {
            printf("Program name must be followed by all letters, please.\n");
            exit(1);
        }
    }
    
    // gets a key from the command line
    string key = argv[1];
    int klen = strlen(key);
    int j = 0;
    
    // gets a string inputted by the user and then encrypts it
    string ptext = GetString();
    
    for (int i = 0, n = strlen(ptext); i < n; i++)
    {
        if (isalpha(ptext[i]))
        {
            if (islower(ptext[i]))
            {
                if (islower(key[j]))
                {
                    char k = key[j] - 'a';
                    char ctext = ((ptext[i] - 'a' + k) % 26) + 'a';
                    printf("%c", ctext);
                    j = (j + 1) % klen;
                }
                        
                else
                {
                    char k = key[j] - 'A';
                    char ctext = ((ptext[i] - 'a' + k) % 26) + 'a';
                    printf("%c", ctext);
                    j = (j + 1) % klen;
                }
            }
                
            else
            {
                if (islower(key[j]))
                {
                    char k = key[j] - 'a';
                    char ctext = ((ptext[i] - 'A' + k) % 26) + 'A';
                    printf("%c", ctext);
                    j = (j + 1) % klen;
                }
                        
                else
                {
                    char k = key[j] - 'A';
                    char ctext = ((ptext[i] - 'A' + k) % 26) + 'A';
                    printf("%c", ctext);
                    j = (j + 1) % klen;
                }

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

    // if the program sucessfully runs the program returns 0
    return 0; 
}
