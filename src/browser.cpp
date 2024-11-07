//
// Created by Matthew Winer on 11/7/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_browser.h" resolved

#include "browser.h"
#include "databasehandler.h"
#include "filemanager.h"
#include "ui_browser.h"

#include <QFileDialog>
#include <QMessageBox>

browser::browser(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::browser) {
    ui->setupUi(this);
    dbHandler = new DatabaseHandler(this);
    fileManager = new FileManager(this);
    connect(ui->addFileButton, &QPushButton::clicked,this.&browser::on_addFileButton_clicked();
}

browser::~browser() {
    delete ui;
    delete dbHandler;
    delete fileManager;
}
void browser::on_addFileButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,"Select Audio File","","Music Files(*.mp3 *.flac *wav");
    if (fileName.isEmpty()) {
        return;
    }
    QString tile = fileName.trimmed();
    QString artist = "UNKNOWN";
    QString album = "UNKNOWN";
    QString genre = "UNKNOWN";
    if (fileManager->organizeFile(filePath, artist, album)) {
        if (dbHandler->addFileToDatabase(filePath, artist, album)) {
            QMessageBox::information(this, "Success", "File added successfully!");
        } else {
            QMessageBox::critical(this, "Database Error", "Failed to add file to the database.");
        }
    } else {
        QMessageBox::critical(this, "File Error", "Failed to organize the file.");
    }
}
