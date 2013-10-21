#include "mainwindow.h"
#include "ui_mainwindow.h"
#define ADDCOLOR( r , g , b ) ui->comboBox->insertItem(cc,"");ui->comboBox->setItemData(cc++,QColor(r,g,b),Qt::BackgroundRole)
#define ADDICON( i, filename, path) icon[i].addFile(path+"\\"+QString::fromUtf8(filename), QSize(32,32), QIcon::Normal, QIcon::Off)

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("IFS Editor - Form Caso Base");
    QObject::connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(onDrawClick()));
    QObject::connect(ui->pushButton_2, SIGNAL(pressed()), this, SLOT(onRotateClick()));
    QObject::connect(ui->pushButton_1, SIGNAL(pressed()), this, SLOT(onMoveClick()));
    QObject::connect(ui->pushButton_3, SIGNAL(pressed()), this, SLOT(onFillClick()));
    QObject::connect(ui->pushButton_4, SIGNAL(pressed()), this, SLOT(onResizeClick()));
    QObject::connect(ui->pushButton_6, SIGNAL(pressed()), this, SLOT(onTextureClick()));
    QObject::connect(ui->pushButton_8, SIGNAL(pressed()), this, SLOT(onDeleteClick()));

    data=new Data();
    data->list=new List();
    data->lmode= ui->lab1;
    data->lmouseX=ui->label_3;
    data->lmouseY=ui->label_4;
    data->lposX=ui->label_5;
    data->lposY=ui->label_6;
    data->lwidth=ui->label_7;
    data->lheight=ui->label_8;
    data->lrot=ui->label_9;
    widget = new MyWidget(ui->centralWidget, data);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(200, 0, 600, 500));
    widget->setMouseTracking(true);
    widget->setStyleSheet(QString::fromUtf8("background-color: white ;"));
    QIcon icon[10] ;

    QString path = QApplication::applicationDirPath();
    path.replace("/","\\");
    ADDICON( 0, "icon\\disegna.png",path);
    ADDICON( 1, "icon\\resize.png",path);
    ADDICON( 2, "icon\\muovi.png",path);
    ADDICON( 3, "icon\\ruota.png",path);
    ADDICON( 4, "icon\\cancella.png", path);
    ADDICON( 5, "icon\\riempi.png", path);
    ui->pushButton->setIcon(icon[0]);
    ui->pushButton_4->setIcon(icon[1]);
    ui->pushButton_1->setIcon(icon[2]);
    ui->pushButton_2->setIcon(icon[3]);
    ui->pushButton_8->setIcon(icon[4]);
    ui->pushButton_3->setIcon(icon[5]);
    int cc=0;
    ui->comboBox->clear();
    ADDCOLOR(0,64,0);
    ADDCOLOR(0,96,0);
    ADDCOLOR(0,128,0);
    ADDCOLOR(0,192,0);
    ADDCOLOR(0,255,0);
    ADDCOLOR(0,128,128);
    ADDCOLOR(0,128,64);
    ADDCOLOR(0,64,64);
    ADDCOLOR(128,128,128);
    ADDCOLOR(64,128,128);
    ADDCOLOR(0,0,128);
    ADDCOLOR(0,0,255);
    ADDCOLOR(0,64,128);
    ADDCOLOR(0,255,255);
    ADDCOLOR(0,128,255);
    ADDCOLOR(0,128,192);
    ADDCOLOR(128,128,255);
    ADDCOLOR(0,0,160);
    ADDCOLOR(0,0,64);
    ADDCOLOR(192,192,192);
    ADDCOLOR(128,0,128);
    ADDCOLOR(128,0,64);
    ADDCOLOR(128,128,192);
    ADDCOLOR(255,128,192);
    ADDCOLOR(255,0,255);
    ADDCOLOR(255,0,128);
    ADDCOLOR(64,0,128);
    ADDCOLOR(255,128,128);
    ADDCOLOR(255,0,0);
    ADDCOLOR(128,64,64);
    ADDCOLOR(128,0,0);
    ADDCOLOR(0,0,0);
    ADDCOLOR(255,255,0);
    ADDCOLOR(255,128,0);
    ADDCOLOR(128,64,0);
    ADDCOLOR(128,128,0);
    //ui->comboBox->setItemData(4,Qt::white,Qt::DecorationRole);
    //QString path = QApplication::applicationDirPath();
//    QMessageBox msg;
//    msg.setText(path );
//    msg.exec();
   }

MainWindow::~MainWindow()
{
    delete ui;
}

//Aggiunge il valore dopo la pressione negandolo
void MainWindow::onDrawClick()
{
    QPushButton* btn=ui->pushButton;
    if ( !btn->isChecked() ) {
        widget->setMode(DRAW);
        this->setAllButtons(false);
    }
    else widget->setMode(NONE);
}
void MainWindow::onRotateClick(){
    QPushButton* btn=ui->pushButton_2;
    if ( !btn->isChecked() ) {
        widget->setMode(ROTATE);
        this->setAllButtons(false);
    }
    else widget->setMode(NONE);
}

void MainWindow::onMoveClick(){
    QPushButton* btn=ui->pushButton_1;
    if ( !btn->isChecked() ) {
        widget->setMode(MOVE);
        this->setAllButtons(false);
    }
    else widget->setMode(NONE);
}
void MainWindow::onFillClick(){
    QPushButton* btn=ui->pushButton_3;
    if ( !btn->isChecked() ) {
        widget->setMode(FILL);
        this->setAllButtons(false);
    }
    else widget->setMode(NONE);
}
void MainWindow::onResizeClick(){
    QPushButton* btn=ui->pushButton_4;
    if ( !btn->isChecked() ) {
        widget->setMode(RESIZE);
        this->setAllButtons(false);
    }
    else widget->setMode(NONE);
}
void MainWindow::onTextureClick(){
    QPushButton* btn=ui->pushButton_6;
    if ( !btn->isChecked() ) {
        widget->setMode(TEXTURE);
        this->setAllButtons(false);
    }
    else widget->setMode(NONE);
}
void MainWindow::onDeleteClick(){
    QPushButton* btn=ui->pushButton_8;
    if ( !btn->isChecked() ) {
        widget->setMode(DELETE);
        this->setAllButtons(false);
    }
    else widget->setMode(NONE);
}
void MainWindow::setAllButtons(bool val){
    ui->pushButton->setChecked(val);
    ui->pushButton_1->setChecked(val);
    ui->pushButton_2->setChecked(val);
    ui->pushButton_3->setChecked(val);
    ui->pushButton_4->setChecked(val);
    ui->pushButton_6->setChecked(val);
    ui->pushButton_8->setChecked(val);
}
void MainWindow::on_comboBox_highlighted(int index)
{
    QColor col= qVariantValue<QColor>(ui->comboBox->itemData(index , Qt::BackgroundRole) );
    QPalette palette;
    QBrush brush( col );
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::All, QPalette::Highlight,  brush);
    palette.setBrush(QPalette::All, QPalette::Base,  brush);
    ui->comboBox->setPalette(palette);
}

void MainWindow::on_comboBox_activated(int index)
{
    QColor col= qVariantValue<QColor>(ui->comboBox->itemData(index , Qt::BackgroundRole) );
    widget->setFillColor( col  );
}

void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Selezione Texture",QApplication::applicationDirPath());
    if (!fileName.isEmpty())
        ui->pushButton_6->setIcon(QIcon(fileName));
        widget->setTexture( fileName );
}

void MainWindow::on_pushButton_7_clicked()
{
    if( data->list->getFirst()!=NULL ){
    Shell* s=new Shell();
    s->convert("data.ifs",data);
    proc= new QProcess();
    QObject::connect(proc, SIGNAL(readyReadStandardOutput()),this,SLOT(openglProcess()));
    QObject::connect(proc, SIGNAL(readyReadStandardError()),this,SLOT(openglProcess()));
    proc->start("TransformOPENGL.exe", QStringList() << "data.ifs" );
    if( !proc->waitForStarted()){
        QMessageBox msg;
        msg.setText( "Processo di rendering fallito!\nImpossibile trovare l'eseguibile TransformOPENGL.exe\n");
        msg.exec();
        }
    }
    else {
    QMessageBox msg;
    msg.setText("Impossibile renderizzare!\nIl form è vuoto.");
    msg.exec();
    }
}
void MainWindow::openglProcess(){
    QMessageBox msg;
    msg.setText( proc->readAllStandardOutput());
    msg.exec();
}


void MainWindow::on_actionApri_triggered()
{
    QStringList filename;
    QFileDialog f;
    Shell s;
    QStringList filters;

    filters<< "Documento di Testo (*.txt)" << "Iterated Function System Files (*.ifs)";
    f.setFilters( filters) ;
    f.setDirectory(QApplication::applicationDirPath());
    if( f.exec() ){
    filename= f.selectedFiles();
    QString str=filename.first();
    std::string str2= str.toStdString();
    char tmp[1024];
    memset(tmp,0,1024);
    strcpy(tmp, str2.data());
    s.open(tmp,data);
    ui->lab1->setText(QString::number(data->count));
    }
}

void MainWindow::on_actionSalva_triggered()
{
    QString filename;
    char* file;
    QFileDialog f;
    Shell s;
    QStringList filters;
    f.setAcceptMode(QFileDialog::AcceptSave);
    filters<< "Documento di Testo (*.txt)" << "Iterated Function System Files (*.ifs)";
    f.setDirectory(QApplication::applicationDirPath());
    f.setFileMode(QFileDialog::AnyFile);
    f.setFilters( filters) ;
    if( f.exec() ){
    char* filtro=NULL;
    filename= f.selectedFiles().first();
    if( f.selectedNameFilter().contains("Documento Di Testo", Qt::CaseInsensitive) )filtro=(char*)".txt";
    else if (f.selectedNameFilter().contains("Iterated Function System Files", Qt::CaseInsensitive) ) filtro=(char*)".ifs";
    file=((QByteArray)((filename).toAscii())).data();
    if ( strstr(file , filtro )==NULL ) strcat(file,filtro);
    s.convert(file,data);
    }
}


void MainWindow::on_actionNuovo_triggered()
{
    QMessageBox msg;
    msg.setText("Sei sicuro di volere eliminare il foglio esistente?");
    QAbstractButton *yes =msg.addButton(QMessageBox::Yes);
    msg.addButton(QMessageBox::No);
    msg.exec();
    if (msg.clickedButton()==yes)
      data->list->remAll();
}
