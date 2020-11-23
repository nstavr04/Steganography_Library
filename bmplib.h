/**
* @file bmplib.h
* @brief The header file is used to connect all .c .bmp image manipulation functions together into one library
*
* @author nstavr04,mvasil17
* @bug No known bugs.
*/

#ifndef HW4_BMPLIB_H
#define HW4_BMPLIB_H

/** @brief This functions prints all the info regarding the bitmap file header and info
 *
 * @param bitmapFileHeader the bitmap file header
 * @param bitmapInfoHeader the bitmap info header
 */
void imageInfo(BITMAPFILEHEADER bitmapFileHeader, BITMAPINFOHEADER bitmapInfoHeader);


/** @brief This function converts a picture to its grayscaled one
 *
 * It takes as input all the necessary parameters to convert a picture, and write it back to the file.
 *
 * @param pixels The structure of the pixels of the image
 * @param bitmapFileHeader the bitmap file header
 * @param bitmapInfoHeader the bitmap info header
 * @param fp the file pointer
 */
void makePictureGrayScaled(PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp);

/**
 * @brief This function encodes (hides) an image inside another image using its 1-4 msb
 *
 * @param imagePixels The structure of the pixels of the image we want to hide
 * @param pixels The structure of the pixels of the other image , the visible one
 * @param bitmapFileHeader the bitmap file header
 * @param bitmapInfoHeader  the bitmap info header
 * @param fp the file pointer
 * @param nbBits how many msb of the image we want to hide (1-4)
 */
void encodeStegano(PIXEL *imagePixels,PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp,char *nbBits);

/**
 * @brief This function decodes the hidden image from another image. We need to use the encodeStegano first if we want to decode.
 *
 * @param pixels The structure of the pixels of the current image
 * @param SecretFileHeader the bitmap file header
 * @param SecretInfoHeader the bitmap info header
 * @param fp the file pointer
 * @param nbBits how many lsb of this image will be removed to be used as the msb of our hidden image, to reveal it. Needs to be the same as the amount of bits we hid in encoding
 */
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

/**
 * @brief This function reads a text file and encodes it into an image creating a black and grey image.
 *
 * If the text file is larger than the size of the image we will ignore the characters when the image is full.
 * If the text file is smaller than the size of the image, the remaining pixels will be black
 *
 * @param bitmapData a pointer to our picture data
 * @param bitmapFileHeader the bitmap file header
 * @param bitmapInfoHeader the bitmap info header
 * @param newFile the file pointer to the new image that we will create
 */
void StringToImage(unsigned char *bitmapData, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER  *bitmapInfoHeader, FILE *newFile,char *arg,int length);

/**
 * @brief get n bit content from message m
 *
 * @param m pointer to the message
 * @param n which bit content to return
 * @return the content of n bit , 0 or 1
 */
int getBit(char *m, int n);

/**
 * @brief
 *
 * @param textToBeEncoded
 * @param bitmapData
 * @param bitmapInfoHeader
 * @param newFile
 */
void stegaEncryptEncodeText(char *textToBeEncoded, unsigned char *bitmapData, BITMAPINFOHEADER *bitmapInfoHeader, FILE *newFile);

void stegaEncryptDecodeText(unsigned char *bitmapData, int length, FILE *outputFile);

#endif //HW4_BMPLIB_H
