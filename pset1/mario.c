#include <stdio.h>
#include <cs50.h>

/*Program prompts user for a height then
draws an assymetrical pyramid of that height.*/

int main(void)
{
    int height = 0;
    
    /*Prompts user until given a valid interger between 0-23*/
    do
    {
        printf("Height:");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    /*the number of spaces and hashes are determined
    using an increasing counter*/
    for (int ctr = 0; ctr < height; ctr++)
    {
        for (int spaces = 0; spaces < (height - ctr - 1); spaces++)
        {
            printf (" ");
        }
        for (int hashes = 0; hashes < (ctr + 2); hashes++)
        {
            printf ("#");
        }
        printf ("\n");
    }
    return 0;
}

