//This is the implementation for the class ConnectFourDiag
//This is the file connectfourdiag.cpp
#include<iostream>
#include "connectfourdiag.h"
#include<string>

using namespace std;
typedef enum typeFormat{SPACE,EMPTY,USER1,USER2,COM, LOWUSER1, LOWUSER2, LOWCOM} TYPE; // for board 

namespace ConnectFour{
       
    ConnectFourDiag::ConnectFourDiag():ConnectFourAbstract(){ // default constructor with inheritance class
        //EMPTY
    }
    /* ---------- end of default constructor ---------- */
    ConnectFourDiag::ConnectFourDiag(int width, int height) // two parameter  constructor with inheritance class
                                :ConnectFourAbstract(width,height){
        //EMPTY
    }
    /* ---------- end of default two parameter constructor---------- */
    ConnectFourDiag::~ConnectFourDiag(){  // destructor
        for(int j = 0; j < row; j++)
                delete[]gameBoard[j];
        delete[]gameBoard;	
    }
    /* ---------- end of destructor ---------- */
    ConnectFourDiag::ConnectFourDiag(const ConnectFourDiag& otherOb){ // copy constructor
        row=otherOb.getRow(); //otherOb information loading
        column =otherOb.getColumn();
        gameMode = otherOb.getGameMode();
        userChoice = otherOb.getUserChoice();

        gameBoard = new Cell*[row]; // new board creating 
        for(int i = 0; i < row; i++ )
            gameBoard[i]= new Cell[column];

        for(int i=0; i<row; i++){
            for(int j =0; j<column; j++){
                gameBoard[i][j].setCellType(otherOb.gameBoard[i][j].getCellType());
                gameBoard[i][j].setRowNumber(otherOb.gameBoard[i][j].getRowNumber());
                gameBoard[i][j].setPositionCell(otherOb.gameBoard[i][j].getPositionCell());		
            }
        }
    }
    /* ---------- end of copy constructor ---------- */
    ConnectFourDiag& ConnectFourDiag::operator=(const ConnectFourDiag & righSide){
        if(row != righSide.getRow() && row != righSide.getColumn()){
            for(int i=0; i< row; i++)  //before board deleting
                    delete[]gameBoard[i];
            delete[]gameBoard;

            gameBoard = new Cell*[righSide.getRow()]; //new board create
            for(int i = 0; i < righSide.getRow(); i++ )
            gameBoard[i]= new Cell[righSide.getColumn()];
        }
        row=righSide.getRow(); //new board assignment
        column =righSide.getColumn();
        gameMode = righSide.getGameMode();
        userChoice = righSide.getUserChoice();	
        for(int i=0; i<row; i++){
            for(int j =0; j<column; j++){
                gameBoard[i][j].setCellType(righSide.gameBoard[i][j].getCellType());
                gameBoard[i][j].setRowNumber(righSide.gameBoard[i][j].getRowNumber());
                gameBoard[i][j].setPositionCell(righSide.gameBoard[i][j].getPositionCell());		
            }
       }
       return *this;	
    }
    /* ---------- end of operator=  ---------- */
    int ConnectFourDiag::getcheckWinner(const int rowNum, const int columnNum, const int user){
         int count6 = 0, count7 = 0, count8 = 0,count9 = 0, count10 = 0, count11=0,count12 =0, count13=0; // counts will count X or O according to selected row and column

         for(int j = 0; j<4; j++){                                                                                                    
            if(rowNum +j < row && columnNum-j >= 0 && gameBoard[rowNum+j][columnNum-j].getCellType() == user) count6++; // diagonal1 count -xxx
            if(rowNum -j >=0 && columnNum+j < row && gameBoard[rowNum-j][columnNum+j].getCellType() == user) count8++;  // diagonal1 count xxx-
            if(rowNum -j >=0 && columnNum-j >= 0 && gameBoard[rowNum-j][columnNum-j].getCellType() == user) count7++;    // diagonal2 count -xxx       
            if(rowNum+j < row && columnNum+j < column && gameBoard[rowNum+j][columnNum+j].getCellType() == user) count9++;// diagonal2 count xxx-     
        } 
        for(int m = 0; m<=4; m++){ 
            if(rowNum + m -1 < row && rowNum + m -1 >=0 && columnNum+m-1 >=0 && columnNum+m-1 < column && gameBoard[rowNum + m - 1][columnNum+m-1].getCellType() == user) 
                count10++; // diagonal2  count x-xxx   
            if(rowNum + m < row && rowNum + m -1 >=0 && columnNum-m+1 >=0 && columnNum-m-1 < column && gameBoard[rowNum + m - 1][columnNum-m+1].getCellType() == user) 
                count11++; // diagonal1 count x-xxx          
            if(rowNum + m -2 < row &&  rowNum + m -2 >=0 && columnNum+m-2 >=0 && columnNum+m-2 < column && gameBoard[rowNum + m - 2][columnNum+m-2].getCellType() == user) 
                count12++; // diagonal2 count xx-x                     
            if(rowNum + m -2 < row && rowNum + m -2 >=0 && columnNum-m +2 >= 0 && columnNum-m+2 < column && gameBoard[rowNum + m - 2][columnNum - m + 2].getCellType() == user) 
                count13++; // diagonal1 count xx-x      
        }

        int flagLower;
        if(count6 == 4 || count7 == 4 || count8 == 4 || count9 == 4 || count10 == 4 || count11 == 4 || count12 == 4 || count13 == 4){
            if(user == 2) flagLower = LOWUSER1; // lowercase
            if(user == 3) flagLower = LOWUSER2;
            if(user == 4) flagLower = LOWCOM;

        for(int k = 0; k <4; k++){   
            if(count6 == 4) gameBoard[rowNum+k][columnNum-k].setCellType(flagLower); // lower letter assigment             
            if(count7 == 4) gameBoard[rowNum-k][columnNum-k].setCellType(flagLower);             
            if(count8 == 4) gameBoard[rowNum-k][columnNum+k].setCellType(flagLower);            
            if(count9 == 4) gameBoard[rowNum+k][columnNum+k].setCellType(flagLower);          
            if(count10 == 4) gameBoard[rowNum + k - 1][columnNum+k-1].setCellType(flagLower);          
            if(count11 == 4) gameBoard[rowNum + k - 1][columnNum-k+1].setCellType(flagLower);           
            if(count12 == 4) gameBoard[rowNum + k - 2][columnNum+k-2].setCellType(flagLower);            
            if(count13 == 4 && count11 !=4){
                if(gameBoard[rowNum + k - 2][columnNum - k + 2].getCellType() ==user) 
                    gameBoard[rowNum + k - 2][columnNum - k + 2].setCellType(flagLower); 
            }    
       }
        return 1;
    }
        return 0;
    }
    /* ---------- end of getcheckWinner ---------- */
}
/* ---------- end of name space ---------- */