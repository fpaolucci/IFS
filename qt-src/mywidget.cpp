#include "mywidget.h"
#include "string.h"
#define M_PI		3.14159265358979323846


 MyWidget::MyWidget()
 {
     QPalette palette(MyWidget::palette());
     palette.setColor(QPalette::Window, Qt::green);
     this->setPalette(palette);

 }
 MyWidget::MyWidget(QWidget * parent, Data* data){
     this->data=data;
     this->setParent(parent);
     this->setMouseTracking(true);
     this->setStyleSheet(QString::fromUtf8("background-color: green"));
     this->setMode( NONE );
     this->setFillColor( QColor(0,170,0) );
 }

 bool MyWidget::setMode(Mode mode ){
 switch ( mode ){

    case DRAW:
        data->mode=DRAW;
        this->setCursor(QCursor(Qt::CrossCursor));
        this->data->lmode->setText("DISEGNA");
        return true;
        break;
    case ROTATE:
         data->mode=ROTATE;
         this->setCursor(QCursor(Qt::SizeBDiagCursor));
         this->data->lmode->setText("RUOTA");
         return true;
         break;
    case MOVE:
         data->mode=MOVE;
         this->setCursor(QCursor(Qt::SizeAllCursor));
         this->data->lmode->setText("SPOSTA");
         return true;
         break;
    case FILL:
      data->mode=FILL;
      this->setCursor(QCursor(Qt::PointingHandCursor));
      this->data->lmode->setText("COLORA");
      return true;
      break;
    case RESIZE:
      data->mode=RESIZE;
      this->setCursor(QCursor(Qt::SizeHorCursor));
      this->data->lmode->setText("RIDIMENSIONA");
      return true;
      break;
    case TEXTURE:
       data->mode=TEXTURE;
       this->setCursor(QCursor(Qt::PointingHandCursor));
       this->data->lmode->setText("APPLICA TEXTURE");
       return true;
       break;
    case DELETE:
       data->mode=DELETE;
       this->setCursor(QCursor(Qt::CrossCursor));
       this->data->lmode->setText("CANCELLA");
       return true;
       break;
    default: data->mode=NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
        this->data->lmode->setText("");
         return false;
    }
}
 void MyWidget::setFillColor( QColor color){
    this->brush=QBrush( color);
 }
 void MyWidget::setTexture(QString filename){
    this->img=QImage(filename);
    this->filename=filename;
 }
 void MyWidget::paintEvent(QPaintEvent *)
 {
     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing);
     painter.setPen(Qt::darkGreen);

      Figure* f;
      for(int i=0; (f=data->list->get(i))!=NULL ; i++ ){
             if( f!=NULL && f->isReady){
                 painter.setBrush(f->col);
                 painter.setPen(f->pencol);
                 painter.save() ;
                 painter.translate(f->mx,f->my);
                 painter.translate(f->x+f->w/2.0f,f->y+f->h/2.0f);
                 painter.rotate( - (f->rot+f->mrot) );
                 if( !f->isImage){
                         painter.drawRect( -f->w/2.0f, -f->h/2.0f, f->w+f->resx, f->h+f->resy);
                     }
                 else if( !f->img.isNull()) {
                     QRectF target(-f->w/2.0f, -f->h/2.0f, f->w+f->resx, f->h+f->resy);
                     painter.drawImage(target,f->img);
                    }
                 painter.restore();
                }
             }
         if( data->selection!=NULL ){
             painter.setPen(Qt::white);
         Figure* f=data->selection;
         painter.save() ;
         painter.translate(f->mx,f->my);
         double tx,ty;
         tx=f->x+(f->w+f->resx)/2.0f;
         ty=f->y+(f->h+f->resy)/2.0f;
         painter.translate(tx,ty);
         painter.rotate( - (f->rot+f->mrot) );
         double x0,y0;
         x0= (f->w+f->resx)/4.0f;
         y0= (f->h+f->resy)/4.0f;
         painter.drawLine( -x0, -y0, x0, y0);
         painter.drawLine( -x0, y0, x0, -y0);
         painter.restore();
        }
     this->update();
 }

 void MyWidget::mouseMoveEvent(QMouseEvent *event){
     data->lmouseX->setText("Mouse X: "+ QString::number(event->x()) );
     data->lmouseY->setText("Mouse Y: "+ QString::number(event->y()) );
     switch( data->mode){
     case DRAW:
         if( data->isStillPressed == 1){
             Figure* f = data->list->getLast();
             if ( f == NULL) {
                 msg.setText("Errore Nel Pop Della Lista\nFigura non trovata");
                 msg.exec();
                 return;
             }
             data->selection=f;
             f->w=event->x()-f->x;
             f->h=event->y()-f->y;
             f->col=Qt::white;
             f->pencol=Qt::red;
             if( f->w>=4 && f->h>=4) {
                 f->isReady=2;
             }
         }
        break;
     case ROTATE:
        if( data->isStillPressed && data->selection!=NULL ){
        int x,y;
        double caty,catx,ipot;
        double rot;
        double startx,starty,startipot;
        double startrot;
        x=event->x();
        y=event->y();
        starty=-(data->tempy-(data->selection->y+data->selection->h/2.0f));
        startx=data->tempx-(data->selection->x+data->selection->w/2.0f);
        caty=-(y-(data->selection->y+data->selection->h/2.0f));
        catx=x-(data->selection->x+data->selection->w/2.0f);
        startipot= sqrt(starty*starty + startx*startx );
        startrot= asin( starty/startipot )/M_PI*180.0f;
        ipot= sqrt( caty*caty + catx*catx );
        rot= asin( caty/ipot )/M_PI*180.0f;
        if( catx <0 ) rot=180-rot;
        data->selection->mrot=rot-startrot;
        }
        break;
     case MOVE:
        if( data->isStillPressed && data->selection!=NULL ){
        int x,y;
        x=event->x();
        y=event->y();
        int dx,dy;
        dx=x-data->tempx;
        dy=y-data->tempy;
        data->selection->mx=dx;
        data->selection->my=dy;
        this->data->lposX->setText("Px: "+ QString::number(data->selection->mx+data->selection->x) );
        this->data->lposY->setText("Py: "+ QString::number(data->selection->my+data->selection->y) );
        }
        break;
     case RESIZE:
        if( data->isStillPressed && data->selection!=NULL ){
        int x,y;
        x=event->x();
        y=event->y();
        int dx,dy;
        dx=(x-data->tempx)*cos(data->selection->rot/180.0f*M_PI)-(y-data->tempy)*sin(data->selection->rot/180.0f*M_PI);
        dy=+(x-data->tempx)*sin(data->selection->rot/180.0f*M_PI)+(y-data->tempy)*cos(data->selection->rot/180.0f*M_PI);;
        if( data->selection->w+dx<0) dx=-data->selection->w;
        if( data->selection->h+dy<0) dy=-data->selection->h;
        data->selection->resx=dx;
        data->selection->resy=dy;
        }
        break;
     default: break;
     }
     if(data->selection!=NULL){
        this->data->lwidth->setText("Width: "+ QString::number(data->selection->resx+data->selection->w) );
        this->data->lheight->setText("Height: "+ QString::number(data->selection->resy+data->selection->h) );
        this->data->lposX->setText("Px: "+ QString::number(data->selection->mx+data->selection->x) );
        this->data->lposY->setText("Py: "+ QString::number(data->selection->my+data->selection->y) );
        this->data->lrot->setText("Rotation: "+QString::number(data->selection->mrot+data->selection->rot));
     }
 }

 void MyWidget::mousePressEvent(QMouseEvent *event){
     data->isStillPressed=1;
     Figure* f;
     switch( data->mode){
     case DRAW:
        f=new Figure();
        f->isReady=0;
        f->x=event->x();
        f->y=event->y();
        data->list->insItem(f);
        this->data->lposX->setText( "Px: "+QString::number(event->x() )) ;
        this->data->lposY->setText( "Py: "+QString::number(event->y())) ;
        break;
     case ROTATE:
        data->tempx=event->x();
        data->tempy=event->y();
        break;
     case MOVE:
        data->tempx=event->x();
        data->tempy=event->y();
        break;
     case RESIZE:
        data->tempx=event->x();
        data->tempy=event->y();
        break;
     default: break;
     }
 }
 void MyWidget::mouseDoubleClickEvent(QMouseEvent *event){
     if ( event->button()==Qt::RightButton && data->selection!=NULL)
         data->selection=NULL;

     if( event->button()==Qt::LeftButton){
         Figure* f;
          for(int i=0; (f=data->list->get(i))!=NULL ;i++){
               if( event->x() >=f->x && event->x() <f->x+f->w &&
                   event->y() >=f->y && event->y() <f->y+f->h  )
               data->selection= f;
        }
      }

     if( event->button()==Qt::LeftButton && data->mode==FILL && data->selection!=NULL){
        data->selection->col=this->brush.color();
        data->selection->isImage=false;
     }
     if( event->button()==Qt::LeftButton && data->mode==TEXTURE && data->selection!=NULL && !this->img.isNull()){
        data->selection->img=this->img;
        data->selection->isImage=true;
        std::string filen = this->filename.toStdString();
        int size= filen.length();
        memset(data->selection->filename,0,1024);
        filen.copy(data->selection->filename,size,0);
     }
     if( event->button()==Qt::LeftButton && data->mode==DELETE && data->selection!=NULL ){
         QMessageBox msg;
         switch (data->list->delItem(data->selection)){

         case 0:
             msg.setText("Errore Figura Non Presente");
             break;
         case 1:
             msg.setText("Cancellazione Corretta");
             break;
         case -1:
             msg.setText("Figura Passata NULLA");
             break;
         }
        msg.exec();
        data->selection=NULL;
        }
     if(data->selection!=NULL){
        this->data->lwidth->setText("Width: "+ QString::number(data->selection->resx+data->selection->w) );
        this->data->lheight->setText("Height: "+ QString::number(data->selection->resy+data->selection->h) );
        this->data->lposX->setText("Px: "+ QString::number(data->selection->mx+data->selection->x) );
        this->data->lposY->setText("Py: "+ QString::number(data->selection->my+data->selection->y) );
        this->data->lrot->setText("Rotation: "+QString::number(data->selection->mrot+data->selection->rot));
     }
     else{
         this->data->lwidth->setText("" );
         this->data->lheight->setText("" );
         this->data->lposX->setText("" );
         this->data->lposY->setText("" );
         this->data->lrot->setText("" );
     }
 }
void MyWidget::mouseReleaseEvent(QMouseEvent *event){
    data->isStillPressed=0;
    Figure* f;
     switch( data->mode ){
     case DRAW:
        f = data->list->popLast();
        if ( f == NULL) {
            msg.setText("Errore Nel Pop Della Lista\nFigura non trovata");
            msg.exec();
            return;
        }
        if( f->isReady==1 ){
            data->list->insItem(f);
            break;
        }
        f->w=event->x()-f->x;
        if( event->x()-f->x <0 ) {
            f->w=f->x-event->x();
            f->x=event->x();
        }
        f->h=event->y()-f->y;
        if( event->y()-f->y <0 ) {
            f->h=f->y-event->y();
            f->y=event->y();
        }
        //if( f->w>=f->h ) f->h=f->w;
        //else f->w=f->h;
        f->col=this->brush.color();
        f->pencol=Qt::darkGreen;
        f->isReady=1;
        if( f->w>=4 && f->h>=4) {
            data->list->insItem(f);
        }
        else delete f;
        break;
     case ROTATE:
        if( data->selection!=NULL ){
        data->selection->rot+=data->selection->mrot;
        data->selection->mrot=0;
        }
        break;
     case MOVE:
        if( data->selection!=NULL ){
        data->selection->x+=data->selection->mx;
        data->selection->y+=data->selection->my;
        data->selection->mx=0;
        data->selection->my=0;
        }
        break;
     case RESIZE:
        if( data->selection!=NULL) {
        data->selection->w+=data->selection->resx;
        data->selection->h+=data->selection->resy;
        data->selection->resx=0;
        data->selection->resy=0;
        }
        break;
     default: break;
    }
 }
