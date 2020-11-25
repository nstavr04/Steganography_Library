/* DecodeText.c
* Copyright (C) 2020 nstavr04 mvasil17
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License.
*/

/**
* @file DecodeText.c
* @brief The class that decodes an encrypted message from the image, back to its .txt format
*
* @author mvasil17
* @bug No known bugs.
*/

#include "bmp.h"
#include "bmplib.h"
#include <math.h>

void stegaEncryptDecodeText(unsigned char *bitmapData, BITMAPINFOHEADER *bitmapInfoHeader, int systemKey, int length, FILE *outputFile){

    int *fn;

    fn = createPermutationFunction(bitmapInfoHeader->biSizeImage, systemKey);    // system-key-integer

    int counter = 7;

    int oneChar = 0;

    for (int i = 0; i < length*8; i++) {

        int o = fn[i];

        unsigned char currentByte = bitmapData[o];
        int res = (currentByte & 1) * pow(2, counter);
        oneChar = oneChar + res;

        if (counter == 0) {
            counter = 7;
            if(oneChar != '\0')
                fprintf(outputFile, "%c", oneChar);
            oneChar = 0;
        } else {
            counter--;
        }
    }

    free(fn);

}

//Driver function
#ifdef DecodeTextDEBUG
int main (int argc, char *argv[]){

    int systemKey = 100;

    unsigned char *bitmapData;

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

    //Open the new file (create it)
    if (argc != 5){
        printf("You need to enter 5 arguments for that operation.\n e.g. $./bmpSteganography –decodeText encryptedImage.bmp msgLength output.txt");
    }

    int textSizeInBytes = atoi(argv[3]);

    FILE *outputFile = NULL;
    outputFile = fopen(argv[4], "w");
    if (outputFile == NULL) {
        printf("unable to open");
        exit(-1);
    }

    bitmapData = LoadBitmapFile(argv[2], &bitmapFileHeader, &bitmapInfoHeader);

    stegaEncryptDecodeText(bitmapData, &bitmapInfoHeader, systemKey, textSizeInBytes, outputFile);

}
#endif