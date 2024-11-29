#ifndef UUIDGEN_H
#define UUIDGEN_H

#include <string>

using namespace std;

class UUIDGen {
public:
    // Constructor and Destructor
    UUIDGen(const string& filePath);
    ~UUIDGen();

    // Member Functions
    string generate();
    string readFile();
    string replacePlaceholder(const string& content, const string& placeholder);
    bool writeFile(const string& content);

private:
    string filePath;  // Path to the XML file
};

#endif // UUIDGEN_H