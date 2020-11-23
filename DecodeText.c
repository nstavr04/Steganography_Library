//
// Created by mvasil17 on 19/11/2020.
//

#include "bmp.h"
#include "bmplib.h"
#include <math.h>

void stegaEncryptDecodeText(unsigned char *bitmapData, BITMAPINFOHEADER *bitmapInfoHeader, int systemKey, int length, FILE *outputFile){

    int *fn;

    fn = createPermutationFunction(bitmapInfoHeader->biSizeImage, systemKey);    // system-key-integer

    int counter = 7;

    int oneChar = 0;

    for (int i = 0; i < length*8; i++) {

        int o = fn[i];

        unsigned char currentByte = bitmapData[o];
        int res = (currentByte & 1) * pow(2, counter);
        oneChar = oneChar + res;

        if (counter == 0) {
            counter = 7;
            fprintf(outputFile, "%c", oneChar);
            oneChar = 0;
        } else {
            counter--;
        }
    }
}