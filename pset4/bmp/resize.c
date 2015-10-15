/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int resize = atoi(argv[1]);
    
    if (resize < 1 || resize > 100)
    {
        printf("Please input a resize between 1 and 100.\n");
        return 2;
    }
    
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    // store useful header info
    int height = abs(bi.biHeight);
    int width = bi.biWidth;
    
    // determine old and new padding size
    int padding =  (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = ((4 - (width * resize * sizeof(RGBTRIPLE)) % 4) % 4);
    
    // modify new header
    bi.biWidth = width * resize;
    bi.biHeight = bi.biHeight * resize;
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + newPadding);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < height; i++)
    {
        // vertical resize
        for (int n = 0; n < resize; n++)
        {
            // set a position
            fpos_t pos;
            fgetpos (inptr, &pos);
            
            // iterate over pixels in scanline
            for (int j = 0; j < width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // resize horizontally
                for (int m = 0; m < resize; m++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // add new padding
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
            if (n < (resize - 1))
            {
                // return to position
                fsetpos (inptr, &pos);
            }
        
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
