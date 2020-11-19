//
// Created by mvasil17 & nstavr04 on 19/11/2020.
//
#include "bmp.h"
int main (int argc, char *argv[]){

    BITMAPFILEHEADER b1;

    BITMAPINFOHEADER b2;

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

    unsigned char *bitmapData;

    bitmapData = LoadBitmapFile("image6.bmp", &bitmapFileHeader, &bitmapInfoHeader);

    if (strcmp(argv[1], "-list") == 0){
        imageInfo(bitmapFileHeader, bitmapInfoHeader);  // Operation 1
    }

    else if (strcmp(argv[1], "-grayscale") == 0 ){
        //Operation 2
    }

    else if (strcmp(argv[1], "-encodeStegano") == 0){
        //Operation 3
    }

    else if (strcmp(argv[1], "-decodeStegano") == 0){
        // Operation 4
    }

    else if (strcmp(argv[1], "-encodeText") == 0){
        // Operation 5
    }

    else if (strcmp(argv[1], "-decodeText") == 0){
        //Operation 6
    }

    else if (strcmp(argv[1], "-stringToImage") == 0){
        //Operation 7
    }

    else if (strcmp(argv[1], "-imageToString") == 0){
        //Operation 8
    }





    return 0;
}

