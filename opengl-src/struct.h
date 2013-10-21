#ifndef STRUCT_H
#define STRUCT_H

struct Figure {
bool isImage;
int x,y;
int w,h;
double cx,cy;
float rot;
int isReady;
int r,g,b;
char filename[1024];
GLuint texID;
} ;

struct Nodo{
 Figure* f;
 Nodo* next;
 Nodo* prec;
};
struct Sliding{
int x,y;
int max,min;
int dimx,dimy;
bool isSelected;
double value;
int function_type;
};
#endif // STRUCT_H
