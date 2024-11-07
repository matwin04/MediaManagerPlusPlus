//
// Created by Matthew Winer on 11/7/24.
//

#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class browser; }
QT_END_NAMESPACE

class DatabaseHandler;
class FileManager;
class browser : public QMainWindow {
    Q_OBJECT

public:
    explicit browser(QWidget *parent = nullptr);
    ~browser() override;
private slots:
    void on_addFileButton_clicked();
private:
    Ui::browser *ui;
    DatabaseHandler *dbHandler;
    FileManager *fileManager;
};


#endif //BROWSER_H
