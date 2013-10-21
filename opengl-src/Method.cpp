#include "Method.h"
AUX_RGBImageRec *LoadBMP(char *Filename){
	FILE *File=NULL;									
	if (!Filename)	{
		return NULL;									
	}
	File=fopen(Filename,"r");							
	if (File){
		fclose(File);									
		return auxDIBImageLoad(Filename);				
	}
	return NULL;										
}

void invertBMP (AUX_RGBImageRec* tex){
	int dim=tex->sizeX*tex->sizeY*3;
	for(int i=0; i<dim ;i++){
		tex->data[i]=255-tex->data[i];
	}
}
void invertXY (AUX_RGBImageRec* tex) {
	int dim=tex->sizeX*tex->sizeY*3;
	int sizeX=tex->sizeX;
	int sizeY=tex->sizeY;
	unsigned char *arr=(unsigned char *) malloc( sizeof(unsigned char)*dim);
	for (int i=0; i<dim;i++)
		arr[i]=tex->data[i];
	for(int j=0; j<tex->sizeX*3 ;j+=3)
		for (int i=0; i<tex->sizeY*3;i+=3){
		tex->data[i+j*sizeY]=arr[i*sizeX+j];
		tex->data[1+i+j*sizeY]=arr[i*sizeX+j];
		tex->data[2+i+j*sizeY]=arr[i*sizeX+j];
	}
	tex->sizeX=sizeY;
	tex->sizeY=sizeX;
}
