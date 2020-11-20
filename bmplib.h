//
// Created by 35799 on 19/11/2020.
//

#ifndef HW4_BMPLIB_H
#define HW4_BMPLIB_H

void imageInfo(BITMAPFILEHEADER bitmapFileHeader, BITMAPINFOHEADER bitmapInfoHeader);

void makePictureGrayScaled(PIXEL *pixels, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader, FILE *fp);

#endif //HW4_BMPLIB_H
