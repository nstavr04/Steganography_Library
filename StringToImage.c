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

    PIXEL *pixels;
    pixels = getEachPixel(bitmapData, bitmapInfoHeader);


    //Working but not the way we want to put them from top right
//    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3) {
//
//        *(bitmapData + i) = 128 * getBit(array, i/3);
//        *(bitmapData + i + 1) = 128 * getBit(array, i/3);
//        *(bitmapData + i + 2) = 128 * getBit(array, i/3);
//    }
//
//    fwrite(bitmapData, bitmapInfoHeader->biSizeImage, 1, newFile);
//    for (int i = 0; i < bitmapInfoHeader->biWidth; i++) {
//        for (int j = 0; j < bitmapInfoHeader->biHeight; j++) {
//            //for(int j=0;j<bitmapInfoHeader->biWidth;j++){
//            pixels[(bitmapInfoHeader->biHeight - j - 1)*bitmapInfoHeader->biWidth + i].red = 128 * getBit(array, bitmapInfoHeader->biHeight * i + j);
//            pixels[(bitmapInfoHeader->biHeight - j - 1)*bitmapInfoHeader->biWidth + i].green = 128 * getBit(array, bitmapInfoHeader->biHeight * i + j);
//            pixels[(bitmapInfoHeader->biHeight - j - 1)*bitmapInfoHeader->biWidth + i].blue = 128 * getBit(array, bitmapInfoHeader->biHeight * i + j);
//
//            //3 because rgb is 3 bytes
//            //fwrite(pixels, 3, 1, newFile);
//
//        }
//
//    }

    int cnt = 0;
    int cnt2 = 0;

    for (int i = 0; i < bitmapInfoHeader->biHeight; i++) {
        for (int j = 0; j < bitmapInfoHeader->biWidth; j++) {
            //for(int j=0;j<bitmapInfoHeader->biWidth;j++){
          bitmapData[cnt2] = 128 * getBit(array, bitmapInfoHeader->biHeight * i + j);
           //pixels[cnt].green = 128 * getBit(array, bitmapInfoHeader->biHeight * i + j);
           //pixels[cnt].blue = 128 * getBit(array, bitmapInfoHeader->biHeight * i + j);
            cnt2++;

            //3 because rgb is 3 bytes
            //fwrite(pixels, 3, 1, newFile);

        }

    }

    cnt2=0;

    for(int i=bitmapInfoHeader->biHeight-1;i>=0;i--){
        for(int j=0;j<bitmapInfoHeader->biWidth;j++){

            if(bitmapData[j+i*bitmapInfoHeader->biWidth] != 0) {

                pixels[cnt].red = bitmapData[j + i * bitmapInfoHeader->biWidth];
                pixels[cnt].green = bitmapData[j + i * bitmapInfoHeader->biWidth];
                pixels[cnt].blue = bitmapData[j + i * bitmapInfoHeader->biWidth];
            }

            cnt++;
        }
    }


    fwrite(pixels,bitmapInfoHeader->biSizeImage,1,newFile);

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