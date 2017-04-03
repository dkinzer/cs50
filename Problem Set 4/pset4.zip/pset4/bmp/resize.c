/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes BMP files by a specifed factor. 
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp.h"


/**
 * Resizes a BMP format image file row.
 */
void resizeRow(int factor, int width, FILE* inptr, FILE* outptr )
{
    // determine padding for scanlines 
    int padding =  (4 - (factor * width * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over pixels in scanline
    for (int i = 0; i <  width; i++)
    {
        // temporary storage
        RGBTRIPLE triple;

        // read RGB triple from infile
        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

        // write RGB triple to outfile by factor given.
        for (int j = 0; j < factor; j++)
        {
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
    }

    // add padding
    for (int i = 0; i < padding; i++)
    {
        fputc(0x00, outptr);
    }
}


int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // verify factor
    int factor = atoi(argv[1]);

    if ((factor == 0 && (argv[1][0] != '0' || strlen(argv[1]) == 0))
            || factor < 1 || factor > 100)
    {
        printf("Error: expected factor to be a number within [1, 100] inclusive, but given \"%s\".\n", argv[1]);
        return 5;
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
        return 4;
    }

    // Create header copies
    BITMAPFILEHEADER bf_new;
    memcpy(&bf_new, &bf, sizeof(BITMAPFILEHEADER));

    BITMAPINFOHEADER bi_new;
    memcpy(&bi_new, &bi, sizeof(BITMAPINFOHEADER));

    // Modify the new headers

    bi_new.biHeight = factor * bi.biHeight ;
    bi_new.biWidth = factor * bi.biWidth;
    BYTE bitsPerPixel = 24;
    LONG rowSize = floor((bitsPerPixel * bi_new.biWidth + 31) / 32 ) * 4;
    bi_new.biSizeImage = rowSize * abs(bi_new.biHeight);

    bf_new.bfSize = bf.bfOffBits + bi_new.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // need the orig image row size to move input file pointer
    rowSize = floor((bitsPerPixel * bi.biWidth + 31) / 32 ) * 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // repeat resize of image row by factor
        for (int j = 0; j < factor; j++)
        {
            // set file pointer to beginning of image row
            LONG toRowSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (rowSize * i);
            fseek(inptr, toRowSize, SEEK_SET);

            resizeRow(factor, bi.biWidth, inptr, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
