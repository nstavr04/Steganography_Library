
#include "bmp.h"

unsigned char *LoadBitmapFile(char *filename, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader) {
    FILE *filePtr; //our file pointer
    //BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data

    //open filename in read binary mode
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
        return NULL;

    //read the bitmap file header
    fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    //verify that this is a bmp file by check bitmap id
    if ((bitmapFileHeader->bfType1) != 0x42 || (bitmapFileHeader->bfType2) != 0x4D)     //0x42 = 'B' && 0x4D = 'M'
    {
        fclose(filePtr);
        return NULL;
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char *) malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage) {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    //read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader->biSizeImage, 1, filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL) {
        fclose(filePtr);
        return NULL;
    }

    //close file and return bitmap image data
    fclose(filePtr);
    return bitmapImage;
}


PIXEL *getEachPixel(unsigned char *bitmapData, BITMAPINFOHEADER *bitmapInfoHeader) {

    int numOfEachLinePadding;
    //check if there is padding
    bool padding = false;
    if ((bitmapInfoHeader->biWidth)*3%4 != 0){
        padding = true;
        numOfEachLinePadding = (bitmapInfoHeader->biWidth)*3%4;
    }

    printf("size of PIXEL: %llu\n", sizeof(PIXEL));
    PIXEL *pixels = malloc(sizeof(PIXEL) * ((bitmapInfoHeader->biSizeImage)/3));    //each pixel is 3 bytes
    if (!pixels){
        printf("Unable to allocate memory");
        exit(-1);
    }

    int linecounter = bitmapInfoHeader->biWidth + numOfEachLinePadding;

    for (int i = 0; i < ((bitmapInfoHeader->biSizeImage) / 3); i++) {    // for each pixel

        (pixels + i)->red = *(bitmapData);
        bitmapData++;
        (pixels + i)->green = *(bitmapData);
        bitmapData++;
        (pixels + i)->blue = *(bitmapData);
        bitmapData++;

        if (padding == true) {
            if (linecounter == 0)
                linecounter = bitmapInfoHeader->biWidth + numOfEachLinePadding;

            if (linecounter <= numOfEachLinePadding) {
                (pixels + i)->isPadding = '1';
            } else {
                (pixels + i)->isPadding = '0';
            }

            //Retracting 3 because we are dealing with pixels
            linecounter--;
        }

    }
    return pixels;
}

//Driver function
#ifdef bmpDEBUG
int main() {

    BITMAPFILEHEADER b1;

    BITMAPINFOHEADER b2;

    printf("%llu\n", sizeof(b1));

    printf("%llu\n\n", sizeof(b2));

    BITMAPINFOHEADER bitmapInfoHeader;

    BITMAPFILEHEADER bitmapFileHeader;

    unsigned char *bitmapData;
    bitmapData = LoadBitmapFile("image6.bmp", &bitmapFileHeader, &bitmapInfoHeader);

//#ifdef list
    imageInfo(bitmapFileHeader, bitmapInfoHeader);
//#endif

    FILE *filePtr;

    filePtr = fopen("newImage.bmp", "wb");

    if (filePtr == NULL) {
        printf("Can't write on file");
        return 0;
    }

    BITMAPFILEHEADER *ptr1 = &bitmapFileHeader;
    BITMAPINFOHEADER *ptr2 = &bitmapInfoHeader;

    fwrite(ptr1, sizeof(BITMAPFILEHEADER), 1, filePtr);
    fwrite(ptr2, sizeof(BITMAPINFOHEADER), 1, filePtr);
    fwrite(bitmapData, bitmapInfoHeader.biSizeImage, 1, filePtr);

    return 0;

}
#endif


