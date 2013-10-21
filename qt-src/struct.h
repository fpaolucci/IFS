#ifndef STRUCT_H
#define STRUCT_H
#include <QtGui>

typedef enum {
  NONE,
  DRAW,
  ROTATE,
  MOVE,
  FILL,
  RESIZE,
  TEXTURE,
  DELETE
} Mode;

struct Figure{
char filename[1024];
bool isImage;
int mx,my;
int resx,resy;
int x,y;
int w,h;
float rot,mrot;
QImage img;
QColor col,pencol;
int isReady;
} ;

struct Nodo{
 Figure* f;
 Nodo* next;
 Nodo* prec;
};
#endif // STRUCT_H
