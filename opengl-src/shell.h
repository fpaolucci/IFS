#ifndef SHELL_H
#define SHELL_H
#define LIBQT 0
#if LIBQT==1
#include <QtGui>
#include "data.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define MIN -100
#define MAX 1500
#define RANGE_COORD -100, 1500
#define RANGE_COLOR 0, 255
#define DEBUG 1
#define CHAR_LENGTH 1024

class Shell{
public :
Shell();
void messageExit(char*  text) ;
void open(char * filename, List* l);
bool isReady(Figure* f);
int isNumeric(const char* p);
bool numInRange(int val, int min, int max);
void setCentre(Figure* f);
void message(char* text);
};
