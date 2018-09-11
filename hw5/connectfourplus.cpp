//This is the implementation for the class ConnectFourPlus
//This is the file  connectfourplus.cpp
#include "connectfourplus.h"
#include<string>

typedef enum typeFormat{SPACE,EMPTY,USER1,USER2,COM, LOWUSER1, LOWUSER2, LOWCOM} TYPE; // for board change

namespace ConnectFour{
    
    ConnectFourPlus::ConnectFourPlus():ConnectFourAbstract(){ //default constructor
        //empty
    }
    /*-----------end of default Constructor----------*/
    ConnectFourPlus::ConnectFourPlus(int width, int height) //two parameter constructor
                                :ConnectFourAbstract(width,height){
        //empty
    }
    /*-----------end of two parameter constructor----------*/
    ConnectFourPlus::~ConnectFourPlus(){ //destructor
        for(int j = 0; j < row; j++)
                delete[]gameBoard[j];
        delete[]gameBoard;	
    }
    /*-----------end of destructor----------*/
    ConnectFourPlus::ConnectFourPlus(const ConnectFourPlus& otherOb){ //copy constructor
        row=otherOb.getRow(); //otherOb information loading
        column =otherOb.getColumn();
        gameMode = otherOb.getGameMode();
        userChoice = otherOb.getUserChoice();

        gameBoard = new Cell*[row];
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
    /*-----------end of copy constructor----------*/
    ConnectFourPlus& ConnectFourPlus::operator=(const ConnectFourPlus & righSide){

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
    /*-----------end of operator =----------*/
    int ConnectFourPlus::getcheckWinner(const int rowNum, const int columnNum, const int user){
        int count1 = 0, count2 = 0,count3 = 0, count4 = 0, count5 = 0;

        for(int i=0; i<4; i++){
            if( rowNum+i < row && gameBoard[rowNum+i][columnNum].getCellType() == user) count1++; 	// vertical count     
            if( columnNum-i >= 0 && gameBoard[rowNum][columnNum-i].getCellType() == user) count2++;	// horizontal count xxx-                     
            if( columnNum+i < column && gameBoard[rowNum][columnNum+i].getCellType() == user) count3++;	// horizontal count -xxx 
            if(columnNum+i-1 >= 0 && columnNum+i-1 < column && gameBoard[rowNum][columnNum+i-1].getCellType() == user) count4++; // horizontal count x-xx                      
            if(columnNum+i-2 >= 0 && columnNum+i-2 < column && gameBoard[rowNum][columnNum+i-2].getCellType() == user) count5++; // horizontal count xx-x   
        }

        int flagLower;
        if(count1 == 4 || count2 == 4 || count3 == 4 || count4 == 4 || count5 == 4){
            if(user == 2) flagLower = LOWUSER1; // lowercase
            if(user == 3) flagLower = LOWUSER2;
            if(user == 4) flagLower = LOWCOM;

        for(int k = 0; k <4; k++){    //board changing lowercase according to user
             if(count1 == 4) gameBoard[rowNum+k][columnNum].setCellType(flagLower);              
            if(count2 == 4 && count3 != 4 && count4 != 4 && count5 != 4) gameBoard[rowNum][columnNum-k].setCellType(flagLower);              
            if(count3 == 4 && count2 != 4 && count4 != 4 && count5 != 4) gameBoard[rowNum][columnNum+k].setCellType(flagLower);              
            if(count4 == 4 && count5 !=4 ) gameBoard[rowNum][columnNum+k-1].setCellType(flagLower); 
            if(count5 == 4) gameBoard[rowNum][columnNum+k-2].setCellType(flagLower);
        }
            return 1;
       }
        return 0;
    }
    /*-----------end of getcheckWinner----------*/
}
/*-----------end of name space----------*/



