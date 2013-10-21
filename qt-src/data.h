#ifndef DATA_H
#define DATA_H

#include <QtGui>
#include "struct.h"
#include "list.h"



class Data : QObject
{
public:
    Mode mode;
    int px,py;
    int tempx,tempy;
    int count;
    int isStillPressed;
    QString isNull;
    QString message;
    int refresh;
    QWidget * parent;
    QLabel *lmode,*lmouseX,*lmouseY,*lposX,*lposY, *lwidth,*lheight,*lrot;
    List* list;
    Figure* selection;
};

#endif // DATA_H
