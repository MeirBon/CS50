/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 * Mèir Noordermeer
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int blocksize = 512;
    char jpeg[8];
    unsigned char buffer[blocksize];

    // open raw image files
    FILE* fcard = fopen("card.raw", "r");
    if (fcard == NULL)
    {
        printf("Unable to open file");
        return 2;
    }
    
    // set first file to write to
    FILE* fjpeg = fopen("000.jpg", "w");
    
    // counter for file names
    int counter = 0;
    
    // keep reading till EOF
    while (fread(&buffer, blocksize, 1, fcard))
    {
        // check for new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            // check if file is already written to, if so open new file
            if (fjpeg != NULL)
            {
                // close old file
                fclose(fjpeg);
                
                // set new file name
                sprintf(jpeg, "%03d.jpg", counter);
                
                // open new file
                fjpeg = fopen(jpeg, "w");
                
                // set new filename counter
                counter++;
            }
            else
            {
                // write buffer to fjpeg
                fwrite(&buffer, blocksize, 1, fjpeg);
            }
        }
        
        // write block to fjpeg
        fwrite(&buffer, blocksize, 1, fjpeg);
    }
    
    // close last file
    fclose(fjpeg);
    
    // close raw file
    fclose(fcard);
}