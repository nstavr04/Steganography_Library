//
// Created by 35799 on 19/11/2020.
//

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

//    srand(systemkey);

    int *permutation = malloc(sizeof(int) * N);
    if (!permutation){
        printf("Not enough memory space to allocate");
        exit(-1);
    }

    for (int k = 0; k < N; k++) {
//        int i = rand() % N;
//        int j = rand() & N;
        *(permutation + k) = k;

    }

    return permutation;

}

int getBit(char *m, int n) {
    if (n <= 8 * strlen(m))
        return ((*(m + n / 8) >> (7 - (n % 8))) & 1);
    else
        return 0;
}

//encription of message
void stega_encrypt(char *textToBeEncoded, unsigned char *bitmapData, BITMAPINFOHEADER *bitmapInfoHeader, FILE *newFile) {

    char *Un = malloc((strlen(textToBeEncoded)+1) * sizeof(char) * 8);
    int n = 0;

    while (*(textToBeEncoded+n/8) != '\0') {        // Im pretty sure that I need '\0' too. So for 8 times

        if (getBit(textToBeEncoded, n) == 1) {
            Un[n] = '1';
        } else {   //getBit == 0
            Un[n] = '0';
        }

        n++;
    }
    //add manually the '\0' chaacter (10 at decimal)
    Un[n++]='0';
    Un[n++]='0';
    Un[n++]='0';
    Un[n++]='0';
    Un[n++]='1';
    Un[n++]='0';
    Un[n++]='1';
    Un[n]='0';


    int *fn;

    fn = createPermutationFunction((strlen(textToBeEncoded)+1)*8, 100);    // system-key-integer


    srand(100);

    for (int k = 0; k < (strlen(textToBeEncoded)+1)*8; k++) {
        int i = rand() % strlen(textToBeEncoded);
        int j = rand() % strlen(textToBeEncoded);

        int temp;

        temp = *(fn + i);
        *(fn + i) = *(fn + j);
        *(fn + j) = temp;

    }

    // isagogi minimatos stin ikonoa

    for (int i = 0; i < (strlen(textToBeEncoded) + 1) * 8; i++) {
        int b = getBit(textToBeEncoded, i);     // ipologise b = getbit(m,i)
        int o = *(fn + i);                      // ipologise 0 = permuation[i]
        unsigned char temp;
//        This can be done in 1 line, but complicated
//        temp = *(bitmapdata + (o/8));
//        temp = (temp ^ 1);
//        *(bitmapdata + (o/8))=temp;

        // diagrafi bit mikroterou varous tou o-ostou byte
        // tou pinaka ton pixel kai
        // antikatastasi tou me tin timi b

        if (b == 0) {
            *(bitmapData + (o / 8)) = (*(bitmapData + (o / 8)) & 0xFE);
        } else if (b == 1) {
            *(bitmapData + (o / 8)) = (*(bitmapData + (o / 8)) | b);
        }else{
            printf("In encodeText -> stega_encrypt, b should be 0 or 1 and its value is: %d\n", b);
        }

        //*(bitmapData + (o / 8)) = (*(bitmapData + (o / 8)) ^ b);


    }

    fwrite(bitmapData, bitmapInfoHeader->biSizeImage, 1, newFile);


}