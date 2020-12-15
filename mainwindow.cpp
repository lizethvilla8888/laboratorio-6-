#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>

#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    h_limit = 2000;
    v_limit = 1000;
    dt = 0.1;

    timer = new QTimer(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-h_limit/2,-v_limit/2,h_limit,v_limit);

    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowTitle("Sistema interplanetario");

    timer->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete scene;
}

void MainWindow::actualizar()
{
        for (int i=0;i<bars.size() ;i++ ) {
        for (int j=0;j<bars.size() ;j++ ) {
            if(i!=j){
                bars.at(i)->getEsf()->acelerar(bars.at(j)->getEsf()->getPX(),bars.at(j)->getEsf()->getPY(),bars.at(j)->getEsf()->getMasa());
                bars.at(i)->actualizar(dt);
                }
            }
        }
}


void MainWindow::on_Agregar_clicked()
{
    can++;
    double x= ui->PX->text().toDouble();
    double y= ui->PY->text().toDouble();
    double vx= ui->VX->text().toDouble();
    double vy= ui->VY->text().toDouble();
    double r= ui->Radio->text().toDouble();
    double m= ui->Masa->text().toDouble();

   bars.append(new cuerpograf(x,y,vx,vy,m,r));
  qDebug () << "cuerpo agregado a lista"<<can;
}

void MainWindow::on_Inicio_clicked()
{
    int num = 0;
    qDebug () << "num inicializado en 0"<<num;
    for (int i=0;i<bars.size() ;i++ ) {
        bars.at(i)->actualizar(dt);
        scene->addItem(bars.at(i));
        // qDebug () << "cuerpo agregado a la esena"<<i;
    }
    num = bars.size();
    qDebug () << "numero de elemetos de lista"<<num;
    timer->start(dt);
}

void MainWindow::on_Pausa_clicked()
{
    timer->stop();
}
