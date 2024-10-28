#include <QApplication>
#include <QMainWindow>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "ui_MainWindow.h"
using namespace std;
const QString INIT_SQL_PATH = QDir::currentPath() + "/init.sql";

void initDB() {
  QString mmppFolderPath = QDir::currentPath() + "/mmpp";
  // Create the /mmpp folder if it doesn't exist
  QDir dir;
  if (!dir.exists(mmppFolderPath)) {
    dir.mkdir(mmppFolderPath);
  }
  // Create media subfolders
  QStringList folderNames = {"music", "movies", "tv", "photos", "videos", "podcasts", "games"};
  for (const QString &folder : folderNames) {
    QString folderPath = mmppFolderPath + "/" + folder;
    dir.mkdir(folderPath);
  }
  QString dbPath = mmppFolderPath + "/mmpp.db";
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(dbPath);
  if (db.open()) {
    QFile initFile(INIT_SQL_PATH);
    if (initFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QTextStream in(&initFile);
      QString sqlCommand;
      QSqlQuery query;
      while (!in.atEnd()) {
        sqlCommand = in.readLine();
        if (!sqlCommand.trimmed().isEmpty()) {
          query.exec(sqlCommand);  // Execute each command
        }
      }
      initFile.close();
      QMessageBox::information(nullptr,"setup complete","Database and folders have been created successfully in /mmpp");
    } else {
      QMessageBox::critical(nullptr, "Error", "Failed to open init.sql file.");
    }
    db.close();
  } else {
    QMessageBox::critical(nullptr, "Error", "Failed to create the database.");
  }
}
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  initDB();
  QMainWindow mainWindow;
  Ui::MainWindow ui;
  ui.setupUi(&mainWindow);
  //Create table
  mainWindow.show();
  return app.exec();
}