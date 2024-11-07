#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>

class filemanager : public QObject {
  Q_OBJECT

public:
  explicit filemanager(QObject *parent = nullptr);
  bool organizeFile(const QString &filePath, const QString &artist, const QString &album);

private:
  QString getTargetDirectory(const QString &artist, const QString &album);
};

#endif // FILEMANAGER_H