/* DecodeStegano.c
* Copyright (C) 2020 nstavr04 mvasil17
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License.
*/

/**
* @file DecodeStegano.c
* @brief The class that unhides an image that is hidden in another image
*
* @author nstavr04
* @bug No known bugs.
*/

#include "bmp.h"
#include "bmplib.h"

void decodeStegano(PIXEL *pixels, BITMAPFILEHEADER *SecretFileHeader, BITMAPINFOHEADER *SecretInfoHeader, FILE *fp,char *nbBits) {

    fwrite(SecretFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(SecretInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    unsigned char R;
    unsigned char G;
    unsigned char B;

    for (unsigned int i = 0; i < ((SecretInfoHeader->biSizeImage)/3); i++){

        if(*nbBits == '1'){

            R = pixels[i].red << 7;
            G = pixels[i].green << 7;
            B = pixels[i].blue << 7;

        }
        else if(*nbBits == '2'){

            R = pixels[i].red << 6;
            G = pixels[i].green << 6;
            B = pixels[i].blue << 6;

        }
        else if(*nbBits == '3'){

            R = pixels[i].red << 5;
            G = pixels[i].green << 5;
            B = pixels[i].blue << 5;

        }
        else{

            R = pixels[i].red << 4;
            G = pixels[i].green << 4;
            B = pixels[i].blue << 4;

        }

        fwrite(&R,1,1,fp);
        fwrite(&G,1,1,fp);
        fwrite(&B,1,1,fp);

    }

}

//Driver function
#ifdef DecodeSteganoDEBUG
int main(int argc, char *argv[]){

    unsigned char *bitmapData;

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

    PIXEL *pixels;

    //Checking if nbBits are correct
    if(strcmp(argv[2] , "1") != 0 && strcmp(argv[2] , "2") != 0 && strcmp(argv[2] , "3") != 0 && strcmp(argv[2] , "4") != 0){
        printf("Wrong nbBits input. nbBits should be 1-4");
        exit(-1);
    }

    //Save the data of the first image in bitmapData
    bitmapData = LoadBitmapFile(argv[3], &bitmapFileHeader, &bitmapInfoHeader);

    //The file to save the Image to new-
    //5 Bytes because we need the \0 too
    char* newFile = (char *)malloc(strlen(argv[3]) + 5);
    strcpy(newFile,"new-");
    strcat(newFile, argv[3]);

    FILE *fp = fopen(newFile, "wb");

    pixels = getEachPixel(bitmapData, &bitmapInfoHeader);

    decodeStegano(pixels, &bitmapFileHeader, &bitmapInfoHeader, fp,argv[2]);

    free(pixels);
    free(newFile);

    fclose(fp);
}
#endif