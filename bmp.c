//
// Created by mvasil17 & nstavr04 on 18/11/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"


unsigned int ReadLE4(FILE *fp);

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    int imageIdx=0;  //image index counter
//    unsigned char tempRGB;  //our swap variable

    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType1 !=0x42 && bitmapFileHeader.bfType2 !=0x4D)     //0x42 = 'B' && 0x4D = 'M'
    {
        fclose(filePtr);
        return NULL;
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);

//    //move file point to the begging of bitmap data
//    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    //read in the bitmap image data
    fread(bitmapImage,3 ,bitmapInfoHeader->biSizeImage,filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    //swap the r and b values to get RGB (bitmap is BGR)
//    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3) // fixed semicolon
//    {
//        tempRGB = bitmapImage[imageIdx];
//        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
//        bitmapImage[imageIdx + 2] = tempRGB;
//    }

    //close file and return bitmap iamge data
    fclose(filePtr);
    return bitmapImage;
}

int main(){


    BITMAPFILEHEADER b1;

    BITMAPINFOHEADER b2;

    printf("%llu\n", sizeof(b1));

    printf("%llu\n", sizeof(b2));


    return 0;

}


