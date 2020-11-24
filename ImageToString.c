/**
* @file ImageToString.c
* @brief The class that decodes an encrypted message thats in an image back to its .txt format
*
* @author nstavr04
* @bug No known bugs.
*/

#include "bmp.h"
#include "bmplib.h"

void ImageToString(unsigned char *bitmapData, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader) {

    // File "outputText.txt" Where we will write the text back
    FILE *fp = NULL;
    fp = fopen("outputText", "w");
    if (fp == NULL) {
        printf("unable to open");
        exit(-1);
    }

    char curChar;
    int number1 = 0;
    int number2 = 0;
    int number3 = 0;
    int number4 = 0;
    int number5 = 0;
    int number6 = 0;
    int number7 = 0;
    int number8 = 0;

//    //Proceed pixel by pixel. Every 8 pixels we got a char
//    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 24) {
//
//        number1 = ((bitmapData[i]));
//        number2 = ((bitmapData[i + 3]) >> 1);
//        number3 = ((bitmapData[i + 6]) >> 2);
//        number4 = ((bitmapData[i + 9]) >> 3);
//        number5 = ((bitmapData[i + 12]) >> 4);
//        number6 = ((bitmapData[i + 15]) >> 5);
//        number7 = ((bitmapData[i + 18]) >> 6);
//        number8 = ((bitmapData[i + 21]) >> 7);
//
//        //Create each char by adding the 8 pixels of the image
//        curChar = number1 + number2 + number3 + number4 + number5 + number6 + number7 + number8;
//
//        //Put the character into the file
//        fprintf(fp, "%c", curChar);
//
//    }

    PIXEL *pixels;
    pixels = getEachPixel(bitmapData,bitmapInfoHeader);
//
//        PIXEL **pixels2D = (PIXEL **)malloc(bitmapInfoHeader->biHeight * sizeof(PIXEL *));
//    for(int i=0;i<bitmapInfoHeader->biHeight;i++){
//        pixels2D[i] = (PIXEL *)malloc(bitmapInfoHeader->biWidth * sizeof(PIXEL));
//    }

//   int k=0;

//    for(int j=0;j<bitmapInfoHeader->biWidth;j++){
//        for(int i=0;i<bitmapInfoHeader->biHeight;i++){
//
//
//           // pixels2D[i][j].red = (pixels[k].red)/128;
//           // k++;
//
//            pixels2D[i][j].red = (pixels[bitmapInfoHeader->biHeight*j + i].red)/128;
//
//        }
//
//    }





    unsigned char curChar2 = 0x00;
    unsigned char curCharTemp;
    int cnt = 0;

//    for(int i=0;i<bitmapInfoHeader->biHeight;i++) {
//        for (int j = 0; j < bitmapInfoHeader->biWidth; j++) {
//
//            if(cnt == 8){
//                cnt=0;
//                fprintf(fp,"%c",curChar2);
//                curChar2 = 0x00;
//            }
//
//
//            curCharTemp = pixels2D[i][j].red;
//
//            curChar2 = (curChar2 << 1) | curCharTemp;
//
//            cnt++;
//
//        }
//    }

    for(int i=0;i<bitmapInfoHeader->biWidth;i++) {
        for (int j = 0; j < bitmapInfoHeader->biHeight; j++) {

            curCharTemp = ((pixels + (bitmapInfoHeader->biHeight - j - 1)*bitmapInfoHeader->biWidth + i)->red) / 128;

            curChar2 = (curChar2 << 1) | curCharTemp;

            cnt++;

            if(cnt == 8){
                cnt=0;
                fprintf(fp,"%c",curChar2);
                curChar2 = 0x00;
            }

        }
    }

    fprintf(fp,"%c",'\0');
    fclose(fp);



}