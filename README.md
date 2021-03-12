/**

@mainpage EPL232 HW4

@author nstavr04 mvasil17


This program implements different 24 bit .bmp image manipulations accordingly to the correct option used.
All of the classes are combined into a bmp library and executed with bmpSteganorgaphy file. The options are as follows:

./bmpSteganography -list image1.bmp [image2.bmp image3.bmp ...]

./bmpSteganography -grayscale image1.bmp [image2.bmp image3.bmp ...]

./bmpSteganography -encodeStegano nbBits coverImage.bmp secretImage.bmp

./bmpSteganography -decodeStegano nbBits encryptedImage.bmp

./bmpSteganography -encodeText coverImage.bmp inputText.txt

./bmpSteganography -decodeText encryptedImage.bmp msgLength output.txt

./bmpSteganography -stringToImage sampleImage.bmp inputText.txt

./bmpSteganography -imageToString encryptedTextImage.bmp

./bmpSteganography -negativeFilter image1.bmp [image2.bmp image3.bmp ...]
