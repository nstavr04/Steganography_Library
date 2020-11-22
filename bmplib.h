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

/** @brief This function reads the file *fp.
 *
 * It reads until the end or until the first '\n'. It depends on the
 * flag. If the flag is 0 it reads untill the first '/n'
 * Else it reads the file as a whole string. It mallocs
 * the suitable memory.
 *
 * @param fp
 * @param size
 * @param flag
 * @return the string
 */
char *inputString(FILE *fp, size_t size, int flag);

#endif //HW4_BMPLIB_H
