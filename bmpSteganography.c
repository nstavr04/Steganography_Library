//
// Created by mvasil17 & nstavr04 on 19/11/2020.
//
#include "bmp.h"
#include "bmplib.h"

int main(int argc, char *argv[]) {

    BITMAPFILEHEADER b1;

    BITMAPINFOHEADER b2;

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

    unsigned char *bitmapData;

    BITMAPINFOHEADER secretInfoHeader;

    BITMAPFILEHEADER  secretFileHeader;

    //Used in encodeImage
    unsigned char *secretImage;


    if (argc < 3) {
        return 0;
    }

    if (strcmp(argv[1], "-list") == 0) {    // Operation 1
        int counter = 2;  // program argument 1 Is the operations. (-list)
        while (counter < argc) {
            bitmapData = LoadBitmapFile(argv[counter], &bitmapFileHeader, &bitmapInfoHeader);

            if (bitmapData != NULL) {  // If bitmapData == null, it means that the file given is not valid, or there is no memory to allocate
                imageInfo(bitmapFileHeader, bitmapInfoHeader);
                if (counter != (argc - 1)) {
                    printf("\n***************************************************************************\n");
                }
            }
            counter++;
        }
    } else if (strcmp(argv[1], "-grayscale") == 0) {    //Operation 2

        PIXEL *pixels;
        int counter = 2;  // program argument 1 Is the operations. (-grayscale)
        while (counter < argc) {


            bitmapData = LoadBitmapFile(argv[counter], &bitmapFileHeader, &bitmapInfoHeader);

            FILE *fp = fopen(argv[counter], "wb");

             pixels = getEachPixel(bitmapData, &bitmapInfoHeader);

             makePictureGrayScaled(pixels, &bitmapFileHeader, &bitmapInfoHeader, fp);

            counter++;

            fclose(fp);
        }
        free(pixels);
    } else if (strcmp(argv[1], "-encodeStegano") == 0) { //Operation 3

        PIXEL *pixels;

        PIXEL *imagePixels;

        //Checking if nbBits are correct
        if(strcmp(argv[2] , "1") != 0 && strcmp(argv[2] , "2") != 0 && strcmp(argv[2] , "3") != 0 && strcmp(argv[2] , "4") != 0){
            printf("Wrong nbBits input. nbBits should be 1-4");
            exit(-1);
        }

            //Save the data of the first image in bitmapData
            bitmapData = LoadBitmapFile(argv[3], &bitmapFileHeader, &bitmapInfoHeader);

            //Save the data of the secret Image
            secretImage = LoadBitmapFile(argv[4], &secretFileHeader, &secretInfoHeader);

            //Checking that the images have the same dimentions
            if(bitmapInfoHeader.biWidth != secretInfoHeader.biWidth && bitmapInfoHeader.biHeight != secretInfoHeader.biHeight){
                printf("Images need to have the same dimentions");
                exit(-1);
            }

            //The file to save the Image to new-
            //5 Bytes because we need the \0 too
            char* newFile = malloc(strlen(argv[3]) + 5);
            strcpy(newFile,"new-");
            strcat(newFile, argv[3]);

            FILE *fp = fopen(newFile, "wb");

            pixels = getEachPixel(bitmapData, &bitmapInfoHeader);

            imagePixels = getEachPixel(secretImage,&secretInfoHeader);

            encodeStegano(imagePixels,pixels, &bitmapFileHeader, &bitmapInfoHeader, fp,argv[2]);

        free(pixels);
        free(imagePixels);
        free(newFile);

        fclose(fp);

    } else if (strcmp(argv[1], "-decodeStegano") == 0) { // Operation 4

        PIXEL *pixels;

        //Checking if nbBits are correct
        if(strcmp(argv[2] , "1") != 0 && strcmp(argv[2] , "2") != 0 && strcmp(argv[2] , "3") != 0 && strcmp(argv[2] , "4") != 0){
            printf("Wrong nbBits input. nbBits should be 1-4");
            exit(-1);
        }

        //Save the data of the first image in bitmapData
        bitmapData = LoadBitmapFile(argv[3], &bitmapFileHeader, &bitmapInfoHeader);

        //The file to save the Image to new-
        //5 Bytes because we need the \0 too
        char* newFile = malloc(strlen(argv[3]) + 5);
        strcpy(newFile,"new-");
        strcat(newFile, argv[3]);

        FILE *fp = fopen(newFile, "wb");

        pixels = getEachPixel(bitmapData, &bitmapInfoHeader);

        decodeStegano(pixels, &bitmapFileHeader, &bitmapInfoHeader, fp,argv[2]);

        free(pixels);
        free(newFile);

        fclose(fp);

    } else if (strcmp(argv[1], "-encodeText") == 0) {
        // Operation 5
    } else if (strcmp(argv[1], "-decodeText") == 0) {
        //Operation 6
    } else if (strcmp(argv[1], "-stringToImage") == 0) {
        //Operation 7
    } else if (strcmp(argv[1], "-imageToString") == 0) {
        //Operation 8
    }


    return 0;

}