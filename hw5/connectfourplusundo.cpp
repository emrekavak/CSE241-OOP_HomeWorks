//This is the implementation for the class ConnectFourPlusUndo
//This is the file connectfourplusundo.cpp
#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<vector>
#include "connectfourplusundo.h"

using namespace std;

typedef enum typeFormat{SPACE,EMPTY,USER1,USER2,COM, LOWUSER1, LOWUSER2, LOWCOM} TYPE;

namespace ConnectFour{
    
    ConnectFourPlusUndo::ConnectFourPlusUndo():ConnectFourPlus(){ // base class default constructor creating
        //EMPTY
    }
     /*-----------end of default Constructor----------*/
    ConnectFourPlusUndo::ConnectFourPlusUndo(int width, int height)
                                :ConnectFourPlus(width,height){
        //EMPTY
    }
    /*-----------end of two parameter constructor----------*/
    ConnectFourPlusUndo::~ConnectFourPlusUndo(){
        for(int j = 0; j < row; j++)
                delete[]gameBoard[j];
        delete[]gameBoard;	
    }
    /*-----------end of destructor----------*/
    ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo& otherOb){
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
    ConnectFourPlusUndo& ConnectFourPlusUndo::operator=(const ConnectFourPlusUndo & righSide){

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
    void ConnectFourPlusUndo::setVec(){ // after load file, vector will delete and resize
        saved.clear();
        saved.resize(column);
    }
    /*-----------end of setVec ----------*/
    int ConnectFourPlusUndo::setBoard(){
        char del = saved.back();  // the last user entered column is assigment to del from vector saved

        for(int i = row-1; i >=0; i--){   // board is scanning to find del's letter value
            for(int j = 0; j < column; j++){
                if(gameBoard[i][j].getPositionCell() == del){  // if value is find
                    if(gameBoard[i][j].getCellType() == USER1 || gameBoard[i][j].getCellType() == USER2 
                            || gameBoard[i][j].getCellType() == COM ){ // and the cell is not empty
                        if(gameBoard[i-1][j].getCellType() == EMPTY){ // and the cell's -1 row num is empty
                            gameBoard[i][j].setCellType(EMPTY);  // cell will change to empty
                            saved.pop_back();  // vector's the last element delete
                            displayGame();
                            i=0;
                            j=column;
                            return 1;
                        }
                    }
                }
            }
        }
        return 0;
    }
    /*-----------end of setBoard ----------*/
    const int ConnectFourPlusUndo:: saveFile( const string fileName){
        ofstream fileWrite;
        fileWrite.open(fileName.c_str(), ios::out); //saved file according to fileName
        if(!fileWrite){
            cerr<<endl<<"Error save file!!!"; //checking file open or not.if not, return will be -1
            return -1;
        }
        // game information writing to file
        fileWrite<<flag<<endl; // for which user next
        fileWrite<<gameMode<<endl;  
        fileWrite<<row<<endl;   
        fileWrite<<column<<endl;    
        fileWrite<<userChoice<<endl;

        for(int i = 0; i < row; i++){ 
            for(int j = 0; j<column; j++){
                if(gameBoard[i][j].getCellType() == SPACE) fileWrite<<' '; //cell information writing
                if(gameBoard[i][j].getCellType()== EMPTY) fileWrite<<'*';
                if(gameBoard[i][j].getCellType() == USER1) fileWrite<<'X';
                if(gameBoard[i][j].getCellType() == USER2) fileWrite<<'O';
                if(gameBoard[i][j].getCellType()== COM) fileWrite<<'C';
            }
            fileWrite<<"\n";
        }
        fileWrite.close();
        return 0; 
    }
    /*-----------end of saveFile ----------*/
    const int ConnectFourPlusUndo::loadFile( const string fileName){
         string boardload;
        ifstream fileload(fileName.c_str(),ios::in); // according to user entered file name, file will open
        if(!fileload){
            cerr<<endl<<"Error open file !!!"<<endl; // checking file opening
            return -1; 
        }else{

        for(int j = 0; j < row; j++)
                delete[]gameBoard[j];
            delete[]gameBoard;// before board clearing   
            
        getline(fileload,boardload); // first, board height reading in first line.
        flag =atoi(boardload.c_str());
        getline(fileload,boardload); // game informations getting to file and game values changing
        gameMode =boardload[0];
        getline(fileload,boardload);
        row =atoi(boardload.c_str()); // convert string to integer
        getline(fileload, boardload);
        column = atoi(boardload.c_str());
        getline(fileload, boardload);
        userChoice = boardload[0];
        resizeLoadedFile();  // game resizing according to row and column number in file
        int m=0,letternum;

            while(fileload)
            {   
                letternum = 97;
                getline(fileload,boardload);
                for(int k=0; k <column;k++,letternum++){ 
                    if(m<row){
                    gameBoard[m][k].setPositionCell(letternum);
                    if(boardload[k]== 'X' || boardload[k]== 'O' || boardload[k]== 'C'  ) saved.push_back(letternum);
                    gameBoard[m][k].setRowNumber(m);
                    if(boardload[k]==' ') gameBoard[m][k].setCellType(SPACE); //cell information changing
                    if(boardload[k]== '*') gameBoard[m][k].setCellType(EMPTY);
                    if(boardload[k]== 'X') gameBoard[m][k].setCellType(USER1); 
                    if(boardload[k]== 'O') gameBoard[m][k].setCellType(USER2); 
                    if(boardload[k]== 'C') gameBoard[m][k].setCellType(COM); 
                    }
                }
               if(fileload) m++;

            } // while end
        } // else end
        fileload.close();
        return 0;
    }
    /*-----------end of loadFile ----------*/
    int ConnectFourPlusUndo::play(){ //  computer play

        char letters[30];
        char move;    //arr array will keep letter according to entered size. move is keeping computer select letter
        int letterNum = 97,count =0;

        for(int i = 0; i < column ; i++){  
            letters[i] = letterNum; // letters according to entered size
            letterNum++;
            count++;
        }
        int count1 =0,count2=0,count3=0,count4=0,col=0; //counts will count how many X there are
                                                        //if they entered consecutive 3 times vertical or horizontal
        move =letters[rand()%count];  // a random letter will select  in array;
        for(int i =row-1; i >= 0; i--){ // horizontal smart move select
            for(int j =0 ; j<column; j++){
                if(gameBoard[i][j].getCellType() == USER1){
                    for(int k = 0; k < 4; k++){
                        if(gameBoard[i][j+k].getCellType() == USER1 && j+k < column ){ 
                        count1++;  
                        }
                        if(count1 ==3){
                        count2 = count1;
                        if(gameBoard[i][j+k+1].getCellType() == EMPTY && j+k+1 < column ) col = j+k;
                        //column will keep column number if there are 3 times 'X' horizontal
                        }   
                    }
                count1=0;
                }
            }
        }
        if(count2 == 3) move = (char)(col+97);
        
        for(int i =row-1; i >= 0; i--){  // vertical smart move select
            for(int j =row-1 ; j >= 0; j--){
                if(gameBoard[j][i].getCellType() == USER1){
                    for(int k = 0; k < 3; k++){
                        if(j-k >=0 && gameBoard[j-k][i].getCellType() ==USER1 ) count3++;  
                        if(count3 ==3 ){
                            count4 = count3;
                                if(gameBoard[j-k-1][i].getCellType() == EMPTY && j-k-1 >=0 && i-1>=0 )col = i; 
                        }       //column will keep column number if there are 3 times 'X' vertical
                    }
                    count3=0;
                }
            }
        }
        if(count4 == 3) move=(char)col+97; // if there are 3 times 'X' vertical, computer letter will be according to column number +97

        if(getcheckColumnFull(move) == 1){ // if selected column is full, move will change until find a '.';
            for(int i =0; i<row; i++){ 
                for(int j =0 ; j<column; j++){
                    if(gameBoard[i][j].getCellType() == EMPTY){ 
                        move =(char) j+97;
                    }
                }
            }
        }

        int minesRow = 0,rowVal,columnval;;
        cout<<"Computer(C) Played :"<<move<<endl;
        // according to  computer's letter, game BOARD changing
        for(int i = row-1; i >= 0; i--){
            for(int j = 0; j < column; j++){
                if(gameBoard[i][j].getPositionCell() == move && gameBoard[i][j].getCellType() ==EMPTY){
                    rowVal = gameBoard[i][j].getRowNumber();
                    columnval =j;
                    gameBoard[rowVal][j].setCellType(COM);
                    saved.push_back(move);   // computer choice saving to vector saved
                    displayGame();
                    i=0;
                    j=column;
                }
            }
        }
        if(getcheckWinner(rowVal,columnval,COM)==1){  // checking computer won or not 
                    cout<<"!!!!! Computer Wİnner !!!!!"<<endl;
                    displayGame();
                    exit(1);
        }
        if(getCheckBoardFull()==1){ // checking board full  or empty 
            cout<<"!!!!! No a winner. Board is full !!!!! "<<endl;
            displayGame();
            exit(1);
        }
        return 0;
    }
     /*-----------end of play----------*/
    int ConnectFourPlusUndo::play(const char columnChoice){
            int rowVal,columnval;

            for(int i = row-1; i >=0; i--){
                for(int j = 0; j < column; j++){
                    if(gameBoard[i][j].getPositionCell() == columnChoice && gameBoard[i][j].getCellType() == EMPTY ){
                    rowVal = gameBoard[i][j].getRowNumber();
                    columnval =j;
                    if(flag == 1) gameBoard[rowVal][columnval].setCellType(USER1);
                    if(flag == 2) gameBoard[rowVal][columnval].setCellType(USER2);
                    displayGame();
                    saved.push_back(columnChoice); // user entered letter saving to vector saved
                    i=0;
                    j=column;
                    }
                }
            }
            if(flag==1){ //player 1
                if(getcheckWinner(rowVal,columnval,USER1)==1){  // checking p1 won or not 
                    cout<<"!!!!! Congratulations  Player1 (X). You have won !!!!! "<<endl;
                    displayGame();
                    return 1;
                }
                if(getCheckBoardFull()==1){ // checking board full  or empty 
                    cout<<"!!!!! No a winner. Board is full !!!!! "<<endl;
                    displayGame();
                    return 1;
                }
            }
            if(flag==2){ //player 2
                if(getcheckWinner(rowVal,columnval,USER2)==1){  // checking p1 won or not 
                    cout<<"!!!!! Congratulations  Player2 (O). You have won !!!!! "<<endl;
                    displayGame();
                    return 1;   
                }

                if(getCheckBoardFull()==1){ // checking board full  or empty 
                    cout<<"!!!!! No a winner. Board is full !!!!! "<<endl;
                    displayGame();
                    return 1;
                }        
            }
            return 0;
    }
    /*-----------end of play----------*/
    int ConnectFourPlusUndo::playGame(){
        int modeFlag=0;
        string mode;
        cout<<endl;
        int numOfWith;

        do{
            cout<<"Please enter With :"; // get width value
            cin>>numOfWith;
            if(cin.fail()){
                cerr<<"invalid size"<<endl;
                cin.clear();
                cin.ignore();
                cout<<"Please enter With :";
                cin>>numOfWith;
            }
        }while(cin.fail());

        int numOfHeight; 
        do{
            cout<<"Please enter Height :"; // get height value
            cin>>numOfHeight;
            if(cin.fail()){
                cerr<<"invalid size"<<endl;
                cin.clear();
                cin.ignore();
                cout<<"Please enter height :";
                cin>>numOfHeight;
            }
        }while(cin.fail());
        cin.ignore();
        resize(numOfWith,numOfHeight); // resize function is calling
        
        string selectedPlayer;
        int letterflag=0;
        do{
            cout<<"Please enter play versus Player(P) or Computer(C)  :"; //get player choice
            getline(cin,selectedPlayer);
            if(selectedPlayer.length()==1){
            if(selectedPlayer[0] == 'P' || selectedPlayer[0] == 'C' || selectedPlayer[0] == 'p' || selectedPlayer[0] == 'c')
                letterflag = 1;
            }
            if(letterflag == 0) cerr<<"invalid letter"<<endl; 
        }while(letterflag == 0);
        userChoice = selectedPlayer[0]; // assignment user choice 
        displayGame();

        string letterChoice1;
        while(1){

        char moveColumn;
        do{ 
            cout<<"Player1 (X), please select between columns : "; //Player1 column choice until enter correct format
            getline(cin,letterChoice1); 
            if(cin.eof()) exit(1);
        }while(letterChoice1 == " "); // input  space or empty control 
        flag = 1; // for change board 'X'.This flag is using in play function
        if(letterChoice1.length()==1 && letterChoice1 != " ") moveColumn =letterChoice1[0];
        if(moveColumn < 97) moveColumn = moveColumn + 32;//if input letter upper , input will low

        string nameOffile,key1 ="SAVE",key2 ="LOAD",key3="UNDO",split =" ",find=" ",token,loadName; // for save or load variables
        int flag5,flag3,flag8=0,flag10=3; // checking variables

        if(letterChoice1.length() > 1){ // if inputUser.length >1 , we assume user maybe entered LOAD or SAVE
            do  {
                find =letterChoice1.substr(0,letterChoice1.find(split)); //Separate input until find space
                if(find == key1){  // if first 4 char EQUAL key1(SAVE), saveFile function will start
                if(letterChoice1.length()>4){  
                    token =letterChoice1.substr(5,letterChoice1.length());
                    if(token.length()>=1 && token !=" ")    flag5 =saveFile(token); //save game with filename  
                }
                if(flag5 == 0 && token.length()>=1 && token !="     "){ // checking save and output saved success
                    cout<<endl<<">>> Saved file Name :"<<token<<endl<<">>> You can continue..."<<endl;  
                    displayGame();
                }
                }else if(find == key2){ // if first 4 char egual key2(LOAD) loadFile function will start.
                    if(letterChoice1.length()>5) 
                    loadName =letterChoice1.substr(5,letterChoice1.length()); // load name is keeping user's entered file name                    
                    flag3 = loadFile(loadName); // file loading
                    if(flag3==0)    cout<<endl<<">>> Loaded File Name :"<<loadName<<endl<<">>> You can continue..."<<endl; // success loaded print
                    displayGame();
                }

               if(find==key3) flag10=setBoard(); // if user entered UNDO, setBoard function will call
                
                if( find == key1 || find == key2){ 
                    if(flag == 1){
                    cout<<"Player1 (X), please select between columns : "; // after save or load, again user input
                    getline(cin,letterChoice1);
                    flag8=0;
                    }else flag8 = 0;
                }
                if(find != key1 && find != key2 & find!=key3){
                    cerr<<"Invalid column!! Player1 (X), please select between columns :"; // if user hasn't entered SAVE OR LOAD OR UNDO
                    getline(cin,letterChoice1);                                            // print will be  error   
                }
                if(find==key3 && flag10==0) {
                    cout<<"Player1 (X), please select between columns : "; // if user entered undo and all board empty
                    getline(cin,letterChoice1);                            //user should enter column letter
                    flag8=0; // flag8 is while condition
                    key3=" ";
                }
                if(letterChoice1.length() > 1 || letterChoice1 ==" ") flag8 = 1;
                if(letterChoice1.length()==1 && letterChoice1 != " ") {
                    moveColumn =letterChoice1[0]; 
                    if(moveColumn < 97) moveColumn = moveColumn + 32;//if input letter upper , input will low
                    flag8=0;
                }
                if(flag10==1) flag8 =0; // for undo, if user entered undo, while will stop 
                if(flag==2) flag8 = 0; // if loaded file flag == 2 , while will stop
            }while(flag8==1); // user input check
        }

        if(letterChoice1.length()==1) moveColumn =letterChoice1[0]; // assignment user column letter choice 

        if(moveColumn < 97) moveColumn = moveColumn + 32;
        if(flag ==1 ){
        if(getcheckColumnFull(moveColumn) == 1 || getcheckLetterCorrect(moveColumn) == 2){ // checking letter and column
            do {
                if(getcheckColumnFull(moveColumn) == 1)
                    cerr<<"Column is full!! Player1 (X) , please select between columns : ";
                if(getcheckLetterCorrect(moveColumn) == 2) 
                    cerr<<"Invalid column!! Player1 (X), please select between columns : ";       
                getline(cin,letterChoice1);
                moveColumn =letterChoice1[0];
                if(moveColumn < 97) moveColumn = moveColumn + 32;//if input letter upper , input will low
            }while(getcheckColumnFull(moveColumn) == 1 || getcheckLetterCorrect(moveColumn) == 2 ); 
        }
        
        if(moveColumn < 97) moveColumn = moveColumn + 32; // if letter uppercase, letter will be lowercase
        if(find!=key3){
        if(play(moveColumn)==1) exit(1);  // board changing according to entered column.If there is a winner , game will be stop  
        }
        } //if flag end
    /* -------------------- Player2 start-------------------*/ 
        string letterChoice2;
        char moveColumn1;

        if(userChoice == 'P' || userChoice == 'p'){
        do  {
            cout<<"Player2 (O) , please select between columns : "; //Player2 column choice, until enter correct format
            getline(cin,letterChoice2);
            if(cin.eof()) exit(1);
            if(letterChoice2.length()==1 && letterChoice2 != " ") moveColumn1 =letterChoice2[0];
            if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
            if(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2) 
            cerr<<"Invalid column!! Player2 (O), please select between columns"<<endl; //empty control 

        }while(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2);  //  input space or empty control 
        flag = 2;
        string key4="UNDO";
        find=" ";
        int flag2,flag4,flag9=0,flag11=0; // for save and load flags
        
        if(letterChoice2.length() > 1){ // if inputUser.length >1 , we assume user maybe entered LOAD or SAVE
            do  {
                find =letterChoice2.substr(0,letterChoice2.find(split)); //Separate input until find space
                if(find == key1){  // if first 4 char EQUAL key1(SAVE), saveFile function will start
                if(letterChoice2.length()>4){  
                    token =letterChoice2.substr(5,letterChoice2.length());
                    if(token.length()>=1 && token !=" ")    flag2 =saveFile(token); //save game with filename  
                }
                if(flag2 == 0 && token.length()>=1 && token !="     ") // checking save and output saved success
                    cout<<endl<<">>> Saved file Name :"<<token<<endl<<">>> You can continue..."<<endl;
                    displayGame();

                }else if(find == key2){ // if first 4 char egual key2(LOAD) loadFile function will start.
                    if(letterChoice2.length()>=5) 
                    loadName =letterChoice2.substr(5,letterChoice2.length()); // load name is keeping user's entered file name                    
                    flag4 = loadFile(loadName); // file loading
                    if(flag4==0)    cout<<endl<<">>> Loaded File Name :"<<loadName<<endl<<">>> You can continue..."<<endl; // success loaded print
                    displayGame();
                }  
                if(find==key4) flag11=setBoard(); // if user entered UNDO, setBoard function will call

                if( find == key1 || find == key2){
                    if(flag==2){
                        cout<<"Player2 (O), please select between columns : "; // after save or load, again user input
                        getline(cin,letterChoice2);
                        flag9=0;
                    } else flag9=0;
                }
                if(find != key1 && find != key2 & find!=key4){
                    cerr<<"Invalid column!! Player2 (O), please select between columns :"; // if user hasn't entered SAVE OR LOAD, print will be  error
                    getline(cin,letterChoice2);
                }
                if(find==key4 && flag11==0) {   // if user entered undo and all board empty
                                                //user should enter column letter
                    cout<<"Player2 (O), please select between columns : "; 
                    getline(cin,letterChoice2);
                    flag9=0; // flag9 is while condition
                    key4=" ";
                }
                if(letterChoice2.length() > 1 || letterChoice2 ==" ") flag9 = 1;
                if(letterChoice2.length()==1 && letterChoice2 != " ") {
                    moveColumn1 =letterChoice2[0]; 
                    if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;//if input letter upper , input will low
                    flag9=0;
                }
                if(flag11==1 || flag==1) flag9 =0;
            }while(flag9==1); // user input check
        }
        if(flag==2){
            if(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2){ // control column full or letter invalid
                do  {
                    if(getcheckColumnFull(moveColumn1) == 1)
                        cerr<<" Column is full!! Player2 (O) , please select between columns : ";
                    if(getcheckLetterCorrect(moveColumn1) == 2) 
                        cerr<<"Invalid column!! Player2 (O), please select between columns : ";
                    getline(cin,letterChoice2);
                    moveColumn1 =letterChoice2[0];
                    if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
                }while(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2); 
            }

            if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
            if(find!=key4)
                if(play(moveColumn1)==1) exit(1);
        } 
        }//player 2 end
        if(userChoice == 'C' || userChoice == 'c') {
            play(); // if computer selected, computer will select a letter
            flag=2;
        }  
    }//while end;
       return 0;
    }
    /*-----------end of playgame----------*/
}
/*-----------end of name space----------*/
