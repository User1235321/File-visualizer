#include "image.hpp"

#include <cmath>
#include <fstream>
#include <stdexcept>
#include <iostream>//dell

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
  std::cout << '\n' << ((end - begin - 1) / 3) << '\n';
  size_t fileSize = std::sqrt((end - begin - 1) / 3);
  std::cout << '\n' << fileSize << '\n';
  return (fileSize + 1);
}
void convertator::convertToRGB(const std::string & fileName)
{
  size_t size = getFileSize(fileName);
  std::ifstream file (fileName);
  if (!file.is_open() || !file.good())
  {
    throw std::logic_error("Error: can't open file!");
  }

  std::string imageName = fileName;
  imageName += ".bmp";
  std::ofstream image(fileName);
  image << "BM" << (54 + 3 * size * size)

  for (size_t i = 0; i < size; ++i)
  {
    for (size_t j = 0; j < size; ++j)
    {
      for (size_t q = 0; q < 3; ++i)
      {
        unsigned char c;
        file >> c;
        image << ' ' << c;
      }
      image << " 0";
      if (file.eof())
      {
        j = size;
        i = size;
      }
    }
  }
  image.close();
  file.close();
};
void convertator::convertToBW(const std::string & fileName)
{
  size_t size = getFileSize(fileName);
};
