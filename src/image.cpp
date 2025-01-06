#include "image.hpp"

#include <cmath>
#include <fstream>
#include <stdexcept>
#include <stdio.h>

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName)
{
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    FILE* imageFile = fopen(imageFileName, "wb");

    unsigned char* fileHeader = createBitmapFileHeader(height, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    unsigned char* infoHeader = createBitmapInfoHeader(height, width);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

    int i;
    for (i = 0; i < height; i++) {
        fwrite(image + (i*widthInBytes), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char* createBitmapFileHeader (int height, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader (int height, int width)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

    return infoHeader;
}

size_t getFileSize(const std::string & fileName)
{
  std::streampos begin, end;
  std::ifstream file (fileName, std::ios::binary);
  if (!file.is_open() || !file.good())
  {
    throw std::logic_error("Error: can't open file!");
  }
  begin = file.tellg();
  file.seekg (0, std::ios::end);
  end = file.tellg();
  file.close();
  return (end - begin);
}

size_t getRGBImageSize(const std::string & fileName)
{
  std::streampos begin, end;
  std::ifstream file (fileName, std::ios::binary);
  if (!file.is_open() || !file.good())
  {
    throw std::logic_error("Error: can't open file!");
  }
  begin = file.tellg();
  file.seekg (0, std::ios::end);
  end = file.tellg();
  file.close();
  size_t fileSize = std::sqrt((end - begin - 1) / 3);
  return (fileSize + 1);
}

void convertator::convertToRGB(const std::string & fileName)
{
  size_t size = getRGBImageSize(fileName);
  std::ifstream file (fileName);
  if (!file.is_open() || !file.good())
  {
    throw std::logic_error("Error: can't open file!");
  }

  int height = size, width = size;
  unsigned char image[height][width][BYTES_PER_PIXEL];
  char* imageFileName = (char*) "bitmapImage.bmp";
  for (size_t i = 0; i < size; ++i)
  {
    for (size_t j = 0; j < size; ++j)
    {
      for (size_t q = 0; q < 3; ++q)
      {
        file >> image[i][j][q];
      }
      if (file.eof())
      {
        j = size;
        i = size;
      }
    }
  }
  generateBitmapImage((unsigned char*) image, height, width, imageFileName);
  printf("Image generated!!");
  file.close();
}

void convertator::convertToBW(const std::string & fileName)
{
  size_t fileSize = getFileSize(fileName);
  std::ifstream file(fileName, std::ios::binary);
  if (!file.is_open() || !file.good())
  {
    throw std::logic_error("Error: can't open file!");
  }

  // Вычисляем размеры изображения, делая его максимально квадратным
  size_t size = std::ceil(std::sqrt(fileSize));
  int height = size, width = size;
  
  unsigned char image[height][width][BYTES_PER_PIXEL];
  char* imageFileName = (char*) "bitmapImageBW.bmp";
  
  // Читаем файл побайтово
  char byte;
  for (size_t i = 0; i < height && !file.eof(); ++i)
  {
    for (size_t j = 0; j < width && !file.eof(); ++j)
    {
      file.get(byte);
      // Используем значение байта как яркость пикселя
      unsigned char pixelValue = static_cast<unsigned char>(byte);
      
      // Устанавливаем одинаковое значение для всех цветовых каналов
      image[i][j][0] = pixelValue; // Blue
      image[i][j][1] = pixelValue; // Green
      image[i][j][2] = pixelValue; // Red
    }
  }

  // Заполняем оставшееся пространство черным цветом, если файл закончился
  for (size_t i = 0; i < height; ++i)
  {
    for (size_t j = 0; j < width; ++j)
    {
      if (i * width + j >= fileSize)
      {
        image[i][j][0] = 0;
        image[i][j][1] = 0;
        image[i][j][2] = 0;
      }
    }
  }

  generateBitmapImage((unsigned char*) image, height, width, imageFileName);
  printf("Black and white image generated!!");
  file.close();
}
