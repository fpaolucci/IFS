#ifndef IFS_H
#define IFS_H
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include "Method.h"
#include "Texture.h"
#include "list.h"


#define M_PI 3.14159265358979323846
#define size 17000
#define ntexture 10

typedef struct _fractal{
	float dimx,dimy;
	float lvl;
	float angle;
	float resize;
	float px,py;

} Frattale;

class IFS
{
public:
	Frattale fract[size]; 
	int count;
	float startangle;
	float min,max;
	float resize;
	int lev;
	float centerx,centery;
	GLuint texture[ntexture];
	double ratio;
	
        IFS(void);
        ~IFS(void);
        void LoadTextures(List*l);
	void ifs_static( GLuint* disp, int lvl , float base, List*l,float aliasing,double aspect, double ztran) ;
	void Ricorsione(int lvl, List*l, double* screensize , float sizex, float sizey);
	double* getMaximumSize(List*l);
	double* getMiniumBorder(List*l);
};

#endif