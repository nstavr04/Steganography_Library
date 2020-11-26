/* bmp.c
* Copyright (C) 2020 nstavr04 mvasil17
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License.
*/

#include "bmp.h"

/**
 * Function to load all the image data details into the memory
 * @param filename the image file name
 * @param bitmapFileHeader the image file header
 * @param bitmapInfoHeader the image info header
 * @return an unsigned char pointer to the image data
 */
unsigned char *LoadBitmapFile(char *filename, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader) {
    FILE *filePtr; //our file pointer
    unsigned char *bitmapImage;  //store image data

    //open filename in read binary mode
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL){
        printf("Unable to open");
        exit(-1);
    }


    //read the bitmap file header
    fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    //verify that this is a bmp file by check bitmap id
    if ((bitmapFileHeader->bfType1) != 0x42 || (bitmapFileHeader->bfType2) != 0x4D)     //0x42 = 'B' && 0x4D = 'M'
    {
        fclose(filePtr);
        printf("This is not a .bmp file!");
        exit(-1);
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

    // Check if the picture is uncopressed
    if (bitmapInfoHeader->biCompression != 0){
        printf("This file is not an uncompressed .bmp file");
        exit(-1);
    }
    // Check if it a 24bit picture
    if (bitmapInfoHeader->biBitCount != 24){
        printf("The .bmp image is not 24 bits");
        exit(-1);
    }

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char *) malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage) {
        free(bitmapImage);
        fclose(filePtr);
        printf("Not enough memory to allocate");
        exit(-1);
    }

    //read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader->biSizeImage, 1, filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL) {
        fclose(filePtr);
        printf("Not enough memory to allocate");
        exit(-1);
    }

    //close file and return bitmap image data
    fclose(filePtr);
    return bitmapImage;
}

/**
 * Function to assign the image data into a pixel structure
 * @param bitmapData the image data
 * @param bitmapInfoHeader the image info header
 * @return a pixel pointer to the image pixel structure
 */
PIXEL *getEachPixel(unsigned char *bitmapData, BITMAPINFOHEADER *bitmapInfoHeader) {

    int numOfEachLinePadding;
    //check if there is padding
    bool padding = false;
    if ((bitmapInfoHeader->biWidth)*3%4 != 0){
        padding = true;
        numOfEachLinePadding = (bitmapInfoHeader->biWidth)*3%4;
    }

    PIXEL *pixels = (PIXEL *)malloc(sizeof(PIXEL) * ((bitmapInfoHeader->biSizeImage)/3));    //each pixel is 3 bytes
    if (!pixels){
        printf("Unable to allocate memory");
        exit(-1);
    }

    int linecounter = bitmapInfoHeader->biWidth + numOfEachLinePadding;

    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage) / 3); i++) {    // for each pixel

        (pixels + i)->red = *(bitmapData);
        bitmapData++;
        (pixels + i)->green = *(bitmapData);
        bitmapData++;
        (pixels + i)->blue = *(bitmapData);
        bitmapData++;

        if (padding == true) {
            if (linecounter == 0)
                linecounter = bitmapInfoHeader->biWidth + numOfEachLinePadding;

            if (linecounter <= numOfEachLinePadding) {
                (pixels + i)->isPadding = '1';
            } else {
                (pixels + i)->isPadding = '0';
            }

            //Retracting 3 because we are dealing with pixels
            linecounter--;
        }

    }
    return pixels;
}

//Driver function
#ifdef bmpDEBUG
int main() {

    BITMAPFILEHEADER b1;

    BITMAPINFOHEADER b2;

    printf("%llu\n", sizeof(b1));

    printf("%llu\n\n", sizeof(b2));

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

    unsigned char *bitmapData;
    bitmapData = LoadBitmapFile("image6.bmp", &bitmapFileHeader, &bitmapInfoHeader);

//#ifdef list
    imageInfo(bitmapFileHeader, bitmapInfoHeader);
//#endif

    FILE *filePtr;

    filePtr = fopen("newImage.bmp", "wb");

    if (filePtr == NULL) {
        printf("Can't write on file");
        return 0;
    }

    BITMAPFILEHEADER *ptr1 = &bitmapFileHeader;
    BITMAPINFOHEADER *ptr2 = &bitmapInfoHeader;

    fwrite(ptr1, sizeof(BITMAPFILEHEADER), 1, filePtr);
    fwrite(ptr2, sizeof(BITMAPINFOHEADER), 1, filePtr);
    fwrite(bitmapData, bitmapInfoHeader.biSizeImage, 1, filePtr);

    return 0;

}
#endif


