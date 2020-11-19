//
// Created by mvasil17 & nstavr04 on 19/11/2020.
//
#include "bmp.h"

int main(int argc, char *argv[]) {

    BITMAPFILEHEADER b1;

    BITMAPINFOHEADER b2;

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

    unsigned char *bitmapData;


    if (argc < 3) {
        return 0;
    }


    if (strcmp(argv[1], "-list") == 0) {    // Operation 1
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
    } else if (strcmp(argv[1], "-grayscale") == 0) {
        //Operation 2
    } else if (strcmp(argv[1], "-encodeStegano") == 0) {
        //Operation 3
    } else if (strcmp(argv[1], "-decodeStegano") == 0) {
        // Operation 4
    } else if (strcmp(argv[1], "-encodeText") == 0) {
        // Operation 5
    } else if (strcmp(argv[1], "-decodeText") == 0) {
        //Operation 6
    } else if (strcmp(argv[1], "-stringToImage") == 0) {
        //Operation 7
    } else if (strcmp(argv[1], "-imageToString") == 0) {
        //Operation 8
    }


    return 0;

}