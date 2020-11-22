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

int *createPermutationFunction(int N, unsigned int systemkey){

}

int getBit(char *m, int n) {
    if (n <= 8 * strlen(m))
        return ((*(m + n / 8) >> (7 - (n % 8))) & 1);
    else
        return 0;
}

//encription of message
void stega_encrypt(char *textToBeEncoded)
{
    char *Un = malloc(strlen(textToBeEncoded) * sizeof(char) * 8);
    int n = 0;

    while(*textToBeEncoded != '\0'){
        for (int i=0; i< 7; i++){

            int bit = getBit(textToBeEncoded, n);

            n++;
        }
    }


}