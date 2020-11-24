/**
* @file StringToImage.c
* @brief The class that hides the a text file into an image.
*
* @author nstavr04
* @bug No known bugs.
*/

#include "bmp.h"
#include "bmplib.h"

void StringToImage(unsigned char *bitmapData, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader,
                   FILE *newFile, char *arg, int length) {

    //Writing the header of the image since we want it to remain the same
    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, newFile);    // Write BITMAPFILEHEADER to the new file
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, newFile);    // Write BITMAPINFOHEADER to the new file

    // Open the file that contains the text that needs to be encrypted
    FILE *fileText = NULL;
    fileText = fopen(arg, "r");
    if (fileText == NULL) {
        printf("unable to open");
        exit(-1);
    }

    char *array;

    //Used to save the text file into an array
    array = inputString(fileText, length, 1);

    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3) {

        *(bitmapData + i) = 128 * getBit(array, i/3);
        *(bitmapData + i + 1) = 128 * getBit(array, i/3);
        *(bitmapData + i + 2) = 128 * getBit(array, i/3);

        }

    fwrite(bitmapData, bitmapInfoHeader->biSizeImage, 1, newFile);

}