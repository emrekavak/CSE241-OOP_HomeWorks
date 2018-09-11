//This is the implementation for the class Cell
//This is the file cell.cpp
#include "cell.h"
#include<string>

typedef enum typeFormat{SPACE,EMPTY,USER1,USER2,COM, LOWUSER1, LOWUSER2, LOWCOM} TYPE;

namespace ConnectFour{
    
    Cell::Cell(){ // default constructor
    cellType = USER1;
    rowNumber = 0;
    positionCell = 'a';
    }
    
    Cell::Cell(int type){ // for cell type assignment
        cellType = type;
    }
    
    int Cell::getCellType()const{ 
        return cellType;
    }
    
    char Cell::getPositionCell()const{ 
        return positionCell;
    }
    
    int Cell::getRowNumber()const { // for return row number
        return rowNumber;
    }   
    
    void Cell::setCellType(const int type){  //for set cellType
        if(type>=SPACE && type<=LOWCOM)cellType = type;
    } 
    
    void Cell::setPositionCell(const char position){   //for set position cell
        if(position>='a' && position<='z') positionCell = position;
    }
    
    void Cell::setRowNumber(const int rowValue){ //for set Row number
        if(rowValue >= 0) rowNumber = rowValue;
    } 
}

