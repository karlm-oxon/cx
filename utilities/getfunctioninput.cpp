#include "getfunctioninput.h"

  std::string cx::utilities:: getfunctioninput () {
            std::string fname;
            std::cout << "Enter function: ";
            std::getline(std::cin, fname);
            return fname;

        };