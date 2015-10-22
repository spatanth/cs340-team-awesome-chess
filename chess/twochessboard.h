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
    const static int CHESSBOARD_GRID_SIZE =30;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::twoChessBoard *ui;

    QPixmap *board;
    QGraphicsScene *scene;
    QGraphicsView *graphicsView;
    Pawn *pawnPiece;
    typedef QVector<QGraphicsRectItem*> QSubContainer;
    QVector<QGraphicsRectItem*>   chessboard[CHESSBOARD_SIZE];
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    void getGridCoordinates();
};




#endif // TWOCHESSBOARD_H
