//
// Created by 35799 on 19/11/2020.
//

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