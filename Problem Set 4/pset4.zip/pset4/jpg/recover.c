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
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;
typedef BYTE BLOCK[512];

/**
 * Determines if this is the beginning block of a JPG image.
 */
bool isBeginningOfJpg(BYTE* block)
{
    return block[0] == 0xff && block[1] == 0xd8  && block[2] == 0xff
        && block[3] >> 4 == 14;
}

/**
 * Given a file a buffer finds first image block in file.
 */
int findFirstImageBlock(FILE* inptr, BYTE* f_block, int block_size)
{
    do
    {
        fread(f_block, block_size, 1, inptr);

        if (isBeginningOfJpg(f_block))
        {
            return 0;
        }

    }
    while(!feof(inptr));

    fprintf(stderr, "No images found.");
    return 3;
}

/**
 * Given image file pointer with buffer size, export all JPGs in file.
 *
 * Assumes all JPGs are abutt eachother.
 */
int exportImages(FILE* inptr, BYTE* f_block, int block_size)
{
    // track count and name
    int file_count = 0;
    char image_file[80];

    do 
    {
        // new file name 
        sprintf(image_file, "%03d.jpg", file_count);
        file_count++;

        // open new image file
        FILE* outptr = fopen(image_file, "w");

        if (outptr == NULL)
        {
            fprintf(stderr, "Could not open %s.\n", image_file);
            return 1;
        }
        // read and write image blocks to file
        do
        {
            fwrite(f_block, block_size, 1, outptr);
            fread(f_block, block_size, 1, inptr);

            // close at end input
            if (feof(inptr))
            {
                fclose(outptr);
                return 0;
            }

        }
        while(!isBeginningOfJpg(f_block));

        // close image file
        fclose(outptr);

        // backtrack to previous so next read is at signature
        fseek(inptr, -block_size , SEEK_CUR);
    }
    while(fread(f_block, block_size, 1, inptr));

    return 0;
}


int main(int argc, char* argv[])
{
    char* infile = "card.raw";

    // open image card drive
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    BLOCK f_block;

    int err = 0;

    err = findFirstImageBlock(inptr, f_block, sizeof(f_block));
    
    if (err != 0)
    {
        fclose(inptr);
        return  err;
    }
    
    err = exportImages(inptr, f_block, sizeof(f_block));

    // close infile
    fclose(inptr);

    return err;
}
