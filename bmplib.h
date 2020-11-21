//
// Created by 35799 on 19/11/2020.
//

#ifndef HW4_BMPLIB_H
#define HW4_BMPLIB_H

/** @brief This functions prints all the info regarding the bitmap file header and info
 *
 * @param bitmapFileHeader
 * @param bitmapInfoHeader
 */
void imageInfo(BITMAPFILEHEADER bitmapFileHeader, BITMAPINFOHEADER bitmapInfoHeader);


/** @brief This function convers a picture to its grayscaled one
 *
 * It takes as input all the necessary parameters to convert a picture, and write it back to the file.
 *
 * @param pixels
 * @param bitmapFileHeader
 * @param bitmapInfoHeader
 * @param fp
 */
void makePictureGrayScaled(PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp);

void encodeStegano(PIXEL *imagePixels,PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp,char *nbBits);

void decodeStegano(PIXEL *pixels, BITMAPFILEHEADER *SecretFileHeader, BITMAPINFOHEADER *SecretInfoHeader, FILE *fp,char *nbBits);

#endif //HW4_BMPLIB_H
