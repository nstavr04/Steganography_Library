/* List.c
* Copyright (C) 2020 nstavr04 mvasil17
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License.
*/

/**
* @file List.c
* @brief The class that prints the header of a .bmp image
*
* This class takes a 24 bit .bmp image and prints the contents of the file and info header
*
* @author nstavr04,mvasil17
* @bug No known bugs.
*/

#include "bmp.h"
#include "bmplib.h"

void imageInfo(BITMAPFILEHEADER bitmapFileHeader, BITMAPINFOHEADER bitmapInfoHeader) {

    printf("BITMAP_FILE_HEADER\n");
    printf("==================\n");

    printf("bfType: %c%c\n", bitmapFileHeader.bfType1, bitmapFileHeader.bfType2);
    printf("bfSize: %d\n", bitmapFileHeader.bfSize);
    printf("bfReserved1: %d\n", bitmapFileHeader.bfReserved1);
    printf("bfReserved2: %d\n", bitmapFileHeader.bfReserved2);
    printf("bfOffBits: %lu\n\n", bitmapFileHeader.bfOffBits);

    printf("BITMAP_INFO_HEADER\n");
    printf("==================\n");

    printf("biSize: %d\n", bitmapInfoHeader.biSize);
    printf("biWidth: %ld\n", bitmapInfoHeader.biWidth);
    printf("biHeight: %ld\n", bitmapInfoHeader.biHeight);
    printf("biPlanes: %d\n", bitmapInfoHeader.biPlanes);
    printf("biBitCount: %d\n", bitmapInfoHeader.biBitCount);
    printf("biCompression: %d\n", bitmapInfoHeader.biCompression);
    printf("biSizeImage: %d\n", bitmapInfoHeader.biSizeImage);
    printf("biXPelsPerMeter: %ld\n", bitmapInfoHeader.biXPixPerMeter);
    printf("biYPelsPerMeter: %ld\n", bitmapInfoHeader.biYPixPerMeter);
    printf("biClrUsed: %lu\n", bitmapInfoHeader.biClrUsed);
    printf("biClrImportand: %lu\n", bitmapInfoHeader.biClrImportant);

}
//Driver function
#ifdef ListDEBUG
int main(int argc, char *argv[]) {

    unsigned char *bitmapData;

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;


    int counter = 2;  // program argument 1 Is the operations. (-list)
        while (counter < argc) {
            bitmapData = LoadBitmapFile(argv[counter], &bitmapFileHeader, &bitmapInfoHeader);

            if (bitmapData != NULL) {  // If bitmapData == null, it means that the file given is not valid, or there is no memory to allocate
                imageInfo(bitmapFileHeader, bitmapInfoHeader);
                if (counter != (argc - 1)) {
                    printf("\n***************************************************************************\n");
                }
            }
            counter++;
        }

}
#endif