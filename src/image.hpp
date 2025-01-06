#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>

void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName);//dell
unsigned char* createBitmapFileHeader (int height, int stride);//dell
unsigned char* createBitmapInfoHeader (int height, int width);//dell
namespace convertator
{
   void convertToRGB(const std::string & fileName);
}

#endif
