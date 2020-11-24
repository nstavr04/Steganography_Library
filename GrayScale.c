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

/**
 * @brief The function used to create the greyscaled image with the help of a function that calculates the luminance
 *
 * @param pixels The pixel structure of the image
 * @param bitmapFileHeader the file header of the image
 * @param bitmapInfoHeader  the info header of the image
 * @param fp the file pointer, used to save the image into the new file
 */
void makePictureGrayScaled(PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp){

    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage)/3); i++) {    // for each pixel
        setNewLuminance(&pixels[i]);
    }

    printf("BITMAPFILEHEADER SIZE SHOULD BE (14) AND IT IS: %llu\n", sizeof(BITMAPFILEHEADER));
    printf("BITMAPINFOHEADER SIZE SHOULD BE (40) AND IT IS: %llu\n", sizeof(BITMAPINFOHEADER));


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