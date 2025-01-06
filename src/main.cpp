#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "image.hpp"

int main()
{
  std::cout << "This is programm, which convert your file to bmp image. At the moment there are next types of convert: rgb, bw. To use it, write \"rgb\" or \"bw\" after name of file\n";

  std::map < std::string, std::function < void(const std::string &) > > convertors;
  convertors["rgb"] = convertator::convertToRGB;

  std::string fileName = "1";
  std::cout << "Please, write file name:\n";
  std::getline(std::cin, fileName);

  while (fileName.find("exit") == std::string::npos)
  {
    std::string format;
    std::cout << "Please, write convertion format:\n";
    std::getline(std::cin, format);

    try
    {
      convertors.at(format)(fileName);
      std::cout << "Image creating succesfully end\n";
    }
    catch (const std::out_of_range & e)
    {
      std::cerr << "Error: unknown command!\n";
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << '\n';
    }

    std::cout << "Write \"exit\" to end programm, or new file name\n";
    std::getline(std::cin, fileName);
  }
  return 0;
}
