/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // save factor
    int factor = atoi(argv[1]);
    
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    else if (factor < 1 || factor > 100)
    {
        printf("Usage: ./copy infile outfile; n must be between 1 and 100\n");
        return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_output;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_output = bf;
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_output;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_output = bi;
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // set new dimensions
    bi_output.biHeight = bi.biHeight * factor;
    bi_output.biWidth = bi.biWidth * factor;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_resized =  (4 - (bi_output.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine new file sizes
    bi_output.biSizeImage = (bi_output.biWidth * sizeof(RGBTRIPLE) + padding_resized) * abs(bi_output.biHeight);
    bf_output.bfSize = bi_output.biSizeImage + sizeof(bi) + sizeof(bf);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_output, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_output, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        // go over each scanlines factor times
        for (int times = 0; times < (factor); times++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write pixel factor times
                for (int k = 0; k < factor; k++)
                {
                    // write to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // done with line, so we need to add padding
            for (int l = 0; l < padding_resized; l++)
            {
                fputc(0x00, outptr);
            }
            
            // reset line till factor - 1 times (last time needs to go on)
            if (times < (factor - 1))
            {
                // reset
                fseek(inptr, (-bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
