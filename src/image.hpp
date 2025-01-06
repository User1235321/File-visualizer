#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>

void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader (int height, int stride);
unsigned char* createBitmapInfoHeader (int height, int width);
namespace convertator
{
   void convertToRGB(const std::string & fileName);
   void convertToBW(const std::string & fileName);
}

#endif
