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
    static void onFolderChanged(const QString &path);
    static void connectToEmby();
private:
    QFileSystemWatcher *fileWatcher;
    QSqlDatabase db;
    static QString mediaFolder;

    void setupDatabase();
    void createMediaFolder();
    void executeSql(const QString &filePath);
    void addFolder(const QString &folderName);
};

#endif // MAINWINDOW_H
