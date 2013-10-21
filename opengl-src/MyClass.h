#include <stdlib.h>
#include "Method.h"
typedef enum {
GIU=0,
SINISTRA=4,
DESTRA=8,
SU=12
} SPRITE;

typedef struct _Img {
	char* anim[16];
}sprite;
class MyClass {
	AUX_RGBImageRec* img;
	char* anim[16];
public:
	MyClass(){
	}
	void Init(){
		printf("OK CLASSE");
		img= LoadBMP("Immagini/pg01.bmp");
		return;
	}
	void DrawScene(){
		//DrawPunto();
		DrawImage();
	}
	void DrawPunto(){
		glColor4f(1.0,1.0,1.0f,1.0f);
		glPointSize(20.0f);
		glBegin(GL_POINTS);
		glVertex3f(0.0f,0.0f,-5.0f);
		glEnd();
	}
	void DrawImage(){
		glLoadIdentity();
		glRasterPos3f(0,0,-1);
		//glBitmap( img->sizeX,img->sizeY, img->sizeX/2,img->sizeY/2, img->sizeX*4 , img->sizeY*4 , img->data);
		glDrawPixels(img->sizeX,img->sizeY/4,GL_RGB,GL_UNSIGNED_BYTE, img->data);
	}
	void Spezzetta(){
		for (int i=0; i<16 ;i++)
			anim[i]=(char*) malloc( sizeof(char) * img->sizeX / 4 * img->sizeY / 4 * 3 );
		for (int i=0; i<img->sizeX*img->sizeY ;i++){
			
		} 
	}
};