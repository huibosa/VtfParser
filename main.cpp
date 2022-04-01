#include "vtf-parser.h"
#include <cstdio>
#include <filesystem>
#include <iostream>

int main(int argc, char** argv) {
  if (argc == 1) {
    std::string inFile;
    while (std::cin >> inFile) {
      VtfParser parser;

      if (inFile.find(".vtf") != std::string::npos) {
        parser.vtfToCsv(inFile);
      }
    }
  } else if (argc == 2) {
    VtfParser parser;
    parser.vtfToCsv(argv[1]);
  }
}
