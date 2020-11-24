/**
 * @file bmp.h
 * @brief The class that has all the necessary functions to handle a .bmp file (read)
 *
 * @authors nstavr04, mvasil17
 * @bug No known bugs.
 *
 */

#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Bitmap file header
 */
typedef struct tagBITMAPFILEHEADER {    /*  14 bytes  */
    char           bfType1;      /* 1 byte  */  // specifies the file type
    char           bfType2;      /* 1 byte  */  // specifies the file type
    unsigned int   bfSize;       /* 4 bytes */  // specifies the size in bytes of the bitmap file
    unsigned short bfReserved1;  /* 2 bytes */  // reserved; must be 0
    unsigned short bfReserved2;  /* 2 bytes */  // reserved; must be 0
    unsigned long  bfOffBits;    /* 4 bytes */  // species the offset in bytes from the bitmapfileheader to the bitmap bits
}__attribute__((packed))BITMAPFILEHEADER;

/**
 * Bitmap info header
 */
typedef struct tagBITMAPINFOHEADER {    /*  40 bytes  */
    unsigned int   biSize;          /* 4 bytes */   // Specifies the size of the BITMAPINFOHEADER structure, in bytes.
    long           biWidth;         /* 4 bytes */   // Specifies the width of the image, in pixels.
    long           biHeight;        /* 4 bytes */   // Specifies the height of the image, in pixels.
    unsigned short biPlanes;        /* 2 bytes */   // Specifies the number of planes of the target device, usually set to zero.
    unsigned short biBitCount;      /* 2 bytes */   // Specifies the number of bits per pixel.
    unsigned int   biCompression;   /* 4 bytes */   // Specifies the type of compression, usually set to zero (no compression). Need to provide an error if image is compressed.
    unsigned int   biSizeImage;     /* 4 bytes */   // Specifies the size of the image data, in bytes. If there is no compression, it is valid to set this member to zero.
    long           biXPixPerMeter;  /* 4 bytes */   // Specifies the horizontal pixels per meter on the designated target device, usually set to zero.
    long           biYPixPerMeter;  /* 4 bytes */   // Specifies the vertical pixels per meter on the designated target device, usually set to zero.
    unsigned long  biClrUsed;       /* 4 bytes */   // Specifies the number of colors used in the bitmap, if set to zero the number of colors is calculated using the biBitCount member.
    unsigned long  biClrImportant;  /* 4 bytes */   // Specifies the number of color that are 'important' for the bitmap, if set to zero, all colors are important.
} __attribute__((packed))BITMAPINFOHEADER;

/**
 * Bitmap pixel. (isPadding byte is just to make sure that this is a pixel or a padding)
 */
typedef struct pixel{
    unsigned char    red;    /* 1 byte  */
    unsigned char   green;   /* 1 byte  */
    unsigned char    blue;   /* 1 byte  */
    unsigned char isPadding; /* 1 byte */
}PIXEL;

/** @brief This function reads and loads the bitmap file
 *
 * @param filename
 * @param bitmapFileHeader
 * @param bitmapInfoHeader
 * @return
 */
unsigned char *LoadBitmapFile(char *filename, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader);

/** @brief This function prints all the header values of the image
 *
 * @param bitmapFileHeader
 * @param bitmapInfoHeader
 */
void imageInfo(BITMAPFILEHEADER bitmapFileHeader, BITMAPINFOHEADER bitmapInfoHeader);


/** @brief This method splits each pixel from bimapData
 *
 *
 * @param bitmapData
 * @param bitmapInfoHeader
 * @return
 */
PIXEL *getEachPixel(unsigned char *bitmapData, BITMAPINFOHEADER *bitmapInfoHeader);

#endif