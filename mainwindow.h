#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemWatcher>
#include <QSqlDatabase>
#include <QTableView>


QT_BEGIN_NAMESPACE
namespace Ui{ class MainWindow;}
QT_END_NAMESPACE
class MainWindow : public QMainWindow {
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

    Ui::MainWindow *ui;

    void setupDatabase();
    void createMediaFolder();
    void executeSql(const QString &filePath);
    void addFolder(const QString &folderName);
    void loadTableData(const QString &tableName, QTableView *tableView);
};

#endif // MAINWINDOW_H
