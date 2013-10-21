#include "IFS.h"

IFS::IFS(void){
//Inizializzare variabili dinamiche;
}

IFS::~IFS(void){
//Gestire variabili dinamiche
}

void IFS::LoadTextures(List*l){
        Figure* f;
        GLuint texture[100];
        glGenTextures(l->getCount(), &texture[0] );
        for (int i=0; (f=l->get(i))!=NULL; i++) {
                if ( strstr(f->filename,".bmp")!=NULL ) {
                        AUX_RGBImageRec* tex;
                        tex =LoadBMP( f->filename);
                        if ( tex == NULL) {
                                char* buf=new char();
                                printf("Errore Caricamento Texture...\nFile per la texture non trovato, ignorare la texture e continuare? (y/n)\n");
                                scanf("%s",buf);
                                        if( buf=="y" ){
                                                f->isImage=0;
                                                sscanf(f->filename,"");
                                        }
                        }
                        else {printf( "Caricamento Texture completato\n");
                        f->texID=texture[i];
                        invertBMP(tex);
                        glBindTexture(GL_TEXTURE_2D, f->texID);
                        glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                        glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                        glTexImage2D( GL_TEXTURE_2D, 0 ,GL_RGB, tex->sizeX, tex->sizeY, 0 , GL_RGB, GL_UNSIGNED_BYTE, tex->data);
                        }
                        }
                else if( strstr(f->filename,".tga")!=NULL ){
                        // PROCEDURA LETTURA TGA
                        Texture tga;
                        bool load = LoadTGA( &tga, "Texture/foglia.tga");
                        if ( load == false) printf("Errore Caricamento Texture TGA\n");
                        else {
                        printf("Caricamento Texture TGA completato\n");
                        f->texID=texture[i];
                        glBindTexture( GL_TEXTURE_2D, f->texID );
                        glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                        glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                        glTexImage2D( GL_TEXTURE_2D, 0 ,GL_RGBA  , tga.width, tga.height, 0 , tga.type,  GL_UNSIGNED_BYTE, tga.imageData);
                        }
                }
        }
}

void IFS::ifs_static( GLuint* disp, int lvl , float base, List*l,float aliasing,double aspect, double ztran) {
	ratio=aspect;
	*disp=glGenLists(1);
	max=0.0f;
	lev=lvl;
	min=1000.0f;
	resize=aliasing;
	glNewList(*disp, GL_COMPILE);
	double* min=getMiniumBorder(l);
	double* screensize=getMaximumSize(l);
	glTranslatef(-0.5*min[0]/screensize[0]+0.04f,+1.0*min[1]/screensize[1]+0.04f,0);
	glScalef(ztran+1.0f,ztran+1.0f,1.0f);
	Ricorsione(lvl,l,screensize,1.0f,1.0f);
	free(min);
	free(screensize);
	glEndList();
}

void IFS::Ricorsione(int lvl, List*l, double* screensize , float sizex, float sizey){
	lvl--;
	Figure* f;
	for (int i=0; (f=l->get(i))!=NULL; i++) {
		float ppx,ppy;
		float dimx=sizex, dimy=sizey;
		ppx=-sizex/2.0f+sizex*(f->w/2.0f+f->x)/screensize[0]; //GIA HO TRASLATO NON DEVO USA PX
		ppy=-sizey/2.0f+sizey*(f->h/2.0f+f->y)/screensize[1];
		dimx=sizex*(f->w/screensize[0]);
		dimy=sizey*(f->h/screensize[1]);
		glTranslatef(+ppx,-ppy,0);
		glRotatef(f->rot,0,0,1);
		if( lvl<=0 ) {
			if(f->isImage==true){
				glEnable(GL_TEXTURE_2D);
				glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
				//glBlendEquation(GL_FUNC_ADD);
				glBlendFunc( GL_SRC_COLOR, GL_ONE);
				glColor3f(1.0,1.0,1.0);
				glEnable(GL_BLEND);
				glBindTexture( GL_TEXTURE_2D, f->texID);
			}
			else glColor3ub(f->r,f->g,f->b);
			float Xdim=dimx/2.0f;
			Xdim*=(1.0f+resize*abs(log10(Xdim)));
			float Ydim=dimy/2.0f;
			Ydim*=(1.0f+resize*abs(log10(Ydim)));
			glBegin(GL_QUADS);
			glTexCoord2f (0,1);		glVertex3f(-Xdim,Ydim,0);
			glTexCoord2f (0,0);		glVertex3f(-Xdim,-Ydim,0);
			glTexCoord2f (1,0);		glVertex3f(+Xdim,-Ydim,0);
			glTexCoord2f (1,1);		glVertex3f(+Xdim,Ydim,0);
			glEnd();
			if(f->isImage==true) {
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
			}
		}
			if( lvl>0) 	Ricorsione(lvl,l,screensize,dimx,dimy) ;
			glRotatef(-f->rot,0,0,1);
			glTranslatef(-ppx,+ppy,0);
	}
}

double* IFS::getMaximumSize(List*l){
	double* maxsize= (double*) malloc (sizeof(double) *2);
	maxsize[0]=0;
	maxsize[1]=0;
	Figure* f;
	for (int i=0; (f=l->get(i))!=NULL; i++) {
		if( f->x+f->w > maxsize[0] ) maxsize[0]=f->x+f->w;
		if( f->y+f->h > maxsize[1] ) maxsize[1]=f->y+f->h;
	}
	if( maxsize[0]>maxsize[1]) maxsize[1]=maxsize[0];
	else maxsize[0]=maxsize[1];
	return maxsize;
}
double* IFS::getMiniumBorder(List*l){
	double* min= (double*) malloc (sizeof(double) *2);
	min[0]=999999999.0;
	min[1]=999999999.0;
	Figure* f;
	for (int i=0; (f=l->get(i))!=NULL; i++) {
		if( f->x < min[0] ) min[0]=f->x;
		if( f->y < min[1] ) min[1]=f->y;
	}
	return min;
}