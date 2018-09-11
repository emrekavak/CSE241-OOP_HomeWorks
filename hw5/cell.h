//This file is the file cell.h 
//This is the interface for the class Cell
//This class have "Has -a relation" with ConnectFourAbstract class
#ifndef CELL_H
#define CELL_H
#include<string>
namespace ConnectFour{
    class Cell{
        public:
                Cell(); // default constructor creates cell cellType = USER1, rowNumber =0 and position='a'
                Cell(int temp);  // for cell type assignment

                int getCellType()const; // for return cellType
                char getPositionCell()const; // for return position cells
                int getRowNumber()const; // for return row number

                void setCellType(const int type); //for set cellType
                void setPositionCell(const char position); //for set position cell
                void setRowNumber(const int rowValue); //for set Row number

        protected:     
                char positionCell; // a,b,c ...
                int rowNumber; // 0,1,2,3 ...
                int cellType; // can be  SPACE,EMPTY,USER1, USER2, COM, LOWUSER1, LOWUSER2, LOWCOM         
    };
}
#endif /* CELL_H */

