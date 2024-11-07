//
// Created by Matthew Winer on 11/7/24.
//

#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class browser; }
QT_END_NAMESPACE

class databasehandler;
class filemanager;
class browser : public QMainWindow {
    Q_OBJECT

public:
    explicit browser(QWidget *parent = nullptr);
    ~browser() override;
private slots:
    void on_addFileButton_clicked();
private:
    Ui::browser *ui;
    databasehandler *dbHandler;
    filemanager *fileManager;
};


#endif //BROWSER_H
