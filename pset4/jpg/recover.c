/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // declare variables
    int counter = 0;
    int buffer[512];
    int open = 1;
    char title[4];
    int check[4];
    int jpg1[4] = {0xff, 0xd8, 0xff, 0xe0};
    int jpg2[4] = {0xff, 0xd8, 0xff, 0xe1};
    
    // open memory card file
    FILE* file = fopen("card.raw", "r");
    
    if (file == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 1;
    }
    
    while(open == 1)
    {
        fread (&buffer, 512, 1, file);
        
        for(int i = 0; i < 4; i++)
        {
            check[i] = buffer[i];
        }
        
        if((memcmp(jpg1, check, 4) == 0 ) || (memcmp(jpg2, check, 4) == 0))
        {
            sprintf(title, "%03d.jpg", counter);
            FILE* img = fopen(title, "a");
            fseek(file, -4, SEEK_CUR);
            
            
            fwrite (&buffer, 512, 1, img);
            open = 0;
            counter++;
            fclose(img);
        }
    }
    
    while(fread(&buffer, 512, 1, file) > 0)
    {
        sprintf(title, "%03d.jpg", counter);
        FILE* img = fopen(title, "a");
        fread (&buffer, 512, 1, file);
        fwrite (&buffer, 512, 1, img);
        counter++;
        fclose(img);
    }
    
    fclose(file);
    return 0;

    
    
    

}
