#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include "ui_MainWindow.h"
using namespace std;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow mainWindow;
  Ui::MainWindow ui;
  ui.setupUi(&mainWindow);
  //Create table
  QStandardItemModel model(4,2);
  model.setHorizontalHeaderLabels({"COL 1","COL 2"});
  ui.tableView->setModel(&model);
  mainWindow.show();
  return app.exec();
}