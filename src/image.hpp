#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <fstream>

namespace convertator
{
  void classicRGB(const std::ifstream & in);
  void bw(const std::ifstream & in);
}

#endif
