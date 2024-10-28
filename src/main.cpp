#include <QApplication>
#include <QMainWindow>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include "ui_MainWindow.h"
using namespace std;
const QString INIT_SQL_PATH = QDir::currentPath() + "/init.sql";


void initDB() {
    QString mmppFolderPath = QDir::currentPath() + "/mmpp";
    QDir dir;
    if (!dir.exists(mmppFolderPath)) {
        dir.mkdir(mmppFolderPath);
    }

    QStringList folderNames = {"music", "movies", "tv", "photos", "videos", "podcasts", "games"};
    for (const QString &folder : folderNames) {
        QString folderPath = mmppFolderPath + "/" + folder;
        dir.mkdir(folderPath);
    }

    QString dbPath = mmppFolderPath + "/mmpp.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (db.open()) {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS music (id INTEGER PRIMARY KEY, title TEXT, artist TEXT, album TEXT, genre TEXT, release_year INTEGER, path TEXT, added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
        query.exec("CREATE TABLE IF NOT EXISTS movies (id INTEGER PRIMARY KEY, title TEXT, director TEXT, genre TEXT, release_year INTEGER, duration INTEGER, path TEXT, added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
        query.exec("CREATE TABLE IF NOT EXISTS tv (id INTEGER PRIMARY KEY, title TEXT, season INTEGER, episode INTEGER, genre TEXT, release_year INTEGER, path TEXT, added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
        query.exec("CREATE TABLE IF NOT EXISTS photos (id INTEGER PRIMARY KEY, title TEXT, resolution TEXT, format TEXT, date_taken TEXT, path TEXT, added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
        query.exec("CREATE TABLE IF NOT EXISTS videos (id INTEGER PRIMARY KEY, title TEXT, format TEXT, duration INTEGER, path TEXT, added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
        query.exec("CREATE TABLE IF NOT EXISTS podcasts (id INTEGER PRIMARY KEY, title TEXT, host TEXT, episode_number INTEGER, duration INTEGER, path TEXT, added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
        query.exec("CREATE TABLE IF NOT EXISTS games (id INTEGER PRIMARY KEY, title TEXT, platform TEXT, genre TEXT, release_year INTEGER, path TEXT, added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
    } else {
        QMessageBox::critical(nullptr, "Error", "Failed to create the database.");
    }
}

void setupTables(Ui::MainWindow &ui) {
    //Music Model
    QSqlTableModel *musicModel = new QSqlTableModel();
    musicModel->setTable("music");
    musicModel->select();
    ui.musicTableView->setModel(musicModel);
    //Movies Model
    QSqlTableModel *moviesModel = new QSqlTableModel();
    moviesModel->setTable("movies");
    moviesModel->select();
    ui.moviesTableView->setModel(moviesModel);
    //TV Model
    QSqlTableModel *tvModel = new QSqlTableModel();
    tvModel->setTable("tv");
    tvModel->select();
    ui.tvTableView->setModel(tvModel);

    QSqlTableModel *photosModel = new QSqlTableModel();
    photosModel->setTable("photos");
    photosModel->select();
    ui.photosTableView->setModel(photosModel);

    QSqlTableModel *videosModel = new QSqlTableModel();
    videosModel->setTable("videos");
    videosModel->select();
    ui.videosTableView->setModel(videosModel);

    QSqlTableModel *gamesModel = new QSqlTableModel();
    gamesModel->setTable("games");
    gamesModel->select();
    ui.gamesTableView->setModel(gamesModel);

    QSqlTableModel *podcastsModel = new QSqlTableModel();
    podcastsModel->setTable("podcasts");
    podcastsModel->select();
    ui.podcastsTableView->setModel(podcastsModel);
}
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    initDB();

    QMainWindow mainWindow;
    Ui::MainWindow ui;
    ui.setupUi(&mainWindow);
    //Create table
    setupTables(ui);
    //Show Main Window
    mainWindow.show();
    return app.exec();
}