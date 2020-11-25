/* bmpSteganography.c
* Copyright (C) 2020 nstavr04 mvasil17
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License.
*/

/**
* @file bmpSteganography.c
* @brief The main class of our .bmp manipulation program
*
* This class is the main class of our program which we will execute with the appropriate -option every time
 * accordingly to how we want to manipulate an image
*
* @authors nstavr04,mvasil17
* @bug Only runs on windows. Working for an update to work on Linux as well.
*/

#include "bmp.h"
#include "bmplib.h"

int main(int argc, char *argv[]) {

    BITMAPFILEHEADER b1;

    BITMAPINFOHEADER b2;

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

    unsigned char *bitmapData;

    BITMAPINFOHEADER secretInfoHeader;

    BITMAPFILEHEADER secretFileHeader;

    int systemKey;
    systemKey = 100;

    //Used in encodeImage
    unsigned char *secretImage;

    //Used for when an operation is completed
    int flag = 0;

    if (argc < 3) {
        printf("Wrong input");
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
            char* newFile = (char *)malloc(strlen(argv[3]) + 5);
            strcpy(newFile,"new-");
            strcat(newFile, argv[3]);

            FILE *fp = fopen(newFile, "wb");

            pixels = getEachPixel(bitmapData, &bitmapInfoHeader);

            imagePixels = getEachPixel(secretImage,&secretInfoHeader);

            encodeStegano(imagePixels,pixels, &bitmapFileHeader, &bitmapInfoHeader, fp,argv[2]);

        free(pixels);
        free(imagePixels);
        free(newFile);
        free(secretImage);

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
        char* newFile = (char *)malloc(strlen(argv[3]) + 5);
        strcpy(newFile,"new-");
        strcat(newFile, argv[3]);

        FILE *fp = fopen(newFile, "wb");

        pixels = getEachPixel(bitmapData, &bitmapInfoHeader);

        decodeStegano(pixels, &bitmapFileHeader, &bitmapInfoHeader, fp,argv[2]);

        free(pixels);
        free(newFile);

        fclose(fp);

    } else if (strcmp(argv[1], "-encodeText") == 0) {   // Operation 5

        //The file to save the Image to new-
        //5 Bytes because we need the \0 too
        char* newFileName = (char *)malloc(strlen(argv[2]) + 5);
        strcpy(newFileName,"new-");
        strcat(newFileName, argv[2]);

        // Open the new file (create it)
        FILE *newFile = NULL;
        newFile = fopen(newFileName, "wb");
        if (newFile == NULL) {
            printf("unable to open");
            exit(-1);
        }

        // Open the file that contains the text that needs to be encrypted
        FILE *fileText = NULL;
        fileText = fopen(argv[3], "r");
        if (fileText == NULL) {
            printf("unable to open");
            exit(-1);
        }

        char *encodedText;  //text that needs to be encoded

        bitmapData = LoadBitmapFile(argv[2], &bitmapFileHeader, &bitmapInfoHeader);

        fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, newFile);    // Write BITMAPFILEHEADER to the new file
        fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, newFile);    // Write BITMAPINFOHEADER to the new file

        encodedText = inputString(fileText, 10, 1);  // Read the text from file

        printf("strlen: %d", strlen(encodedText));

        stegaEncryptEncodeText(encodedText, bitmapData, systemKey, &bitmapInfoHeader,newFile);
        free(newFileName);
        free(encodedText);
    fclose(fileText);
    fclose(newFile);

    } else if (strcmp(argv[1], "-decodeText") == 0) {   //Operation 6

        //Open the new file (create it)
        if (argc != 5){
            printf("You need to enter 5 arguments for that operation.\n e.g. $./bmpSteganography –decodeText encryptedImage.bmp msgLength output.txt");
        }

        int textSizeInBytes = atoi(argv[3]);

        FILE *outputFile = NULL;
        outputFile = fopen(argv[4], "w");
        if (outputFile == NULL) {
            printf("unable to open");
            exit(-1);
        }

        bitmapData = LoadBitmapFile(argv[2], &bitmapFileHeader, &bitmapInfoHeader);

        stegaEncryptDecodeText(bitmapData, &bitmapInfoHeader, systemKey, textSizeInBytes, outputFile);

    } else if (strcmp(argv[1], "-stringToImage") == 0) {    //Operation 7
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

    } else if (strcmp(argv[1], "-imageToString") == 0) { //Operation 8

        //Save the data of the image in bitmapData
        bitmapData = LoadBitmapFile(argv[2], &bitmapFileHeader, &bitmapInfoHeader);

        ImageToString(bitmapData,&bitmapFileHeader,&bitmapInfoHeader);

    } else if(strcmp(argv[1], "-negativeFilter") == 0){ //Operation 9

        PIXEL *pixels;
        int counter = 2;  // program argument 1 Is the operations. (-negativeFilter)
        while (counter < argc) {

            bitmapData = LoadBitmapFile(argv[counter], &bitmapFileHeader, &bitmapInfoHeader);

            FILE *fp = fopen(argv[counter], "wb");

            pixels = getEachPixel(bitmapData, &bitmapInfoHeader);

            makePictureNegative(pixels, &bitmapFileHeader, &bitmapInfoHeader, fp);

            counter++;

            fclose(fp);
        }
        free(pixels);

    }
    else{
        printf("Wrong -option input");
        flag = 1;
        exit(-1);
    }

    if(!flag)
        printf("Operation Successful");

    free(bitmapData);

    return 0;

}