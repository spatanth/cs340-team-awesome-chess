#ifndef TWOCHESSBOARD_H
#define TWOCHESSBOARD_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPixmap>
#include "pawn.h"
#include <QGraphicsRectItem>


namespace Ui {
    class twoChessBoard;
}

class twoChessBoard : public QDialog
{
    Q_OBJECT

public:
    explicit twoChessBoard(QWidget *parent = 0);
    ~twoChessBoard();

    const static int CHESSBOARD_SIZE = 8;
    const static int CHESSBOARD_GRID_SIZE = 60;

    int gridLoc[8][8];



private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void drawboard();

    void deletepieces();

private:

    Ui::twoChessBoard *ui;
    QWidget *parent;

    QPixmap *board;
    QGraphicsScene *scene;
    QGraphicsView *graphicsView;
    Pawn *pawnPiece;



    QVector<QGraphicsRectItem*>  chessboard[CHESSBOARD_SIZE];
    QVector<QGraphicsRectItem*> whitePawns;
    QVector<QGraphicsRectItem*> blackPawns;
    QVector<QGraphicsRectItem*> whiteRooks;
    QVector<QGraphicsRectItem*> blackRooks;
    QVector<QGraphicsRectItem*> whiteKnights;
    QVector<QGraphicsRectItem*> blackKnights;
    QVector<QGraphicsRectItem*> whiteBishops;
    QVector<QGraphicsRectItem*> blackBishops;

    QGraphicsRectItem *whiteQueen;
    QGraphicsRectItem *blackQueen;

    QGraphicsRectItem *whiteKing;
    QGraphicsRectItem *blackKing;


    int boardvalues[8][8];
    int selectx;
    int selecty;
    int select;
    int turn;
    int blackPawnsLeft;
    int whitePawnsLeft;
    int blackRooksLeft;
    int whiteRooksLeft;
    int blackKnightsLeft;
    int whiteKnightsLeft;
    int blackBishopsLeft;
    int whiteBishopsLeft;
    int blackQueenLeft;
    int whiteQueenLeft;
    int blackKingLeft;
    int whiteKingLeft;


    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    void getGridCoordinates(int x);


    bool isSquareEmpty();
};


#endif // TWOCHESSBOARD_H
