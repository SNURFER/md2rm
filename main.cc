#include <vector>
#include <fstream>
#include <iostream>

#include <filesystem>

using namespace std;

class Converter{
  public:
  Converter() {}
  ~Converter() {}

  public:
   void convertString(string& srcPath, string& targetPath);

  private:
   string convertHeader(string& line);
   string convertBullet(string& line);
   string replaceString(string& mainStr, const string& findStr, const string& replaceStr);



};

string Converter::replaceString(string& mainStr, const string& findStr, const string& replaceStr) {
    size_t pos = 0;
    while ((pos = mainStr.find(findStr, pos)) != std::string::npos) {
         mainStr.replace(pos, findStr.length(), replaceStr);
         cout << "replace string : " << findStr <<  "->" << replaceStr << endl; 
         pos += replaceStr.length();
    }
    return mainStr;
}

string Converter::convertHeader(string& line) {

  replaceString(line, "###", "h3.");
  replaceString(line, "##", "h2.");
  replaceString(line, "#", "h1.");

  return line;
}

string Converter::convertBullet(string& line) {

  replaceString(line, "            *", "****");
  replaceString(line, "        *", "***");
  replaceString(line, "    *", "**");

  return line;
}

void Converter::convertString(string& srcPath, string& targetPath) {
  ifstream input(srcPath);
  ofstream output(targetPath);

  string tempStr;
  for (string line; getline(input, line); ) {
    tempStr = convertHeader(line);
    tempStr = convertBullet(tempStr);

    output << tempStr;
    output << "\n";
  }


  output.close();
}


int main(int argc, char *argv[]) {

  vector<string> inputVec;
  for (int i = 0; i < argc; ++i) {
    if (i == 0)
      continue;
    inputVec.push_back(argv[i]);
  }

  Converter converter;
  string targetPath;
  for (auto path : inputVec) {
    targetPath = path + "_rm";
    converter.convertString(path, targetPath);
    cout << "convert path " << targetPath << " ended" << endl;
  }

  cout << "==================================" << endl;
  cout << "==================================" << endl;
  cout << "===========convert ended==========" << endl;


  



  return 0;
}