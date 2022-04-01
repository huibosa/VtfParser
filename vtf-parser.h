#pragma

#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

class VtfParser {
public:
  VtfParser() = default;

public:
  void vtfToCsv(const std::string& inFile);

private:
  void parseFile(const std::string& filename);
  void processValues();
  void processColumns();
  void changeSuffix(const std::string& src, const std::string& suffix);
  void writeOutput(const std::string& outFile);

private:
  class TextHelper {
  public:
    TextHelper() = default;

  public:
    void deleteQuotes(std::string& str);
    void deleteSpaces(std::string& str);
    void tabToComma(std::string& str);
    std::string formatFileNmae(const std::string& src);

  private:
    void changeSuffix(std::string& src, const std::string& suffix);
    void sensorFormat(std::string& str);
  };

private:
  std::vector<std::string> values;
  std::string columns;
  TextHelper th;
};
