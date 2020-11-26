/* EncodeText.c
* Copyright (C) 2020 nstavr04 mvasil17
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License.
*/

/**
* @file EncodeText.c
* @brief The class that hides a text file into an image.
*
* @author mvasil17
* @bug No known bugs.
*/


#include "bmp.h"
#include "bmplib.h"


char *inputString(FILE *fp, size_t size, int flag) {       //size_t = size of 'object' in bytes
    // flag: if true the function ignores the '\n'
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = malloc(sizeof(char) * size);//size is start size
    if (!str)
        return str;
    if (flag == 0) {
        while (EOF != (ch = fgetc(fp)) && ch != '\n') {
            str[len++] = ch;
            if (len == size) {
                str = realloc(str, sizeof(char) * (size += 16));
                if (!str)
                    return str;
            }
        }
    } else {
        while (EOF != (ch = fgetc(fp))) {
//            if (ch != '\n')         // This if ignores the new line characters
            str[len++] = ch;
            if (len == size) {
                str = realloc(str, sizeof(char) * (size += 16));
                if (!str)
                    return str;
            }
        }
    }
    str[len++] = '\0';

    return realloc(str, sizeof(char) * len);
}

int *createPermutationFunction(int N, unsigned int systemkey) {

    srand(systemkey);

    int *permutation = (int *)malloc(sizeof(int) * N);

    if (!permutation){
        printf("Not enough memory space to allocate");
        exit(-1);
    }

    for (int k = 0; k < N; k++) {
        *(permutation + k) = k;
    }

    for (int k = 0; k < N; k++) {
        int i = rand() % N;
        int j = rand() % N;

        int temp;

        temp = *(permutation + i);
        *(permutation + i) = *(permutation + j);
        *(permutation + j) = temp;
    }

    return permutation;
}

int getBit(unsigned char *m,int n){
    if(n>=0 && n<=8*strlen(m)){
        int i = n/8;
        char ch = m[i];
        int bitStatus;
        bitStatus = (ch >> 7 - (n % 8)) & 1;
        return bitStatus;
    }
    return 0;
}

//encription of message
void stegaEncryptEncodeText(char *textToBeEncoded, unsigned char *bitmapData, int systemKey, BITMAPINFOHEADER *bitmapInfoHeader, FILE *newFile) {

    int *fn;

    fn = createPermutationFunction(bitmapInfoHeader->biSizeImage, systemKey);    // system-key-integer

    // isagogi minimatos stin ikonoa

    for (int i = 0; i < (strlen(textToBeEncoded) + 1) * 8; i++) {
        int b = getBit(textToBeEncoded, i);     // ipologise b = getbit(m,i)
        int o = *(fn + i);                      // ipologise 0 = permuation[i]

        // diagrafi bit mikroterou varous tou o-ostou byte
        // tou pinaka ton pixel kai
        // antikatastasi tou me tin timi b

        if (b == 0) {
            *(bitmapData + o) = (*(bitmapData + o) & 0xFE);
        }else if (b == 1) {
            *(bitmapData + o) = (*(bitmapData + o) | b);
        }else{
            printf("In encodeText -> stega_encrypt, b should be 0 or 1 and its value is: %d\n", b);
        }


    }

    fwrite(bitmapData, bitmapInfoHeader->biSizeImage, 1, newFile);

    free(fn);

}

//Driver function
#ifdef EncodeTextDEBUG
int main(int argc, char *argv[]){

    int systemKey = 100;

    unsigned char *bitmapData;

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

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

    fclose(fileText);
    fclose(newFile);
}
#endif