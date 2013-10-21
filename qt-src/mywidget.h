#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtGui>
#include "data.h"
#include "list.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE


class MyWidget : public QWidget
{

public:
    Data* data;
    QLabel* lab1;
    QBrush brush;
    QImage img;
    QString filename;
    int x,y;
    QMessageBox msg;
public:
    MyWidget();
    MyWidget(QWidget * parent, Data* data);
    void setDataObj(Data* data);
    bool setMode(Mode mode );
    void setFillColor( QColor color);
    void setTexture(QString filename);
protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *event);

};

#endif// MYWIDGET_H
