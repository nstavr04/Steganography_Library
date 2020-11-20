//
// Created by 35799 on 19/11/2020.
//

#include "bmp.h"
#include "bmplib.h"
#include <math.h>

void setNewLuminance(PIXEL pixel){
    unsigned char newLuminance;

    newLuminance = pixel.red*0.299 + pixel.green*0.587 + pixel.blue*0.114;
    printf("new luminance: %d\n", newLuminance);

    pixel.red = newLuminance;
    pixel.blue = newLuminance;
    pixel.green = newLuminance;

    printf("%d\n", pixel.red);
    printf("%d\n", pixel.green);
    printf("%d\n", pixel.blue);

}

void makePictureGrayScaled(PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader){

    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage - 2) / 3); i++) {    // for each pixel
        setNewLuminance(pixels[i]);
    }



}