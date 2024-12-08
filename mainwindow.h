#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemWatcher>
#include <QSqlDatabase>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void onFolderChanged(const QString &path);
    void connectToEmby();
private:
    QFileSystemWatcher *fileWatcher;
    QSqlDatabase db;

    void setupDatabase();
    void scanAndOrganize();
    void createMediaFolder();
    void addShowsTable();
    void addShowsFolder();
    void addMoviesTable();
    void addMoviesFolder();
    void addMusicFolder();
    void addMusicTable();


};

#endif // MAINWINDOW_H
