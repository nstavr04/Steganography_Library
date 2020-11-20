//
// Created by 35799 on 19/11/2020.
//

#include "bmp.h"
#include "bmplib.h"
#include <math.h>

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

    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
    fwrite(pixels, bitmapInfoHeader->biSizeImage, 1, fp);

}