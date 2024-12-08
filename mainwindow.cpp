#include "mainwindow.h"
#include <QFileDialog>
#include <QSqlQuery>
#include <QTreeView>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), fileWatcher(new QFileSystemWatcher(this)) {
    setupDatabase();
    fileWatcher->addPath("/database");
    connect(fileWatcher,&QFileSystemWatcher::directoryChanged,this, &MainWindow::onFolderChanged);

}

MainWindow::~MainWindow() {
    db.close();
}
void MainWindow::setupDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("media.db");
    if (!db.open()){
        std::cout << "Error\n";
        return;
    }
    //Create the main folder
    createMediaFolder();

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS media ("
               "id INTEGER PRIMARY KEY, "
               "artist TEXT, "
               "album TEXT, "
               "title TEXT, "
               "path TEXT)");
    std::cout << "DB CREATED\n";
}
void MainWindow::onFolderChanged(const QString &path) {
    scanAndOrganize();
}

void MainWindow::scanAndOrganize() {
    //
}
void MainWindow::connectToEmby() {
    //
}

void MainWindow::createMediaFolder() {

}
