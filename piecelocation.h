#ifndef PIECELOCATION_H
#define PIECELOCATION_H
#include <string>

class pieceLocation
{

public:
    pieceLocation();
    pieceLocation(int row, int column);
    int getRowNumber();
    int getColumnNumber();
    bool equals(pieceLocation loc);
    //string toString();


};

#endif // PIECELOCATION_H
