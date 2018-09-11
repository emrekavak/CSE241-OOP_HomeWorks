//This is the file connectfourabstract.h
//This is the interface for the class ConnnectFourAbstract
#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H
#include "cell.h"
#include<string>
using namespace std;

namespace ConnectFour{

    class ConnectFourAbstract
    {
    public:
        ConnectFourAbstract(); // default constructor creating 5x5 game with board 
        ConnectFourAbstract(int rowValue, int columnValue); 
        //Precondition : rowValue > 0 && columnValue > 0
        //PostCondition : will resize gameBoard according to parameter
        ConnectFourAbstract& operator=(const ConnectFourAbstract & righSide); // assignment operator
        ConnectFourAbstract(const ConnectFourAbstract& otherOb); // copy constructor
        //Precondition : after gameMode select, if mode == M, this function will call
        //PostCondition : 5 object will create and game will play in this function with another functions
        virtual int playGame() ; // if game mode S or s, this function will call
        virtual int play(const char columnChoice); // if player choice P, user selected column no will changed board in here
        virtual int play(); // if player choice C, this function will call and computer will play, board will change in here

        int resizeLoadedFile(); // after load a file, this function will created new 2d board according to row and column
        const int saveFile( const string fileName); 
        //Precondition : user will input SAVE OR SAVE FILENAME OR SAVE FILENAME.TXT
        //PostCondition : gameBoard row,column,userChoice and board will save in file
        const int loadFile( const string fileName);
        //Precondition : user will input LOAD FILENAME OR LOAD FILENAME.TXT
        //PostCondition : gameBoard row,column,userChoice and board cells will save in file
        const void displayGame()const; // for display gameBoard
        void resize(int width, int height);

        int getColumn()const{ return column;} // for return column
        int getRow()const{return row;} // for return row
        int getGameMode()const{ return gameMode;} // for return gameMode
        int getUserChoice()const{ return userChoice;} // for return userChoice

        void setColumn( int colValue){ if(colValue >=0 ) column = colValue;} // for set column
        void setRow(int rowValue){ if(rowValue>=0) row = rowValue;}  // for set row
        void setGameMode(char gmode){ gameMode =gmode;}// for set gameMode
        void setUserChoice(char uChoice){ if(uChoice =='P' ||uChoice =='p' 
                            ||uChoice =='S' ||uChoice =='s' ) userChoice =uChoice;}// for set userChoice

        int getcheckColumnFull(const char letter)const; 
        //Precondition : checking board full or not
        //Postcondition : if board full, return will 1 else return will 0
        int getcheckLetterCorrect(const char letter)const; // for check letter correct or not
        virtual int getcheckWinner(const int rowNum,const int columnNum,const int user) = 0; //pure virtual funciton
        //Precondition : after user's selected column, this function will call
        //Postcondition : if user win, return 1 and lover case game board will create in here
        int getCheckBoardFull()const; // for check column full or not. if full return will 1 else return 0

        ~ConnectFourAbstract(); // destructor 
    protected :

        Cell ** gameBoard; //2d Cell array
        int column; //column number for gameBoard
        int row;    //row number for gameBoard
        char userChoice; // can be P,p or C,c
        char gameMode;  // can be M,m or S,s
        int flag; //for user 1 and 2 flag  choice when board change X,O,C
        };
}
#endif

