/**
* @file bmplib.h
* @brief The header file is used to connect all .c .bmp image manipulation functions together into one library
*
* @author nstavr04, mvasil17
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


/** @brief This function encodes (hides) an image inside another image using its 1-4 msb
 *
 * @param imagePixels The structure of the pixels of the image we want to hide
 * @param pixels The structure of the pixels of the other image , the visible one
 * @param bitmapFileHeader the bitmap file header
 * @param bitmapInfoHeader  the bitmap info header
 * @param fp the file pointer
 * @param nbBits how many msb of the image we want to hide (1-4)
 */
void encodeStegano(PIXEL *imagePixels,PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp,char *nbBits);


/** @brief This function decodes the hidden image from another image. We need to use the encodeStegano first if we want to decode.
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


/** @brief get n bit content from message m
 *
 * @param m pointer to the message
 * @param n which bit content to return
 * @return the content of n bit , 0 or 1
 */
int getBit(unsigned char *m, int n);


/** @brief This function encodes(hides) a text inside a .bmp picture.
 *
 * @param textToBeEncoded the text that needs to be encoded
 * @param bitmapData the data of the .bmp picture in bytes
 * @param bitmapInfoHeader the info header
 * @param newFile the file that
 */
void stegaEncryptEncodeText(char *textToBeEncoded, unsigned char *bitmapData, int systemKey, BITMAPINFOHEADER *bitmapInfoHeader, FILE *newFile);

/** @brief This function decodes the hidden text inside a .bmp picture and makes back to its .txt format
 *
 * @param bitmapData he data of the .bmp picture in byte
 * @param bitmapInfoHeader the info header
 * @param systemKey the key that is used as seed to create pseudorandom numbers
 * @param length the length of the text that needs to be decoded (MUST BE CORRECT)
 * @param outputFile the file that we write
 */
void stegaEncryptDecodeText(unsigned char *bitmapData, BITMAPINFOHEADER *bitmapInfoHeader, int systemKey, int length, FILE *outputFile);


/** @brief This function creates pseudorandom permutations using a system-key integer
 *
 * @param N the size of image in bytes
 * @param systemkey the key that is used as seed to create pseudorandom numbers
 * @return the int table with all the permutations
 */
int *createPermutationFunction(int N, unsigned int systemkey);

/** @brief This function reads a text file and encodes it into an image creating a black and grey image.
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

/** @brief This function is used to decrypt the hidden message from a .bmp image
 *
 * @param bitmapData a pointer to our picture data
 * @param bitmapFileHeader the bitmap file header
 * @param bitmapInfoHeader the bitmap info header
 */
void ImageToString(unsigned char *bitmapData, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader);

/** @brief This function is used to encrypt a message into a .bmp image
 *
 * @param pixels the table with all the pixels of the image
 * @param bitmapFileHeader the bitmap file header
 * @param bitmapInfoHeader the bitmap info header
 * @param fp the file that we apply on, and write the new .bmp image
 */
void makePictureNegative(PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp);

#endif //HW4_BMPLIB_H
