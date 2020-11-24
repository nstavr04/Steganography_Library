/* Negative.c
* Copyright (C) 2020 nstavr04 mvasil17
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License.
*/

#include "bmp.h"
#include "bmplib.h"

void setNegative(PIXEL *pixel){
    unsigned char newLuminance;


    pixel->red = 255 - pixel->red;
    pixel->green = 255 - pixel->green;
    pixel->blue = 255 - pixel->blue;

}

void makePictureNegative(PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp){

    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage)/3); i++) {    // for each pixel
        setNegative(&pixels[i]);
    }

    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
    //fwrite(pixels, bitmapInfoHeader->biSizeImage, 1, fp);

    // We cant use fwrite because our structure PIXEL has 4 bytes instead of 3 for the RGB
    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage)/3); i++){

        fwrite(&pixels[i].blue,1,1,fp);
        fwrite(&pixels[i].green,1,1,fp);
        fwrite(&pixels[i].red,1,1,fp);

    }

}