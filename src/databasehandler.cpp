#include "databasehandler.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>

databasehandler::databasehandler(QObject *parent) : QObject(parent) {
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("MediaManager.db");
  if (!db.open() || !initializeDatabase()) {
    qDebug() << "Database initialization failed:" << db.lastError().text();
  }
}

bool databasehandler::initializeDatabase() {
  QFile initFile(":/init.sql");
  if (!initFile.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

  QSqlQuery query;
  foreach (const QString &statement, QString(initFile.readAll()).split(';')) {
    if (!statement.trimmed().isEmpty()) {
      if (!query.exec(statement)) return false;
    }
  }
  return true;
}

bool databasehandler::addAudioToDatabase(const QString &filePath, const QString &artist, const QString &album, const QString &trackName) {
  QSqlQuery query;
  query.prepare("INSERT INTO audio (file_path, artist, album, track_name) VALUES (?, ?, ?, ?)");
  query.addBindValue(filePath);
  query.addBindValue(artist);
  query.addBindValue(album);
  query.addBindValue(trackName);
  return query.exec();
}