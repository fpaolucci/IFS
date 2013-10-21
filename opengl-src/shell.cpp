#include "shell.h"
Shell::Shell(){
//Inizializzazione var dinamiche
}
void Shell::messageExit(char*  text) {
        printf(text);
#if DEBUG==1
	getchar();
#endif
	exit(1);
}
void Shell::open(char * filename, List* l){
        FILE* f=fopen(filename,"r");
        if( f == NULL) messageExit("Errore Impossibile Trovare il File Di Configurazione\n");
        int str=0;
        int open=0;
        char texture[CHAR_LENGTH]="";
        bool ctexture=false;
        char msg[CHAR_LENGTH];
        char buf[CHAR_LENGTH];
            int token=0;
        Figure* fig;
        int val;
        double v;
        char * cmd;
        //FIRST PASS
        while( fscanf(f,"%s",buf)!=EOF ){
            if ( isNumeric(buf) ) continue;
            if ( strcmp(buf,"-color")== 0 ) continue;
            if ( strcmp(buf,"-position")== 0 ) continue;
            if ( strcmp(buf,"-size")== 0 ) continue;
            if ( strcmp(buf,"-rotation")== 0 ) continue;
            if ( strcmp(buf,"-rectstart")==0 ) continue;
            if ( strcmp(buf,"-rectend")==0 ) continue;
            if ( strcmp(buf,"color")== 0 ) continue;
            if ( strcmp(buf,"position")== 0 ) continue;
            if ( strcmp(buf,"size")== 0 ) continue;
            if ( strcmp(buf,"rotation")== 0 ) continue;
            if ( strcmp(buf,"rectstart")==0 ) continue;
            if ( strcmp(buf,"rectend")==0 ) continue;
            if ( strstr(buf,"-")==NULL ) continue;
                    sprintf(msg,"Comando \"%s\" inesistente!\nIl file non e' scritto correttamente...\n",buf);
                    messageExit(msg);
            }
        l->remAll();
        rewind(f);
        //ACQUISIZIONE VALORI
        while( fscanf(f,"%s",buf)!=EOF ){
                    if( ( strcmp(buf,"-rectstart")==0 || strcmp(buf,"rectstart")==0 ) && open!=0) {
                            sprintf(msg,"Controllare il codice sorgente: \"%s\" nidificati!\nComando \"-rectend\" mancante...\n",buf);
                            messageExit(msg);
                    } 
                    else if( ( strcmp(buf,"-rectend")==0  || strcmp(buf,"rectend")==0 ) && open!=1) {
                            sprintf(msg,"Controllare il codice sorgente: \"%s\" nidificati!\nComando \"-rectstart\" mancante...\n",buf);
                            messageExit(msg);
                    } 
            else if( strstr(buf,"-rectstart")!=NULL || strstr(buf,"rectstart")!=NULL){
                            open++;
                cmd=(char*)"-rectstart";
                fig= new Figure();
            }
            else if( strstr(buf,"-rectend")!=NULL || strstr(buf,"rectend")!=NULL ){
                            open--;
                cmd=(char*)"-rectend";
                if( !isReady(fig) ) delete fig;
                else {
                                    setCentre(fig);
                    l->insItem(fig);
                }
            }
            else if( strstr(buf,"-rotation")!=NULL || strstr(buf,"rotation")!=NULL  ){
                cmd=(char*)"-rotation";
                token=0;
            }
            else if( strstr(buf,"-size")!=NULL || strstr(buf,"size")!=NULL ){
                cmd=(char*)"-size";
                token=0;
            }
            else if( strstr(buf,"-position")!=NULL || strstr(buf,"position")!=NULL ){
                cmd=(char*)"-position";
                token=0;
            }
            else if( strstr(buf,"-color")!=NULL || strstr(buf,"color")!=NULL ){
                cmd=(char*)"-color";
                token=0;
            }
            else if( strcmp(cmd,"-color")==0 ){
                if( strcmp( buf,"rgb")==0) cmd=(char*)"-color rgb";
                else if( strcmp( buf,"texture")==0 ) cmd=(char*)"-color texture";
            }
            else if( strcmp(cmd,"-color rgb")==0 ){
                val=atoi(buf);
                switch( token){
                case 0: fig->r=val;
                    break;
                case 1: fig->g=val;
                    break;
                case 2: fig->b=val;
                    break;
                default:break;
                            }
                token++;
            }
                    else if( strcmp( cmd,"-color texture")==0 ){
                ctexture=true;
                strcat(texture,buf);
                strcat(texture," ");
                    }
            else if( strcmp(cmd,"-position")==0 ){
                val=atoi(buf);
                switch( token){
                case 0: fig->x=val;
                    break;
                case 1: fig->y=val;
                    break;
                default:break;
                }
                token++;
            }
            else if( strcmp(cmd,"-rotation")==0 ){
                v=atof(buf);
                fig->rot=v;
                token++;
            }
            else if( strcmp(cmd,"-size")==0 ){
                val=atoi(buf);
                switch( token){
                case 0: fig->w=val;
                    break;
                case 1: fig->h=val;
                    break;
                default:break;
                }
                token++;
            }
            if( ctexture==true && strcmp(cmd,"-color texture")!=0 ) {
            //Stampa stringa
            ctexture=false;
            char* p=NULL;
            while ( (p=strstr(texture,"\""))!=NULL ) {
                for (char* tmp=p; *p!='\0'; ){
                    p++;
                    *tmp=*p;
                    tmp++;
                }
            }
            texture[strlen(texture)-1]='\0';
            strcpy(fig->filename,texture);

            fig->isImage=1;
                    if( fopen(fig->filename,"r")==NULL ) {
                sprintf(texture,"Errore Filename Texture: %s\nControllare che il percorso texture sia tra virgolettee valido.\n",fig->filename);
                message(texture);
                l->remAll();
                }
                    else {
                            sprintf(texture,"Controllo texture %s ... completato!\n",fig->filename);
                            message(texture);
                    }
                    memset(texture,0,1024);
            }
        }
        fclose(f);
}
bool Shell::isReady(Figure* f){
        if ( f==NULL) return false;
        f->isReady=0;
        if( !numInRange( f->x,RANGE_COORD)  ) return false;
        if( !numInRange( f->y,RANGE_COORD)  ) return false;
        if( !numInRange( f->w,RANGE_COORD)  ) return false;
        if( !numInRange( f->h,RANGE_COORD)  ) return false;
            if ( f->w<=4 || f->h<=4) return false; 
        //if( !numInRange( f->rot,RANGE_COORD)  ) return false;
        //if( !numInRange( f->col.getRed(),RANGE_COLOR)  ) return false;
        //if( !numInRange( f->col.getRed(),RANGE_COLOR)  ) return false;
        //if( !numInRange( f->col.getRed(),RANGE_COLOR)  ) return false;
        f->isReady=1;
        return true;
}
int Shell::isNumeric(const char* p){
        bool floating=false;
        if (*p) {
             char c=*p++;
             if( !isdigit(c) && c!='-') return 0;
             while ((c=*p++)) {
                   if (isdigit(c)) continue;
                   if( !floating && c=='.') {
                       floating=true;
                       continue;
                   }
                   return 0;
             }
            return 1;
         }
         return 0;
}
bool Shell::numInRange(int val, int min, int max){
        if ( val >= min && val <=max ) return true;
        return false;
}
void Shell::setCentre(Figure* f){
	f->cx=f->x+(f->w/2.0f);
	//f->rot=int(f->rot)%90;
	f->cy=f->y+(f->h/2.0f);
}
void Shell::message(char* text){
#if LIBQT==1
    msg.setText(text);
    msg.exec();
#else
    printf(text);
#endif
}
