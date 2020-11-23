//
// Created by 35799 on 19/11/2020.
//

#include "bmp.h"
#include "bmplib.h"

void textToImage(unsigned char *bitmapData, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader,
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

//    int n=0;
//
//    while (*(array + n/8) != '\0' && n < bitmapInfoHeader->biSizeImage){
//
//        //printf("%d",getBit(array,n));
//
//            *(bitmapData+n) = 128*getBit(array,n);
//            *(bitmapData+n+1) = 128*getBit(array,n);
//            *(bitmapData+n+2) = 128*getBit(array,n);
//
//        n+=3;
//    }

//    for(int i=0;i<bitmapInfoHeader->biHeight;i++){
//        for(int j=0;j<bitmapInfoHeader->biWidth;j++){
//
//            *(bitmapData + i*j) = 128*getBit(array,bitmapInfoHeader->biHeight*i + j);
//            *(bitmapData+i*j +1) = 128*getBit(array,bitmapInfoHeader->biHeight*i + j);
//            *(bitmapData+i*j +2) = 128*getBit(array,bitmapInfoHeader->biHeight*i + j);
//
//        }
//    }

    //Working but not the way we want to put them from top right
    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3) {

        *(bitmapData + i) = 128 * getBit(array, i);
        *(bitmapData + i + 1) = 128 * getBit(array, i);
        *(bitmapData + i + 2) = 128 * getBit(array, i);
    }


    //Dynamically declaring a 2d array where we will save in correct order our pixels

//    PIXEL **pixels2D = (PIXEL **)malloc(bitmapInfoHeader->biHeight * sizeof(PIXEL *));
//    for(int i=0;i<bitmapInfoHeader->biHeight;i++){
//        pixels2D[i] = (PIXEL *)malloc(bitmapInfoHeader->biWidth * sizeof(PIXEL));
//    }

//    int k=0;
//
//    //For every pixel , read the appropriate char and add the correct color (black or white)
//    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage)/3); i++) {
//
//        pixels2D[i % (bitmapInfoHeader->biWidth)][k] = pixels[k];
//
//        //Moving column every biHeight
//        if(i%(bitmapInfoHeader->biHeight) == 0 && i != 0 ){
//            k++;
//        }
//    }
//    int counterTemp = 0;
//    for(int i=0;i<bitmapInfoHeader->biWidth;i++){
//        for(int j=0;j<bitmapInfoHeader->biHeight;j++){
//            pixels2D[j][i] = pixels[counterTemp];
//            counterTemp++;
//        }
//    }
//
//    for(int i=0;i<bitmapInfoHeader->biWidth;i++){
//        for(int j=0;j<bitmapInfoHeader->biHeight;j++){
//            fwrite(&pixels2D[j][i], 1, 1, newFile);
//        }
//    }


    fwrite(bitmapData, bitmapInfoHeader->biSizeImage, 1, newFile);

//    public void rotateRight() {
//        Color[][] copy = shapeCopy();
//        int c = copy[0].length-1;
//        for(int i = c; i >= 0; i--) {
//            Color[] col = copyCol(i, copy);
//            for(int j = 0; j < col.length; j++) {
//                shape[c-i][j] = col[j];
//            }
//        }
//    }
//
//    private Color[] copyCol(int col, Color[][] shape) {
//        Color[] column = new Color[shape.length];
//        for(int i = 0; i < shape.length; i++)
//            column[i] = shape[i][col];
//        return column;
//    }
//    private Color[] copyRow(int row, Color[][] shape) {
//        Color[] rows = new Color[shape[0].length];
//        for(int i = 0; i < shape[0].length; i++)
//            rows[i] = shape[row][i];
//        return rows;
//    }

}