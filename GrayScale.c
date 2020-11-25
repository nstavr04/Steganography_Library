/* GrayScale.c
* Copyright (C) 2020 nstavr04 mvasil17
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License.
*/

/**
* @file GrayScale.c
* @brief The class that implements the GrayScale function.
*
* This class takes an images and creates the grayscaled version of the image
*
* @authors nstavr04, mvasil17
* @bug No known bugs.
*/

#include "bmp.h"
#include "bmplib.h"
#include <math.h>

/** @brief This method is used at each pixel, to find and set the new grayscaled rgb value
 *
 * @param pixel
 */
void setNewLuminance(PIXEL *pixel){
    unsigned char newLuminance;
    newLuminance = (unsigned char)(round(pixel->red*0.299 + pixel->green*0.587 + pixel->blue*0.114));

    pixel->red = newLuminance;
    pixel->blue = newLuminance;
    pixel->green = newLuminance;
}

void makePictureGrayScaled(PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp){

    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage)/3); i++) {    // for each pixel
        setNewLuminance(&pixels[i]);
    }

    // We cant use fwrite because our structure PIXEL has 4 bytes instead of 3 for the RGB
    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage)/3); i++){

        fwrite(&pixels[i].blue,sizeof(unsigned char ),1,fp);
        fwrite(&pixels[i].green,sizeof(unsigned char ),1,fp);
        fwrite(&pixels[i].red,sizeof(unsigned char ),1,fp);

    }

}

//Driver function
#ifdef GrayScaleDBUG
int main(int argc, char *argv[]) {
    PIXEL *pixels;
    int counter = 2;  // program argument 1 Is the operations. (-grayscale)
    while (counter < argc) {

        unsigned char *bitmapData;

        BITMAPINFOHEADER bitmapInfoHeader;

        BITMAPFILEHEADER bitmapFileHeader;

        bitmapData = LoadBitmapFile(argv[counter], &bitmapFileHeader, &bitmapInfoHeader);

        FILE *fp = fopen(argv[counter], "wb");

        pixels = getEachPixel(bitmapData, &bitmapInfoHeader);

        makePictureGrayScaled(pixels, &bitmapFileHeader, &bitmapInfoHeader, fp);

        counter++;

        fclose(fp);
    }

    free(pixels);
}
#endif