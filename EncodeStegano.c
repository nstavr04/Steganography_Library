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
    for (unsigned int i = 0; i < ((SecretInfoHeader->biSizeImage)/3); i++){

        if(*nbBits == '1'){

            //Getting the msb
            msbR = (imagePixels[i]).red & 0x80;
            msbG = (imagePixels[i]).green & 0x80;
            msbB = (imagePixels[i]).blue & 0x80;

            //Shifting the msb to be applied in the lsb of pixels
            msbR = msbR >> 7;
            msbG = msbG >> 7;
            msbB = msbB >> 7;

            //Making 1 the 7 msb
            msbR = msbR | 0xFE;
            msbG = msbG | 0xFE;
            msbB = msbB | 0xFE;

            (pixels + i)->red = (pixels + i)->red | 0x01;
            (pixels + i)->green = (pixels + i)->green | 0x01;
            (pixels + i)->blue = (pixels + i)->blue | 0x01;

        }
        else if(*nbBits == '2') {

            //Getting the msb
            msbR = (imagePixels[i]).red & 0xC0;
            msbG = (imagePixels[i]).green & 0xC0;
            msbB = (imagePixels[i]).blue & 0xC0;

            //Shifting the msb to be applied in the lsb of pixels
            msbR = msbR >> 6;
            msbG = msbG >> 6;
            msbB = msbB >> 6;

            //Making 1 the 6 msb
            msbR = msbR | 0xFC;
            msbG = msbG | 0xFC;
            msbB = msbB | 0xFC;

            (pixels + i)->red = (pixels + i)->red | 0x03;
            (pixels + i)->green = (pixels + i)->green | 0x03;
            (pixels + i)->blue = (pixels + i)->blue | 0x03;

        }

        else if(*nbBits == '3'){

            //Getting the msb
            msbR = (imagePixels[i]).red & 0xE0;
            msbG = (imagePixels[i]).green & 0xE0;
            msbB = (imagePixels[i]).blue & 0xE0;

            //Shifting the msb to be applied in the lsb of pixels
            msbR = msbR >> 5;
            msbG = msbG >> 5;
            msbB = msbB >> 5;

            //Making 1 the 5 msb
            msbR = msbR | 0xF8;
            msbG = msbG | 0xF8;
            msbB = msbB | 0xF8;

            (pixels + i)->red = (pixels + i)->red | 0x09;
            (pixels + i)->green = (pixels + i)->green | 0x09;
            (pixels + i)->blue = (pixels + i)->blue | 0x09;

        }

        else{

            //Getting the msb
            msbR = (imagePixels[i]).red & 0xF0;
            msbG = (imagePixels[i]).green & 0xF0;
            msbB = (imagePixels[i]).blue & 0xF0;

            //Shifting the msb to be applied in the lsb of pixels
            msbR = msbR >> 4;
            msbG = msbG >> 4;
            msbB = msbB >> 4;

            //Making 1 the 4 msb
            msbR = msbR | 0xF0;
            msbG = msbG | 0xF0;
            msbB = msbB | 0xF0;

            (pixels + i)->red = (pixels + i)->red | 0x0F;
            (pixels + i)->green = (pixels + i)->green | 0x0F;
            (pixels + i)->blue = (pixels + i)->blue | 0x0F;

        }

        //Applying the msb to the lsb of pixels
        (pixels + i)->red = (pixels + i)->red & msbR;
        (pixels + i)->green = (pixels + i)->green & msbG;
        (pixels + i)->blue = (pixels + i)->blue & msbB;

        fwrite(&pixels[i].red,1,1,fp);
        fwrite(&pixels[i].green,1,1,fp);
        fwrite(&pixels[i].blue,1,1,fp);

    }

}
