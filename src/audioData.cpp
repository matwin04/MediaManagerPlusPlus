//
// Created by Matthew Winer on 10/24/24.
//
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <iostream>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "audioData.h"

using namespace std;
using namespace TagLib;
//constructor
audioData::audioData(const std::string &filePath) : year(0) {
    // Pass the filePath argument when calling loadMetadata
    loadMetadata();
}
//Destructor
audioData::~audioData() {
}
void audioData::loadMetadata() {
    std::cout << "Attempting to load metadata from: " << filePath << std::endl;  // Debug print
    TagLib::FileRef file(filePath.c_str());
    if (!file.isNull() && file.tag()) {
        TagLib::Tag *tag = file.tag();
        // Extract metadata
        title = tag->title().toCString(true);
        artist = tag->artist().toCString(true);
        album = tag->album().toCString(true);
        year = tag->year();
    } else {
        std::cerr << "Error reading metadata from file: " << filePath << std::endl;
        title = "Unknown Title";
        artist = "Unknown Artist";
        album = "Unknown Album";
        year = 0;
    }
}
// Play the audio file
void audioData::playAudio() {
    // Assuming you're using Qt's QMediaPlayer and QAudioOutput to handle audio playback
    QMediaPlayer* mediaPlayer = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl::fromLocalFile(QString::fromStdString(filePath)));
    audioOutput->setVolume(0.5);  // Adjust the volume
    mediaPlayer->play();
}

string audioData::getTitle() const {
    return title;
}
string audioData::getArtist() const {
    return artist;
}
string audioData::getAlbum() const {
    return album;
}
int audioData::getYear() const {
    return year;
}
