//
// Created by Matthew Winer on 11/7/24.
//

#include "filemanager.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
filemanager::filemanager(QObject *parent) : QObject(parent) {}
bool filemanager::organizeFile(const QString &filePath, const QString &artist, const QString &album) {
  QString targetDir = getTargetDirectory(artist, album);
  QDir dir;
  if (!dir.exists(targetDir)) {
    if (!dir.mkpath(targetDir)) return false;
  }
  QString fileName = QFileInfo(filePath).fileName();
  return QFile::copy(filePath, targetDir + "/" + fileName);
}

QString filemanager::getTargetDirectory(const QString &artist, const QString &album) {
   return QDir::currentPath() + "/music/" + artist + "/" + album;
 }