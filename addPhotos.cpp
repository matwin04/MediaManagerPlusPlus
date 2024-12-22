//
// Created by mwiner on 12/22/24.
//

#include "addPhotos.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDir>
#include <QDate>
#include <QDebug>
#include <QImageReader>
#include <exiv2/exiv2.hpp>
#include <iostream>
addPhotos::addPhotos(const QString &photosFolder, QWidget *parent)
    : QDialog(parent),photosFolder(photosFolder) {
    setWindowTitle("Add Photos To DB");
    //Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *instructions = new QLabel("Select photos to add to the database");
    QPushButton *selectButton = new QPushButton("Select Photos");
    QPushButton *processButton = new QPushButton("Process Photos");

    layout->addWidget(instructions);
    layout->addWidget(selectButton);
    layout->addWidget(processButton);

    connect(selectButton,&QPushButton::clicked,this,&addPhotos::onSelectPhotos);
    connect(processButton,&QPushButton::clicked,this,&addPhotos::onProcessPhotos);
}
addPhotos::~addPhotos() {}
void addPhotos::onSelectPhotos() {
    selectedFiles = QFileDialog::getOpenFileNames(
            this,
            "Select Photos",
            QDir::homePath(),
            "Images (*.jpg *.jpeg *.png *.tiff)"
    );
    if (selectedFiles.isEmpty()){
        QMessageBox::warning(this,"No Files Selected","no files selected");
    } else {
        QMessageBox::information(this,"Files Selected","Files Selected");
    }
}
void addPhotos::onProcessPhotos() {
    if (selectedFiles.isEmpty()){
        QMessageBox::warning(this, "No Files", "Please select photos before processing.");
        return;
    }
    for (const QString &filePath : selectedFiles) {
        extractSortPhoto(filePath);
    }
    QMessageBox::information(this,"Processing Complete","complete");
    accept();
}
void addPhotos::extractSortPhoto(const QString &filePath) {
    QString cameraModel = QString::fromStdString(getMetadata(filePath,"Exif.Image.Model"));
    QString dateString = QString::fromStdString(getMetadata(filePath,"Exif.Photo.DateTimeOriginal"));

    if (cameraModel.isEmpty()||dateString.isEmpty()){
        std::cerr << "Skipping file\n";
        return;
    }

    QDate date = QDate::fromString(dateString,"yyyy:MM:dd HH:mm:ss");
    if (!date.isValid()){
        std::cerr << "" << std::endl;
        return;
    }
    QString targetFolder = QString("%1/%2/%3")
            .arg(photosFolder)
            .arg(cameraModel)
            .arg(date.toString("yyyy-MM-dd"));
    QDir dir;
    if (!dir.mkpath(targetFolder)){
        std::cerr << "Error Failed to create folder \n";
        return;
    }
    QFile::copy(filePath,targetFolder+"/"+ QFileInfo(filePath).fileName());

}
std::string addPhotos::getMetadata(const QString &filePath, const std::string &tagName) {
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filePath.toStdString());

    image->readMetadata();
    Exiv2::ExifData &exifData = image->exifData();
    auto tag = exifData.findKey(Exiv2::ExifKey(tagName));
    if (tag!=exifData.end()){
        return tag->toString();
    } else {
        return "";
    }
}

