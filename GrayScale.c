//
// Created by 35799 on 19/11/2020.
//

#include "bmp.h"
#include "bmplib.h"
#include <math.h>

void setNewLuminance(PIXEL pixel){
    unsigned char newLuminance;

    newLuminance = (unsigned char)(round(pixel.red*0.299 + pixel.green*0.587 + pixel.blue*0.114));
//    printf("new luminance: %d\n", newLuminance);

    pixel.red = newLuminance;
    pixel.blue = newLuminance;
    pixel.green = newLuminance;

//    printf("%d\n", pixel.red);
//    printf("%d\n", pixel.green);
//    printf("%d\n", pixel.blue);

}

void makePictureGrayScaled(PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp){

    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage)/3); i++) {    // for each pixel

        unsigned char newLuminance;
        if (pixels[i].isPadding == false) {
            newLuminance = (unsigned char) (round(
                    pixels[i].red * 0.299 + pixels[i].green * 0.587 + pixels[i].blue * 0.114));

            pixels[i].red = newLuminance;
            pixels[i].blue = newLuminance;
            pixels[i].green = newLuminance;
        }
    }


    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
    fwrite(pixels, bitmapInfoHeader->biSizeImage, 1, fp);



}