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
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>

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

    qDebug() << "Retrived Raw Date: " << dateString;
    QDateTime dateTime;
    QStringList formats = {
            "yyyy:MM:dd HH:mm:ss",  // Standard EXIF format
            "yyyy-MM-ddTHH:mm:ss", // ISO-8601 format
            "yyyy-MM-dd HH:mm:ss"  // Alternate format
    };
    for (const QString &format : formats) {
        dateTime = QDateTime::fromString(dateString,format);
        if (dateTime.isValid()){
            break;
        }
    }
    if (!dateTime.isValid()){
        std::cerr << "DATE TIME NOT VALID OR IN FILE : " << filePath.toStdString() << std::endl;
        return;
    }

    QString targetFolder = QString("%1/%2/%3")
            .arg(photosFolder)
            .arg(cameraModel)
            .arg(dateTime.date().toString("yyyy-MM-dd"));
    QDir dir;
    if (!dir.mkpath(targetFolder)){
        std::cerr << "Error Failed to create folder \n";
        return;
    }
    QString newFilePath = targetFolder+"/"+ QFileInfo(filePath).fileName();
    if (!QFile::copy(filePath,newFilePath)){
        std::cerr << "Failed to copt to target folder\n";
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO photos (file_path, camera_model, date_taken) VALUES (:file_path, :camera_model, :date_taken)");
    query.bindValue(":file_path", newFilePath);
    query.bindValue(":camera_model", cameraModel);
    query.bindValue(":date_taken", dateTime.toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()) {
        std::cerr << "Database Insert Error: " << query.lastError().text().toStdString() << std::endl;
    } else {
        qDebug() << "Photo added to database successfully.";
    }

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

