#include "twochessboard.h"
#include "ui_twochessboard.h"
#include "mainwindow.h"

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPixmap>
#include <stdio.h>
#include <math.h>

twoChessBoard::twoChessBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::twoChessBoard)
{

	// There are issues with this right now. Hardcoded integers are only used for testing on simulator, not actual phone.
    this->parent = parent;
    ui->setupUi(this);
    ui->widget->setGeometry(QRect(10,130,480,480));
    graphicsView = new QGraphicsView(ui->widget);
    scene = new QGraphicsScene(QRect(-240,-180,480,480));
    graphicsView->setGeometry(QRect(0,0,490,490));
    graphicsView->setScene(scene);
    select = 0;//used to check whether a piece is selected or not
    turn = 1;//used to check which players turn it is
    //the following are to check how many different kind of pieces are left in the board
    blackPawnsLeft = 8;
    whitePawnsLeft = 8;
    blackRooksLeft = 2;
    whiteRooksLeft = 2;
    blackKnightsLeft = 2;
    whiteKnightsLeft = 2;
    blackBishopsLeft = 2;
    whiteBishopsLeft = 2;
    blackQueenLeft = 1;
    whiteQueenLeft = 1;
    blackKingLeft = 1;
    whiteKingLeft = 1;

    // colors for pieces
    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::white);
    QBrush greenBrush(Qt::green);
    QBrush redBrush(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QBrush blueBrush(Qt::blue);
    QBrush magentaBrush(Qt::magenta);
    QBrush grayBrush(Qt::gray);

    QBrush darkGreenBrush(Qt::darkGreen);
    QBrush darkRedBrush(Qt::darkRed);
    QBrush darkYellowBrush(Qt::darkYellow);
    QBrush darkBlueBrush(Qt::darkBlue);
    QBrush darkMagentaBrush(Qt::darkMagenta);
    QBrush darkGrayBrush(Qt::darkGray);

    QPen pen(Qt::transparent);
    pen.setWidth(0);


    // This loop generates the chessboard. Code was written by TA.
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
    qDebug("Initialized chessboard...");


    for(int i =0; i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            boardvalues[i][j] = 0;
        }
    }


    //initialising the board values
    for(int i = 0;i<8;i++)
    {
        //pawns
        boardvalues[1][i] = 1;
        boardvalues[6][i] = 7;
    }

    //rooks
    boardvalues[0][0] = 2;
    boardvalues[0][7] = 2;
    boardvalues[7][0] = 8;
    boardvalues[7][7] = 8;

    //knights
    boardvalues[0][1] = 3;
    boardvalues[0][6] = 3;
    boardvalues[7][1] =9;
    boardvalues[7][6] =9;

    //bishops
    boardvalues[0][2] = 4;
    boardvalues[0][5] = 4;
    boardvalues[7][2] =10;
    boardvalues[7][5] =10;

    //queen
    boardvalues[0][3] = 6;
    boardvalues[7][3] =12;

    //king
    boardvalues[0][4] = 5;
    boardvalues[7][4] =11;

    // white pawns
    for (int i = 0; i < 8; i++)
    {
        whitePawns.resize(8);
        whitePawns[i] = new QGraphicsRectItem(-225+60*i, -105, 30, 30 );
        whitePawns[i]->setBrush(greenBrush);
        scene->addItem(whitePawns[i]);
    }
    //black pawns
    for (int i = 0; i < 8; i++)
    {
        blackPawns.resize(8);
        blackPawns[i] = new QGraphicsRectItem(-225+60*i, 195, 30, 30 );
        blackPawns[i]->setBrush(darkGreenBrush);
        scene->addItem(blackPawns[i]);
    }

    // white and black pieces
    for (int i = 0; i < 2; i++)
    {
        whiteRooks.resize(2);
        whiteRooks[i] = new QGraphicsRectItem(-225+420*i,-165,30,30);
        whiteRooks[i]->setBrush(redBrush);
        scene->addItem(whiteRooks[i]);

        blackRooks.resize(2);
        blackRooks[i] = new QGraphicsRectItem(-225+420*i,255,30,30);
        blackRooks[i]->setBrush(darkRedBrush);
        scene->addItem(blackRooks[i]);

        whiteKnights.resize(2);
        whiteKnights[i] = new QGraphicsRectItem(-165+300*i,-165,30,30);
        whiteKnights[i]->setBrush(yellowBrush);
        scene->addItem(whiteKnights[i]);

        blackKnights.resize(2);
        blackKnights[i] = new QGraphicsRectItem(-165+300*i,255,30,30);
        blackKnights[i]->setBrush(darkYellowBrush);
        scene->addItem(blackKnights[i]);

        whiteBishops.resize(2);
        whiteBishops[i] = new QGraphicsRectItem(-105+180*i,-165,30,30);
        whiteBishops[i]->setBrush(blueBrush);
        scene->addItem(whiteBishops[i]);

        blackBishops.resize(2);
        blackBishops[i] = new QGraphicsRectItem(-105+180*i,255,30,30);
        blackBishops[i]->setBrush(darkBlueBrush);
        scene->addItem(blackBishops[i]);
    }


    whiteQueen = new QGraphicsRectItem(-45,-165,30,30);
    whiteQueen->setBrush(magentaBrush);
    scene->addItem(whiteQueen);

    blackQueen = new QGraphicsRectItem(-45,255,30,30);
    blackQueen->setBrush(darkMagentaBrush);
    scene->addItem(blackQueen);

    whiteKing = new QGraphicsRectItem(15,-165,30,30);
    whiteKing->setBrush(grayBrush);
    scene->addItem(whiteKing);

    blackKing = new QGraphicsRectItem(15,255,30,30);
    blackKing->setBrush(darkGrayBrush);
    scene->addItem(blackKing);

}

twoChessBoard::~twoChessBoard() //deletes chessboard and pieces;
{
    qDebug("Free chessboard...");
    for(int i=0;i<CHESSBOARD_SIZE;i++){
        for(int j = 0 ; j<CHESSBOARD_SIZE;j++){
            delete chessboard[i][j];
        }

    }

    for (int i = 0; i < 8; i++)
    {
        delete whitePawns[i];
        delete blackPawns[i];
    }

    for (int i = 0; i < 2; i++)
    {
        delete whiteRooks[i];
        delete blackRooks[i];
        delete whiteKnights[i];
        delete blackKnights[i];

    }
    delete scene;
    delete ui;
}

void twoChessBoard::on_pushButton_2_clicked()
{
    //MainWindow m;
    //m.showExpanded();
    this->parent->showFullScreen();
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
    if((x>10 && x<490 ) && (y>130 && y<610))
    {
        int xaxis = ( (x-10)/60 );
        int yaxis = (y-130)/60;
        square = (yaxis*8)+xaxis;
        QString str2= QString::number(yaxis);
        ui->label_3->setText(str2);



        if(select==0)//enters this if statement if no piece is selected
                {
                    selectx = xaxis;
                    selecty = yaxis;
                    if(turn==1)//used to make sure that the player selects only his/her pieces
                    {
                        if(boardvalues[selecty][selectx]>0&&boardvalues[selecty][selectx]<=6)
                        {
                            select = 1;
                        }
                    }
                    if(turn==2)
                    {
                        if(boardvalues[selecty][selectx]>6&&boardvalues[selecty][selectx]<=12)
                        {
                            select = 1;
                        }
                    }


                }
                else
                {
                    //enters this if a piece is already selected
                    int changedvalue = 16;//used to store the values that has been eliminated, I used the intial value as 16 because no pieces has this as their boardvalue

                    if((boardvalues[yaxis][xaxis]>=7 && boardvalues[yaxis][xaxis]<=12)||boardvalues[yaxis][xaxis]==0)//this if statement is to make sure that the player doesnot eliminate his/her own pieces
                    {
                    if(boardvalues[selecty][selectx]==1)
                    {//if the selected pieces is black pawn
                        if((yaxis==selecty+1)&&(selectx==xaxis))
                        {//to check that the new position is one step down in the board
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 2;//changes the turn

                        }
                        if(((yaxis==selecty+1)&&(selectx==xaxis+1))||((yaxis==selecty+1)&&(selectx==xaxis-1)))
                        {
                            if(boardvalues[yaxis][xaxis]>=7 && boardvalues[yaxis][xaxis]<=12)
                            {
                                changedvalue = boardvalues[yaxis][xaxis];
                                boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                                select = 0;
                                boardvalues[selecty][selectx] = 0;
                                turn = 2;

                            }
                        }
                    }
                    //the following code is similar but for other pieces rules
                    if(boardvalues[selecty][selectx]==2)
                    {

                        if((yaxis==selecty)||(xaxis==selectx))
                        {
                                    changedvalue = boardvalues[yaxis][xaxis];
                                    boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                                    select = 0;
                                    boardvalues[selecty][selectx] = 0;
                                    turn = 2;

                         }

                    }
                    if(boardvalues[selecty][selectx]==3)
                    {
                        int xchange = fabs(selectx-xaxis);
                        int ychange = fabs(selecty-yaxis);
                        int totalchange = xchange+ychange;
                        if((totalchange==3))
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 2;

                        }
                    }
                    if(boardvalues[selecty][selectx]==4)
                    {
                        int xchange = fabs(selectx-xaxis);
                        int ychange = fabs(selecty-yaxis);
                        if(xchange==ychange)
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 2;

                        }


                    }
                    if(boardvalues[selecty][selectx]==5)
                    {
                        int xchange = fabs(selectx-xaxis);
                        int ychange = fabs(selecty-yaxis);
                        if(xchange==1 && ychange==1)
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 2;

                        }
                        if(((yaxis==selecty+1)&&(selectx==xaxis))||((yaxis==selecty-1)&&(selectx==xaxis)))
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 2;

                        }
                        if(((yaxis==selecty)&&(selectx==xaxis+1))||((yaxis==selecty)&&(selectx==xaxis-1)))
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 2;

                        }


                    }
                    if(boardvalues[selecty][selectx]==6)
                    {
                        int xchange = fabs(selectx-xaxis);
                        int ychange = fabs(selecty-yaxis);
                        if(xchange==ychange)
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 2;

                        }
                        if((yaxis==selecty)||(xaxis==selectx))
                        {
                                    changedvalue = boardvalues[yaxis][xaxis];
                                    boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                                    select = 0;
                                    boardvalues[selecty][selectx] = 0;
                                    turn = 2;

                         }

                    }
                    }
                    if((boardvalues[yaxis][xaxis]>=0 && boardvalues[yaxis][xaxis]<=6))
                    {
                    if(boardvalues[selecty][selectx]==7)
                    {
                        if((yaxis==selecty+-1)&&(selectx==xaxis))
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 1;

                        }
                        if(((yaxis==selecty-1)&&(selectx==xaxis+1))||((yaxis==selecty-1)&&(selectx==xaxis-1)))
                        {
                            if(boardvalues[yaxis][xaxis]>=1 && boardvalues[yaxis][xaxis]<=6)
                            {
                                changedvalue = boardvalues[yaxis][xaxis];
                                boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                                select = 0;
                                boardvalues[selecty][selectx] = 0;
                                turn = 2;

                            }
                        }
                    }
                    if(boardvalues[selecty][selectx]==8)
                    {

                        if((yaxis==selecty)||(xaxis==selectx))
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                                    boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                                    select = 0;
                                    boardvalues[selecty][selectx] = 0;
                                    turn = 1;

                         }

                    }
                    if(boardvalues[selecty][selectx]==9)
                    {
                        int xchange = fabs(selectx-xaxis);
                        int ychange = fabs(selecty-yaxis);
                        int totalchange = xchange+ychange;
                        if((totalchange==3))
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 1;

                        }
                    }
                    if(boardvalues[selecty][selectx]==10)
                    {
                        int xchange = fabs(selectx-xaxis);
                        int ychange = fabs(selecty-yaxis);
                        if(xchange==ychange)
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 1;

                        }


                    }
                    if(boardvalues[selecty][selectx]==11)
                    {
                        int xchange = fabs(selectx-xaxis);
                        int ychange = fabs(selecty-yaxis);
                        if(xchange==1 && ychange==1)
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 1;

                        }
                        if(((yaxis==selecty+1)&&(selectx==xaxis))||((yaxis==selecty-1)&&(selectx==xaxis)))
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 1;

                        }
                        if(((yaxis==selecty)&&(selectx==xaxis+1))||((yaxis==selecty)&&(selectx==xaxis-1)))
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 1;

                        }



                    }
                    if(boardvalues[selecty][selectx]==12)
                    {
                        int xchange = fabs(selectx-xaxis);
                        int ychange = fabs(selecty-yaxis);
                        if(xchange==ychange)
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                            boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                            select = 0;
                            boardvalues[selecty][selectx] = 0;
                            turn = 1;

                        }
                        if((yaxis==selecty)||(xaxis==selectx))
                        {
                            changedvalue = boardvalues[yaxis][xaxis];
                                    boardvalues[yaxis][xaxis] = boardvalues[selecty][selectx];
                                    select = 0;
                                    boardvalues[selecty][selectx] = 0;
                                    turn = 1;

                         }
                    }
                    }
                    if(changedvalue==0)
                    {
                        deletepieces();
                        drawboard();
                    }
                    //the following code is used to delete the piece that has been elimiated
                    if(changedvalue==1)
                    {
                        delete blackPawns[blackPawnsLeft-1];
                        blackPawnsLeft = blackPawnsLeft-1;
                        deletepieces();//this method is to delete all the remaining pieces on the board. I am deleteing all because if not when we change the color of the pieces to highlight the  turn there are copies of pieces with the old colors
                        drawboard();// to place all the pieces in their new locations
                    }
                    else if(changedvalue==2)
                    {
                        delete blackRooks[blackRooksLeft-1];
                        blackRooksLeft = blackRooksLeft-1;
                        deletepieces();
                        drawboard();
                    }
                    else if(changedvalue==3)
                    {
                        delete blackKnights[blackKnightsLeft-1];
                        blackKnightsLeft = blackKnightsLeft-1;
                        deletepieces();
                        drawboard();
                    }
                    else if(changedvalue==4)
                    {
                        delete blackBishops[blackBishopsLeft-1];
                        blackBishopsLeft = blackBishopsLeft-1;
                        deletepieces();
                        drawboard();
                    }
                    else if(changedvalue==5)
                    {
                        delete blackKing;
                        blackKingLeft =  0;
                        deletepieces();
                        drawboard();
                    }
                    else if(changedvalue==6)
                    {
                        delete blackQueen;
                        blackQueenLeft = 0;
                        deletepieces();
                        drawboard();

                    }
                    else if(changedvalue==7)
                    {
                        delete whitePawns[whitePawnsLeft-1];
                        whitePawnsLeft = whitePawnsLeft-1;
                        deletepieces();
                        drawboard();

                    }
                    else if(changedvalue==8)
                    {
                        delete whiteRooks[whiteRooksLeft-1];
                       whiteRooksLeft = whiteRooksLeft-1;
                       deletepieces();
                       drawboard();

                    }
                    else if(changedvalue==9)
                    {
                        delete whiteKnights[whiteKnightsLeft-1];
                        whiteKnightsLeft = whiteKnightsLeft-1;
                        deletepieces();
                        drawboard();
                    }
                    else if(changedvalue==10)
                    {
                        delete whiteBishops[whiteBishopsLeft-1];
                        whiteBishopsLeft = whiteBishopsLeft-1;
                        deletepieces();
                        drawboard();
                    }
                    else if(changedvalue==11)
                    {
                     delete whiteKing;
                     whiteKingLeft = 0;
                     deletepieces();
                     drawboard();
                    }
                    else if(changedvalue==12)
                    {
                        delete whiteQueen;
                        whiteQueenLeft = 0;
                        deletepieces();
                        drawboard();
                    }
                    select = 0;
                }

            }
}
}


void twoChessBoard::mouseReleaseEvent(QMouseEvent *)
{
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();

    ui->label->setText("Mouse Released");
}

void twoChessBoard::getGridCoordinates(int x)
{
;

}


void twoChessBoard::on_pushButton_clicked()
{
    this->scene->update();
    graphicsView->show();
}

void twoChessBoard::drawboard()
{
    QBrush greenBrush(Qt::green);
    QBrush redBrush(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QBrush blueBrush(Qt::blue);
    QBrush magentaBrush(Qt::magenta);
    QBrush grayBrush(Qt::gray);
   QBrush darkGreenBrush(Qt::darkGreen);
    QBrush darkRedBrush(Qt::darkRed);
    QBrush darkYellowBrush(Qt::darkYellow);
    QBrush darkBlueBrush(Qt::darkBlue);
    QBrush darkMagentaBrush(Qt::darkMagenta);
    QBrush darkGrayBrush(Qt::darkGray);
    int blackpawnsno = 0;
    int blackknightsno = 0;
    int blackrooksno = 0;
    int blackbhisopsno = 0;
    int whitepawnsno = 0;
    int whiteknightsno = 0;
    int whiterooksno = 0;
    int whitebhisopsno = 0;

    //places the pieces in their new locations
    for(int i = 0; i<8;i++)
    {
        for(int j = 0; j<8; j++)
        {
            if(boardvalues[i][j]==1)
            {
                blackPawns.resize(8);
                blackPawns[blackpawnsno] = new QGraphicsRectItem(-220+60*j, -160 +i*60, 30, 30 );
                if(turn==2)
                {
                    blackPawns[blackpawnsno]->setBrush(darkGreenBrush);
                }
                if(turn==1)
                {
                   blackPawns[blackpawnsno]->setBrush(greenBrush);
                }
                scene->addItem(blackPawns[blackpawnsno]);
                blackpawnsno = blackpawnsno+1;
            }
            if(boardvalues[i][j]==2)
            {
                blackRooks.resize(2);
                blackRooks[blackrooksno] = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    blackRooks[blackrooksno]->setBrush(darkRedBrush);
                }
                if(turn==1)
                {
                    blackRooks[blackrooksno]->setBrush(redBrush);
                }
                scene->addItem(blackRooks[blackrooksno]);
                blackrooksno = blackrooksno+1;

            }
            if(boardvalues[i][j]==3)
            {
                blackKnights.resize(2);
                blackKnights[blackknightsno] = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    blackKnights[blackknightsno]->setBrush(darkYellowBrush);
                }
                if(turn==1)
                {
                     blackKnights[blackknightsno]->setBrush(yellowBrush);
                }
                scene->addItem(blackKnights[blackknightsno]);
                blackknightsno = blackknightsno+1;

            }
            if(boardvalues[i][j]==4)
            {
                blackBishops.resize(2);
                blackBishops[blackbhisopsno] = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    blackBishops[blackbhisopsno]->setBrush(darkBlueBrush);
                }
                if(turn==1)
                {
                    blackBishops[blackbhisopsno]->setBrush(blueBrush);
                }
                scene->addItem(blackBishops[blackbhisopsno]);
                blackbhisopsno = blackbhisopsno+1;

            }
            if(boardvalues[i][j]==5)
            {
                blackKing = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    blackKing->setBrush(darkGrayBrush);
                }
                if(turn==1)
                {
                    blackKing->setBrush(grayBrush);
                }

                scene->addItem(blackKing);
            }
            if(boardvalues[i][j]==6)
            {

                blackQueen = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    blackQueen->setBrush(darkMagentaBrush);
                }
                if(turn==1)
                {
                    blackQueen->setBrush(magentaBrush);
                }
                scene->addItem(blackQueen);

            }
            if(boardvalues[i][j]==7)
            {
                whitePawns.resize(8);
                whitePawns[whitepawnsno] = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    whitePawns[whitepawnsno]->setBrush(greenBrush);
                }
                if(turn==1)
                {
                    whitePawns[whitepawnsno]->setBrush(darkGreenBrush);
                }
                scene->addItem(whitePawns[whitepawnsno]);
                whitepawnsno = whitepawnsno+1;
            }
            if(boardvalues[i][j]==8)
            {
                whiteRooks.resize(2);
                whiteRooks[whiterooksno] = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    whiteRooks[whiterooksno]->setBrush(redBrush);
                }
                if(turn==1)
                {
                    whiteRooks[whiterooksno]->setBrush(darkRedBrush);
                }
                scene->addItem(whiteRooks[whiterooksno]);
                whiterooksno = whiterooksno+1;

            }
            if(boardvalues[i][j]==9)
            {
                whiteKnights.resize(2);
                whiteKnights[whiteknightsno] = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    whiteKnights[whiteknightsno]->setBrush(yellowBrush);
                }
                if(turn==1)
                {
                    whiteKnights[whiteknightsno]->setBrush(darkYellowBrush);
                }
                scene->addItem(whiteKnights[whiteknightsno]);
                whiteknightsno = whiteknightsno+1;
            }
            if(boardvalues[i][j]==10)
            {
                whiteBishops.resize(2);
                whiteBishops[whitebhisopsno] = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    whiteBishops[whitebhisopsno]->setBrush(blueBrush);
                }
                if(turn==1)
                {
                    whiteBishops[whitebhisopsno]->setBrush(darkBlueBrush);
                }
                scene->addItem(whiteBishops[whitebhisopsno]);
                whitebhisopsno = whitebhisopsno+1;
            }
            if(boardvalues[i][j]==11)
            {
                whiteKing = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    whiteKing->setBrush(grayBrush);
                }
                if(turn==1)
                {
                    whiteKing->setBrush(darkGrayBrush);
                }
                scene->addItem(whiteKing);
            }
            if(boardvalues[i][j]==12)
            {
                whiteQueen = new QGraphicsRectItem(-220+60*j, -160 +i*60,30,30);
                if(turn==2)
                {
                    whiteQueen->setBrush(magentaBrush);
                }
                if(turn==1)
                {
                    whiteQueen->setBrush(darkMagentaBrush);
                }
                scene->addItem(whiteQueen);
            }
        }

    }
}

void twoChessBoard::deletepieces()
{

    for (int i = 0; i < blackPawnsLeft; i++)
    {
        delete blackPawns[i];
    }
    for (int i = 0; i < whitePawnsLeft; i++)
    {
        delete whitePawns[i];
    }
    for (int i = 0; i < blackRooksLeft; i++)
    {
        delete blackRooks[i];
    }
    for (int i = 0; i < whiteRooksLeft; i++)
    {
        delete whiteRooks[i];
    }
    for (int i = 0; i < blackKnightsLeft; i++)
    {
        delete blackKnights[i];
    }
    for (int i = 0; i < whiteKnightsLeft; i++)
    {
        delete whiteKnights[i];
    }
    for (int i = 0; i < blackBishopsLeft; i++)
    {
        delete blackBishops[i];
    }
    for (int i = 0; i < whiteBishopsLeft; i++)
    {
        delete whiteBishops[i];
    }

    if(blackQueenLeft==1)
    {
        delete blackQueen;
    }
    if(whiteQueenLeft==1)
    {
        delete whiteQueen;
    }
    if(blackKingLeft==1)
    {
        delete blackKing;
    }
    if(whiteKingLeft==1)
    {
        delete whiteKing;
    }
}

