#include "UUIDGen.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
UUIDGen::UUIDGen(const string& filePath) : filePath(filePath) {}

// Destructor
UUIDGen::~UUIDGen() {}
//Generate UUID
string UUIDGen::generate() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint32_t> dis(0, 0xFFFFFFFF);

    stringstream ss;
    ss << hex << setfill('0');
    ss << setw(8) << dis(gen) << '-';
    ss << setw(4) << (dis(gen) & 0xFFFF) << '-';
    ss << setw(4) << ((dis(gen) & 0x0FFF) | 0x4000) << '-'; // Version 4
    ss << setw(4) << ((dis(gen) & 0x3FFF) | 0x8000) << '-'; // Variant 1
    ss << setw(12) << dis(gen) << dis(gen);

    return ss.str();
}
//Read File
string UUIDGen::readFile(){
    ifstream xml_in(filePath);

    if(!xml_in.is_open()){
        cerr << "Failed to open the xml file:" << filePath << endl;
        return "";
    }
    string content((istreambuf_iterator<char>(xml_in)), istreambuf_iterator<char>());
    xml_in.close();
    return content;
}
//Replace the Placeholder
string UUIDGen::replacePlaceholder(const string& content, const string& placeholder) {
    string updatedContent = content;
    size_t uuid_pos = updatedContent.find(placeholder);
    if (uuid_pos != string::npos) {
        string newUUID = "uuid:" + generate();
        updatedContent.replace(uuid_pos, placeholder.length(), newUUID);
        cout << "Generated UUID: " << newUUID << "\n";
    } else {
        cerr << "Placeholder UUID not found in the content.\n";
    }
    return updatedContent;
}
// Write the updated content back to the XML file
bool UUIDGen::writeFile(const string& content) {
    ofstream xml_out(filePath);
    if (!xml_out.is_open()) {
        cerr << "Failed to write to the XML file: " << filePath << "\n";
        return false;
    }
    xml_out << content;
    xml_out.close();
    return true;
}