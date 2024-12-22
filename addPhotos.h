//
// Created by mwiner on 12/22/24.
//

#ifndef MEDIAMANAGER_ADDPHOTOS_H
#define MEDIAMANAGER_ADDPHOTOS_H
#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <iostream>
class addPhotos : public QDialog {
    Q_OBJECT
public:
    explicit addPhotos(const QString &photosFolder, QWidget *parent = nullptr);
    ~addPhotos();

private slots:
    void onSelectPhotos();
    void onProcessPhotos();
private:
    QString photosFolder;
    QStringList selectedFiles;
    void extractSortPhoto(const QString &filePath);
    std::string getMetadata(const QString &filePath, const std::string &tagName);
};


#endif //MEDIAMANAGER_ADDPHOTOS_H
