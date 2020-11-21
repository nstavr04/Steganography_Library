//
// Created by 35799 on 19/11/2020.
//

#include "bmp.h"
#include "bmplib.h"

void encodeStegano(PIXEL *imagePixels,PIXEL *pixels, BITMAPFILEHEADER *SecretFileHeader, BITMAPINFOHEADER *SecretInfoHeader, FILE *fp,char *nbBits){

    fwrite(SecretFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(SecretInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    unsigned char msbR;
    unsigned char msbG;
    unsigned char msbB;

    //We need to replace the nbBits lsb of the original image with the nbBits msb of the secret image
    for (int i = 0; i < ((SecretInfoHeader->biSizeImage)/3); i++){

        if(*nbBits == '1'){

            //Getting the msb
            msbR = (imagePixels + i)->red & 0x80;
            msbG = (imagePixels + i)->green & 0x80;
            msbB = (imagePixels + i)->blue & 0x80;

            //Shifting the msb to be applied in the lsb of pixels
            msbR = msbR >> 7;
            msbG = msbG >> 7;
            msbB = msbB >> 7;

        }
        else if(*nbBits == '2') {

            //Getting the msb
            msbR = (imagePixels + i)->red & 0xC0;
            msbG = (imagePixels + i)->green & 0xC0;
            msbB = (imagePixels + i)->blue & 0xC0;

            //Shifting the msb to be applied in the lsb of pixels
            msbR = msbR >> 6;
            msbG = msbG >> 6;
            msbB = msbB >> 6;

        }

        else if(*nbBits == '3'){

            //Getting the msb
            msbR = (imagePixels + i)->red & 0xE0;
            msbG = (imagePixels + i)->green & 0xE0;
            msbB = (imagePixels + i)->blue & 0xE0;

            //Shifting the msb to be applied in the lsb of pixels
            msbR = msbR >> 5;
            msbG = msbG >> 5;
            msbB = msbB >> 5;

        }

        else{

            //Getting the msb
            msbR = (imagePixels + i)->red & 0xF0;
            msbG = (imagePixels + i)->green & 0xF0;
            msbB = (imagePixels + i)->blue & 0xF0;

            //Shifting the msb to be applied in the lsb of pixels
            msbR = msbR >> 4;
            msbG = msbG >> 4;
            msbB = msbB >> 4;

        }

        //Applying the msb to the lsb of pixels
        //NEEDS FIXING
        (pixels + i)->red = (pixels + i)->red & msbR;
        (pixels + i)->green = (pixels + i)->green & msbR;
        (pixels + i)->blue = (pixels + i)->blue & msbR;

        fwrite(&pixels[i].blue,1,1,fp);
        fwrite(&pixels[i].green,1,1,fp);
        fwrite(&pixels[i].red,1,1,fp);

    }

}
