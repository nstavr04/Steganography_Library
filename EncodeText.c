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
    str = realloc(NULL, sizeof(char) * size);//size is start size
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

//    char *Un = malloc((strlen(textToBeEncoded)+1) * sizeof(char) * 8);
//    int n = 0;
//
//    while (*(textToBeEncoded+n/8) != '\0') {
//
//        if (getBit(textToBeEncoded, n) == 1) {
//            Un[n] = '1';
//        } else {   //getBit == 0
//            Un[n] = '0';
//        }
//        n++;
//    }
//    //add manually the '\0' character (10 at decimal)
//    Un[n++]='0';
//    Un[n++]='0';
//    Un[n++]='0';
//    Un[n++]='0';
//    Un[n++]='1';
//    Un[n++]='0';
//    Un[n++]='1';
//    Un[n]='0';


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