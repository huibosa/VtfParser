#include "vtf-parser.h"

void VtfParser::processColumns() {
  th.deleteQuotes(columns);
  th.deleteSpaces(columns);
  th.tabToComma(columns);
}

void VtfParser::processValues() {
  for (auto &val : values) {
    th.deleteSpaces(val);
    th.tabToComma(val);
  }
}

void VtfParser::parseFile(const std::string &filename) {
  std::fstream input(filename);
  std::size_t lineNo = 1;

  values.reserve(3000);
  for (std::string temp; std::getline(input, temp); ++lineNo) {
    if ((lineNo < 8) || (lineNo > 8 && lineNo < 12)) {
      continue;
    } else if (lineNo == 8) {
      columns = temp;
    } else {
      values.push_back(temp);
    }
  }
}

void VtfParser::writeOutput(const std::string &outFile) {
  std::ofstream output(outFile);

  output << columns << std::endl;
  for (const auto &val : values) {
    output << val << std::endl;
  }
  std::cout << "Generating -> " << outFile << std::endl;
}

void VtfParser::vtfToCsv(const std::string &inFile) {
  parseFile(inFile);
  processColumns();
  processValues();

  auto outFile = th.formatFileNmae(inFile);
  writeOutput(outFile);
}

void VtfParser::TextHelper::deleteQuotes(std::string &str) {
  std::string::size_type pos;
  while ((pos = str.find('\"')) != std::string::npos) {
    str.erase(pos, 1);
  }
}

void VtfParser::TextHelper::deleteSpaces(std::string &str) {
  std::string::size_type pos;
  while ((pos = str.find(' ')) != std::string::npos) {
    str.erase(pos, 1);
  }
}

void VtfParser::TextHelper::tabToComma(std::string &str) {
  std::string::size_type pos;
  while ((pos = str.find('\t')) != std::string::npos) {
    str.replace(pos, 1, ",");
    ++pos;
  }

  std::string::size_type temp;
  if ((temp = str.rfind(',')) == str.size() - 2) {
    str.erase(temp, 1);
  }
}

std::string VtfParser::TextHelper::formatFileNmae(const std::string &src) {
  auto ret = src;
  changeSuffix(ret, ".csv");
  sensorFormat(ret);

  return ret;
}

void VtfParser::TextHelper::changeSuffix(std::string &src,
                                         const std::string &suffix) {
  auto pos = src.rfind('.');
  src.erase(pos, src.size() - pos);
  src += suffix;
}

// remove "1_" or "1" in filename
void VtfParser::TextHelper::sensorFormat(std::string &str) {
  std::string pattern1("sensors1_"); // billet_sensors11.vtf
  std::string pattern2("sensors1");  // billet_sensors1_1.vtf
  std::string::size_type pos;

  if ((pos = str.find(pattern1)) != std::string::npos) {
    str.erase(pos + 7, 2); // "sensor".lengh() - 1 == 7
  } else if ((pos = str.find(pattern2)) != std::string::npos) {
    str.erase(pos + 7, 1);
  }
};
