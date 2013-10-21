#pragma comment(lib, "glew32.lib")

#include <stdlib.h>
#include <stdio.h>
#include <GL\glew.h>
#include <GL\glut.h>

#include "Timer.h"
#include "IFS.h"
#include "shell.h"
#include "list.h"
#define MAXLVL 12.0f


int tex=0;
int buffvalue;
double buffocus;
double buffzoom;
IFS* ifs;
GLuint display;
float time;
float oldtime;
float  refresh;
List* l;
AUX_RGBImageRec *sliderRic,*sliderFoc,*scroll,*sliderZoom,*sliderScrollh;
int w,h,oldh;
double ratio;
Sliding s1,s2,s3;
Sliding* s;
float tx,ty;

void myRasterPos2f(int tx, int ty) {
    double x=tx;
    double y=ty;
    x= (x-0.5f*w)/w*2.0f ;
    y=-(y-0.5f*h)/h*2.0f ; 
    glRasterPos2f(x,y/ratio);
}
double myPosy(int ty) {
    double y=ty;
    y=-(y-0.5f*h)/h*2.0f ; 
    return y/ratio;
}
double myPosx(int tx) {
    double x=tx;
    x=(x-0.5f*w)/w*2.0f ; 
    return x;
}
void myKeyboardFunc( unsigned char key, int x, int y )
{
	switch ( key ) {
	case ' ':// Space bar
            // Increment the current mode, and tell operating system screen needs redrawing
            glutPostRedisplay();
            break;
	case 'w':
            ty+=0.025f;
            glutPostRedisplay();
            break;
	case 's':
            ty-=0.025f;
            glutPostRedisplay();
            break;
	case 'a':
            tx-=0.025f;
            glutPostRedisplay();
            break;
	case 'd':
            tx+=0.025f;
            glutPostRedisplay();
            break;
            case 27:// "27" is theEscape key
		exit(1);
	}
}
void myMouseFunc(int botton, int state,int x, int y){
	int dy=y;
	int dx=x;
	if ( x<400 && y>h-82) s=&s1;
	else if( x>=400 && y>h-82) s=&s2;
	else if ( y<h-82) s=&s3;
	if( dy>s->y-s->dimy && dy<s->y+s->dimy && dx>s->x-s->dimx && dx<s->x+s->dimx ) {
		s->isSelected=true;
	}
}
void myMotionFunc(int x, int y){
	if( s->isSelected && s->function_type==1) {
		if( x>s->max ) x=s->max;
		if (x<s->min ) x=s->min;
		s->x=x;
		double lvlval=(s->max-s->min)/MAXLVL;
		int result =(int) (s->x-s->min)/lvlval;
		s->value=result;
	}
	else if (s->isSelected && s->function_type==2){
		if( x>s->max ) x=s->max;
		if (x<s->min ) x=s->min;	
		s->x=x;
		double lvlval=(s->max-s->min)/2.0f;
		double result =(s->x-s->min)-lvlval;
		s->value=result/100.0f;
	}
	else if (s->isSelected && s->function_type==3){
		if( y>s->max ) y=s->max;
		if (y<s->min ) y=s->min;
		s->y=y;
		double lvlval=s->max-s->min;
		double result =(s->max-s->y)/lvlval;
		s->value=(-0.25f+result)*1.75f;
	}
}
void loadSlider(){
        sliderRic =LoadBMP( "Texture\\SliderRicorsione.bmp");
        if ( sliderRic == NULL) {
                char* buf=new char();
                printf("Errore Caricamento Interfaccia 1...contenuti mancanti\n");
                scanf("%s",buf);
        }
        else printf( "Caricamento Interfaccia 1 completato\n");
        scroll =LoadBMP( "Texture\\SliderScroll.bmp");
        if ( scroll == NULL) {
                char* buf=new char();
                printf("Errore Caricamento Interfaccia 2...contenuti mancanti\n");
                scanf("%s",buf);
        }
        else printf( "Caricamento Interfaccia 2 completato\n");
        sliderFoc =LoadBMP( "Texture\\SliderFocus.bmp");
        if ( sliderFoc == NULL) {
                char* buf=new char();
                printf("Errore Caricamento Interfaccia 3...contenuti mancanti\n");
                scanf("%s",buf);
        }
        else printf( "Caricamento Interfaccia 3 completato\n");

        sliderZoom =LoadBMP( "Texture\\SliderZoom.bmp");
        if ( sliderZoom == NULL) {
                char* buf=new char();
                printf("Errore Caricamento Interfaccia 4...contenuti mancanti\n");
                scanf("%s",buf);
        }
        else printf( "Caricamento Interfaccia 4 completato\n");
        sliderScrollh =LoadBMP( "Texture\\SliderScrollHor.bmp");
        if ( sliderScrollh == NULL) {
                char* buf=new char();
                printf("Errore Caricamento Interfaccia 4...contenuti mancanti!\n");
                scanf("%s",buf);
        }
        else printf( "Caricamento Interfaccia 4 completato\n");
}
void setSliderRic(){
        if(s1.function_type==0) s1.x=65;
        s1.function_type=1;
        s1.y=h-12;
        //CONSIDERO COME DIMENSIONE/2.0f
        s1.dimx=15;
        s1.dimy=20;
        s1.min=65;
        s1.max=340;
        double lvlval=(s1.max-s1.min)/MAXLVL;
        int result =(int) (s1.x-s1.min)/lvlval;
        s1.value=result;
        s1.isSelected=false;
}
void setSliderFoc(){
        if(s2.function_type==0) s2.x=602;
        s2.function_type=2;
        s2.y=h-12;
        //CONSIDERO COME DIMENSIONE/2.0f
        s2.dimx=15;
        s2.dimy=20;
        s2.min=465;
        s2.max=740;
        s2.value=((s2.x-s2.min)-(((double)s2.max-s2.min)/2.0f))/100.0f  ;
        s2.isSelected=false;
}
void setSliderZoom(){
        if( s3.function_type==0) s3.y=h-200;
        s3.y=h-(oldh-s3.y);
        s3.function_type=3;
        s3.x=18;
        //CONSIDERO COME DIMENSIONE/2.0f
        s3.dimx=20;
        s3.dimy=15;
        s3.min=h-320;
        s3.max=h-160;
        s3.value=(-0.25f+(s3.max-s3.y)/(((double)s3.max-s3.min)))*1.75f  ;
        s3.isSelected=false;
}
void drawScene(void)
{
	time=TimerGetTime();
	refresh+= (time-oldtime)/1000.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if( s1.value!=buffvalue || s2.value!=buffocus || s3.value!=buffzoom) {
		ifs->ifs_static(&display,1+s1.value,l->getCount(),l,s2.value,ratio,s3.value);
		buffvalue=s1.value;
		buffocus=s2.value;
		buffzoom=s3.value;
	}
	else {
		glLoadIdentity();
		glTranslatef(tx,ty,0);
		glCallList(display);
	}
	
	glLoadIdentity();
	double hiy=myPosy(h-82);
	double hfy=myPosy(h);
	glDisable(GL_TEXTURE_2D);
	glColor3ub(48,48,48);
	glBegin(GL_QUADS);
	glVertex2f(-1.0f,hiy);
	glVertex2f(1.0f, hiy);
	glVertex2f(1.0f, hfy);
	glVertex2f(-1.0f,hfy );
	glEnd();
	hiy=myPosy(0);
	hfy=myPosy(h);
	double fx=myPosx(60);
	glBegin(GL_QUADS);
	glVertex2f(-1.0f,hiy);
	glVertex2f(fx, hiy);
	glVertex2f(fx, hfy);
	glVertex2f(-1.0f,hfy );
	glEnd();

	glLoadIdentity();
	myRasterPos2f(0,h);
	glDrawPixels(sliderRic->sizeX,sliderRic->sizeY,GL_RGB,GL_UNSIGNED_BYTE, sliderRic->data);
	myRasterPos2f(s1.x,s1.y);
	glDrawPixels(scroll->sizeX,scroll->sizeY,GL_RGB,GL_UNSIGNED_BYTE, scroll->data);
	myRasterPos2f(400,h);
	glDrawPixels(sliderFoc->sizeX,sliderFoc->sizeY,GL_RGB,GL_UNSIGNED_BYTE, sliderFoc->data);
	myRasterPos2f(s2.x,s2.y);
	glDrawPixels(scroll->sizeX,scroll->sizeY,GL_RGB,GL_UNSIGNED_BYTE, scroll->data);
	myRasterPos2f(0,h-82);
	glDrawPixels(sliderZoom->sizeX,sliderZoom->sizeY,GL_RGB,GL_UNSIGNED_BYTE, sliderZoom->data);
	myRasterPos2f(s3.x,s3.y+5);
	glDrawPixels(sliderScrollh->sizeX,sliderScrollh->sizeY,GL_RGB,GL_UNSIGNED_BYTE, sliderScrollh->data);
	
	oldtime=time;
	//glFlush();
	glutSwapBuffers();
}

// Initialize OpenGL's rendering modes
void initRendering()
{
	glewInit();

	glEnable(GL_TEXTURE_2D);				// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);				// Enable Smooth Shading
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);			// Black Background
	glClearDepth(1.0f);					// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);				// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);					// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);			// Really Nice Point Smoothing
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	
	glEnable(GL_COLOR_MATERIAL);				// Enable Coloring Of Material

	TimerInit();
	ifs=new IFS();
	loadSlider();
	ifs->LoadTextures(l);
	refresh=1.0;
	buffvalue=-1;
	buffocus=-1;
	buffzoom=-1;
}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int width, int height)
{	
        oldh=h;
	w=width;
	h=height;
	setSliderRic();
	setSliderFoc();
	setSliderZoom();
	ratio=((double)w)/((double)h);

	if (height==0)	{		
                height=1;										
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();							// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.0,100.0f);
	//DEVO CONSIDERARE L'ASPECT RATIO SULLE DIMENSIONI
	glOrtho(-1.0f,1.0f,-1.0f/ratio,1.0f/ratio,-1.0f,100.0f);
	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glLoadIdentity();	
}

void TimerFunction(int value) {
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(15,TimerFunction, 1);
}

// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
	l=new List();
	Shell* s=new Shell();

#if DEBUG==0
	if( argc < 2) {
		printf( "Nessun File Di Configurazione trovato*.ifs\nImpossibile procedere con l'esecuzione del programma.\n");
		getchar();
		exit(0);
	}
	printf("Controllo del file di configurazione %s\n", argv[1]);
	s->open( argv[1],l);
#else 
	s->open( "data.ifs",l);
#endif

	glutInit(&argc,argv);

	// The image is not animated so single buffering is OK. 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	// Window position (from top corner), and size (width and hieght)
	glutInitWindowPosition( 20, 60 );
	glutInitWindowSize( (w=800), (h=600) );
	glutCreateWindow( "TRASFORMAZIONI GEOMETRICHE **OPENGL**" );

	// Initialize OpenGL as we like it..
	initRendering();

	// Set up callback functions for key presses
	glutMouseFunc( myMouseFunc);
	glutMotionFunc(myMotionFunc);
	glutKeyboardFunc( myKeyboardFunc );		// Handles "normal" ascii symbols
	// glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

	glutReshapeFunc( resizeWindow );

	glutDisplayFunc( drawScene );
        glutTimerFunc(30,TimerFunction, 1);

	glutMainLoop(  );

	return(0);	// This line is never reached.
}

