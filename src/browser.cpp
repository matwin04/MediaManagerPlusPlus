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
    dbHandler = new databasehandler(this);
    fileManager = new filemanager(this);
    connect(ui->addFileButton, &QPushButton::clicked, this, &browser::on_addFileButton_clicked);
}

browser::~browser() {
    delete ui;
    delete dbHandler;
    delete fileManager;
}

void browser::on_addFileButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select Music File", "", "Music Files (*.mp3 *.flac *.wav)");
    if (filePath.isEmpty()) return;

    QString trackName = QFileInfo(filePath).baseName();
    QString artist = "Unknown";
    QString album = "Unknown";

    if (fileManager->organizeFile(filePath, artist, album)) {
        if (dbHandler->addAudioToDatabase(filePath, artist, album, trackName)) {
            QMessageBox::information(this, "Success", "Audio file added successfully!");
        } else {
            QMessageBox::critical(this, "Database Error", "Failed to add audio file to the database.");
        }
    } else {
        QMessageBox::critical(this, "File Error", "Failed to organize the audio file.");
    }
}
