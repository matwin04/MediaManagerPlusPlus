//
// Created by Matthew Winer on 10/24/24.
//

#ifndef AUDIODATA_H
#define AUDIODATA_H
#include <string>
using namespace std;


class audioData {
public:
    //constructor
    audioData(const std::string &filePath);
    ~audioData();
    void loadMetadata();
    void playAudio();
    string getTitle() const;
    string getArtist() const;
    string getAlbum() const;
    int getYear() const;
private:
    string filePath;
    string title;
    string artist;
    string album;
    int year;
};
#endif //AUDIODATA_H
