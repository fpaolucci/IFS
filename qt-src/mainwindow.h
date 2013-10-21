#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qvariant.h>
#include "mywidget.h"
#include "data.h"
#include "shell.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Data* data;
    MyWidget* widget;
    QProcess* proc;
public slots:
    void onDrawClick();
    void onRotateClick();
    void onMoveClick();
    void onFillClick();
    void onResizeClick();
    void onTextureClick();
    void onDeleteClick();
    void setAllButtons(bool val);
    void openglProcess();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_actionNuovo_triggered();
    void on_actionSalva_triggered();
    void on_actionApri_triggered();
    void on_pushButton_7_clicked();
    void on_pushButton_5_clicked();

    void on_comboBox_activated(int index);
    void on_comboBox_highlighted(int index);
};

#endif // MAINWINDOW_H
