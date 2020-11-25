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
    free(array);
    fclose(fileText);

}

//Driver function
#ifdef StringToImageDEBUG
int main(int argc, char *argv[]){

    unsigned char *bitmapData;

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

    //The file to save the Image to new-
    //5 Bytes because we need the \0 too
    char* newFileName = (char *)malloc(strlen(argv[2]) + 5);
    strcpy(newFileName,"new-");
    strcat(newFileName, argv[2]);

    // Open the file that contains the text that needs to be encrypted
    FILE *fileText = NULL;
    fileText = fopen(argv[3], "r");
    if (fileText == NULL) {
        printf("unable to open");
        exit(-1);
    }

    //Calculating the length of the text of the file
    int c;
    int cnt = 0;

    while((c = fgetc(fileText)) != EOF){
        cnt++;
    }

    //Closing text pointer to open it again after for inputting the chars data into the image
    fclose(fileText);

    // Open the new file (create it)
    FILE *newFile = NULL;
    newFile = fopen(newFileName, "wb");
    if (newFile == NULL) {
        printf("unable to open");
        exit(-1);
    }

    bitmapData = LoadBitmapFile(argv[2], &bitmapFileHeader, &bitmapInfoHeader);

    //Freeing all the image pixels and allocating the memory with 0
    free(bitmapData);

    bitmapData = (unsigned char *)calloc(bitmapInfoHeader.biSizeImage,sizeof(unsigned  char));

    StringToImage(bitmapData, &bitmapFileHeader, &bitmapInfoHeader,newFile,argv[3],cnt);

}
#endif