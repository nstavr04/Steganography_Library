/* DecodeStegano.c
* Copyright (C) 2020 nstavr04 mvasil17
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License.
*/

#include "bmp.h"
#include "bmplib.h"

/**
 *
 * @param pixels
 * @param SecretFileHeader
 * @param SecretInfoHeader
 * @param fp
 * @param nbBits
 */
void decodeStegano(PIXEL *pixels, BITMAPFILEHEADER *SecretFileHeader, BITMAPINFOHEADER *SecretInfoHeader, FILE *fp,char *nbBits) {

    fwrite(SecretFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(SecretInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    unsigned char R;
    unsigned char G;
    unsigned char B;

    for (unsigned int i = 0; i < ((SecretInfoHeader->biSizeImage)/3); i++){

        if(*nbBits == '1'){

            R = pixels[i].red << 7;
            G = pixels[i].green << 7;
            B = pixels[i].blue << 7;

        }
        else if(*nbBits == '2'){

            R = pixels[i].red << 6;
            G = pixels[i].green << 6;
            B = pixels[i].blue << 6;

        }
        else if(*nbBits == '3'){

            R = pixels[i].red << 5;
            G = pixels[i].green << 5;
            B = pixels[i].blue << 5;

        }
        else{

            R = pixels[i].red << 4;
            G = pixels[i].green << 4;
            B = pixels[i].blue << 4;

        }

        fwrite(&R,1,1,fp);
        fwrite(&G,1,1,fp);
        fwrite(&B,1,1,fp);

    }

}