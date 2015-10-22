#include "twochessboard.h"
#include "ui_twochessboard.h"
#include "mainwindow.h"

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPixmap>

twoChessBoard::twoChessBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::twoChessBoard)
{

    ui->setupUi(this);
    ui->widget->setGeometry(QRect(0,200,480,480));
    graphicsView = new QGraphicsView(ui->widget);
    scene = new QGraphicsScene(QRect(-240,-240,480,480));
    graphicsView->setGeometry(QRect(0,0,480,480));
    graphicsView->setScene(scene);
    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::white);
    QBrush greenBrush(Qt::green);
    QPen pen(Qt::transparent);
    pen.setWidth(0);

    //scene->setSceneRect(0,150,300,300);
    //chessboard = new QVector< QVector<QGraphicsRectItem*> >(CHESSBOARD_SIZE);

    for(int i=0;i<CHESSBOARD_SIZE;i++){

        chessboard[i].resize(CHESSBOARD_SIZE);
        for(int j = 0 ; j<CHESSBOARD_SIZE;j++){
            chessboard[i][j] = new QGraphicsRectItem(CHESSBOARD_GRID_SIZE*(j-CHESSBOARD_SIZE/2) , CHESSBOARD_GRID_SIZE*( -i+CHESSBOARD_SIZE/2) ,
                            CHESSBOARD_GRID_SIZE ,CHESSBOARD_GRID_SIZE);
            scene->addItem(chessboard[i][j]);
            chessboard[i][j]->setPen(pen);

            chessboard[i][j]->setBrush(((i+j)%2==0)?blackBrush:whiteBrush);

        }
    }
    graphicsView->show();
    qDebug("Initilized chessboard...");


    //pawnPiece = new Pawn();
    //scene->addItem(pawnPiece);

    //pawnPiece->scenePos();




    //QPixmap board("/EmptyBoard.png");

    //ui->graphicsView->setScene(scene);
    //board->load("EmptyBoard.png");
    //scene->addPixmap(board);

    //scene->addRect(-100,-100,50,50,blackPen,yellowBrush);


}

twoChessBoard::~twoChessBoard()
{
    qDebug("Free chessboard...");
    for(int i=0;i<CHESSBOARD_SIZE;i++){
        for(int j = 0 ; j<CHESSBOARD_SIZE;j++){
            delete chessboard[i][j];
        }

    }
    //delete chessboard;
    delete scene;
    delete ui;
}

void twoChessBoard::on_pushButton_2_clicked()
{
    //MainWindow m;
    //m.showExpanded();
    this->scene->update();
    graphicsView->show();
}

void twoChessBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    // ui->label_2->clear();
    // ui->label_3->clear();


    int x = event->x();
    int y = event->y();

    ui->label->setText("Mouse pressed");

    //the following code is used to find which square is clicked.
    int square = 0;
    if((x>0 && x<480 ) && (y>140 && y<620))
    {
        int xaxis = (x/60) + 1;
        int yaxis = (y-140)/60;
        square = (yaxis*8)+xaxis;
        QString str= QString::number(square);
        ui->label_2->setText(str);

    }
    /*else if (x > 100)
    {
    ui->label_2->setText("X coordinate greater than 100");
    }
    else
    ui->label_2->setText("X coordinate less than 100");
*/

    if (y > 100)
    {
    ui->label_3->setText("Y coordinate greater than 100");
    }
    else
    ui->label_3->setText("Y coordinate less than 100");

    /*
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //QPixmap board ("EmptyBoard.png");

    QPen blackPen(Qt::black);
    QBrush yellowBrush(Qt::yellow);


    scene->addRect(-100,-100,50,50,blackPen,yellowBrush);
    */

    //scene = new QGraphicsScene(this);
    //QPixmap board("/Users/cuzoaru90/Desktop/EmptyBoard.png");

    //ui->graphicsView->setScene(scene);
   // board.load("/Users/cuzoaru90/chess/EmptyBoard.png");
    //scene->addPixmap(board);

}


void twoChessBoard::mouseReleaseEvent(QMouseEvent *)
{
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();

    ui->label->setText("Mouse Released");
}

void twoChessBoard::getGridCoordinates()
{
;

}


void twoChessBoard::on_pushButton_clicked()
{
    this->scene->update();
    graphicsView->show();
}
