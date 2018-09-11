//This is the implementation for the class ConnectFourAbstract
//This is the file connecfourabstract.cpp
#include "connectfourabstract.h"
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;
typedef enum typeFormat{SPACE,EMPTY,USER1,USER2,COM, LOWUSER1, LOWUSER2, LOWCOM} TYPE;

namespace ConnectFour{

    ConnectFourAbstract::ConnectFourAbstract():row(5),column(5){ //default constructor

        gameBoard = new Cell*[row]; //game board creating
        
        for(int i = 0; i < row; i++ )
            gameBoard[i]= new Cell[column];
        
        for(int i=0;i<row;i++ ){
            int letternum =97;
            for(int k=0; k <column;k++,letternum++){ //assignment gameBoard column letter,row number and type(EMPTY == '*')
                gameBoard[i][k].setPositionCell(letternum);
                gameBoard[i][k].setRowNumber(i);
                gameBoard[i][k].setCellType(EMPTY);
            }
        }
    }
    /* ---------- end of default constructor ---------- */
    ConnectFourAbstract::ConnectFourAbstract(int rowValue, int columnValue){ // resize constructor
        
        if(rowValue > 0 && columnValue > 0){
        for(int j = 0; j < row; j++)
                delete[]gameBoard[j];
        delete[]gameBoard;
        row = rowValue;
        column = columnValue;
        gameBoard = new Cell*[row];
        for(int i = 0; i < row; i++ )
            gameBoard[i]= new Cell[column]; 
        }
    }
    /*----------- end of resize constructor----------*/
    ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& otherOb){ // copy constructor

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
    /*-----------end of Constructor----------*/
    ConnectFourAbstract::~ConnectFourAbstract(){ //destructor
            for(int j = 0; j < row; j++)
                delete[]gameBoard[j];
        delete[]gameBoard;	
    }
    /*-----------end of destructor----------*/
    void ConnectFourAbstract::resize(int width, int height){ //resize function
        
        if(height > 0 && width > 0){ //before dynamic array is deleting
            for(int j = 0; j < row; j++)
                delete[]gameBoard[j];
        delete[]gameBoard;

        row = height;  // new array creating 
        column = width;
        gameBoard = new Cell*[row];
        for(int i = 0; i < row; i++ )
            gameBoard[i]= new Cell[column]; 

            for(int i=0; i<row ;i++ ){
               int letternum =97;
               for(int k=0; k < column ;k++,letternum++){ //assignment gameBoard column letter,row number and type(EMPTY == '*')
                   gameBoard[i][k].setPositionCell(letternum);
                   gameBoard[i][k].setRowNumber(i);
                   gameBoard[i][k].setCellType(EMPTY);
               }
           }
        }   
    }
    /*-----------end of resize function ----------*/
    ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract & righSide){

        if(row != righSide.getRow() && row != righSide.getColumn()){
            for(int i=0; i< row; i++)  //before board deleting
                    delete[]gameBoard[i];
            delete[]gameBoard;

            gameBoard = new Cell*[righSide.getRow()]; //new board is  creating
            for(int i = 0; i < righSide.getRow(); i++ )
            gameBoard[i]= new Cell[righSide.getColumn()];
        }
        row=righSide.getRow(); //new board assignment
        column =righSide.getColumn();
        gameMode = righSide.getGameMode();
        userChoice = righSide.getUserChoice();	
        for(int i=0; i<row; i++){
            for(int j =0; j<column; j++){  //assignment gameBoard column letter,row number and type(EMPTY == '*')
                gameBoard[i][j].setCellType(righSide.gameBoard[i][j].getCellType());
                gameBoard[i][j].setRowNumber(righSide.gameBoard[i][j].getRowNumber());
                gameBoard[i][j].setPositionCell(righSide.gameBoard[i][j].getPositionCell());		
            }
       }
       return *this;	
    }
    /*-----------end of operator= overload  ----------*/
    int ConnectFourAbstract::playGame(){
        
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
        while(1){    // game starting

        char moveColumn;
        do{
            cout<<"Player1 (X), please select between columns : "; //Player1 column choice until enter correct format
            getline(cin,letterChoice1); 
            if(cin.eof()) exit(1);
        }while(letterChoice1 == " "); // input  space or empty control 
        flag = 1; // for change board 'X'.This flag is using in play function
        
        if(letterChoice1.length()==1 && letterChoice1 != " ") moveColumn =letterChoice1[0]; // entered letter assignment to char 
        if(moveColumn < 97) moveColumn = moveColumn + 32;//if input letter upper , input will low

        string nameOffile,key1 ="SAVE",key2 ="LOAD",split =" ",find,token,loadName; // for save or load variables
        int flag5,flag3,flag8=0; // for checking variables

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
                if( find == key1 || find == key2){
                    if(flag==1){
                        cout<<"Player1 (X), please select between columns : "; // after save or load, again user input
                        getline(cin,letterChoice1);
                        flag8 = 1;
                    }else flag8=0;
                   
                }   
                if(find != key1 && find != key2){
                    cerr<<"Invalid column!! Player1 (X), please select between columns :"; // if user hasn't entered SAVE OR LOAD OR UNDO                                                                       // print will be  error
                    getline(cin,letterChoice1);
                }
               
                if(letterChoice1.length() > 1 || letterChoice1 ==" ") flag8 = 1;
                if(letterChoice1.length()==1 && letterChoice1 != " ") {
                    moveColumn =letterChoice1[0]; 
                    if(moveColumn < 97) moveColumn = moveColumn + 32;//if input letter upper , input will low
                    flag8=0;
                }
                
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
                    cerr<<" BU MU Invalid column!! Player1 (X), please select between columns : ";       
                getline(cin,letterChoice1);
                moveColumn =letterChoice1[0];
                if(letterChoice1.length()==1) moveColumn =letterChoice1[0]; // assignment user column letter choice  
                if(moveColumn < 97) moveColumn = moveColumn + 32;
            }while(getcheckColumnFull(moveColumn) == 1 || getcheckLetterCorrect(moveColumn) == 2 ); 
        }
        
        if(moveColumn < 97) moveColumn = moveColumn + 32; // if letter uppercase, letter will be lowercase
        if(play(moveColumn)==1) exit(1);  // board changing according to entered column.If there is a winner , game will be stop  
        }
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
        int flag2,flag4,flag9=0; // for save and load flags
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
                if( find == key1 || find == key2){
                if(flag==2){ // loaded file order checking 
                        cout<<"Player2 (O), please select between columns : "; // after save or load, again user input
                        getline(cin,letterChoice2);
                        flag9 = 1;
                    }else flag9=0;
                   
                }   
                if(find != key1 && find != key2){
                    cerr<<"Invalid column!! Player2 (O), please select between columns :"; // if user hasn't entered SAVE OR LOAD OR UNDO                                                                       // print will be  error
                    getline(cin,letterChoice2);
                }
               
                if(letterChoice2.length() > 1 || letterChoice2 ==" ") flag9 = 1;
                if(letterChoice2.length()==1 && letterChoice2 != " ") {
                    moveColumn1 =letterChoice2[0]; 
                    if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;//if input letter upper , input will low
                    flag9=0;
                }
                if(flag == 1) flag9=0;
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
            if(play(moveColumn1)==1) exit(1);
            } //player 2 end
            
        }//flag end
        if(userChoice == 'C' || userChoice == 'c') {
            play(); // if computer selected, computer will select a letter
            flag=2;
        }
        }//while end;
       return 0;
    }
    /*-----------end of playGame----------*/
    const int ConnectFourAbstract::saveFile(const string fileName){
        ofstream fileWrite;
        fileWrite.open(fileName.c_str(), ios::out); //saved file according to fileName
        if(!fileWrite){
            cerr<<endl<<"Error save file!!!"; //checking file open or not.if not, return will be -1
            return -1;
        }
        fileWrite<<flag<<endl;
        fileWrite<<gameMode<<endl;  // game information write to file 
        fileWrite<<row<<endl;   
        fileWrite<<column<<endl;   
        fileWrite<<userChoice<<endl;
        
        for(int i = 0; i < row; i++){ // and finally, current board cellType write in file.
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
    /*-----------end of saveFile----------*/
    const int ConnectFourAbstract::loadFile(const string fileName){

        string boardload;
        ifstream fileload(fileName.c_str(),ios::in); // according to user entered file name, file will open
        if(!fileload){
            cerr<<endl<<"Error open file !!!"<<endl; // checking file opening
            return -1; 
        }
        else{
            for(int j = 0; j < row; j++)
                delete[]gameBoard[j];
            delete[]gameBoard;// before board clearing   
            
            getline(fileload,boardload); // first, board height reading in first line.
            flag =atoi(boardload.c_str());
            getline(fileload,boardload); // first, board height reading in first line.
            gameMode =boardload[0];
            getline(fileload,boardload);
            row =atoi(boardload.c_str());
            getline(fileload, boardload);//width reading 
            column = atoi(boardload.c_str());
            getline(fileload, boardload);//user choice reading
            userChoice = boardload[0];
            resizeLoadedFile();  // game resizing according to height and width in file
            int m=0,letternum;

            while(fileload)
            {   
                letternum = 97;
                getline(fileload,boardload);
                for(int k=0; k <column;k++,letternum++){ //assignment board ' ' or '*'
                    if(m<row){
                    gameBoard[m][k].setPositionCell(letternum);
                    gameBoard[m][k].setRowNumber(m);
                    if(boardload[k]==' ') gameBoard[m][k].setCellType(SPACE); //cell information writing
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
    /*-----------end of loadFile----------*/
    int ConnectFourAbstract::resizeLoadedFile(){ // if a object file loaded, object will be resize

        gameBoard = new Cell*[row];
        for(int i = 0; i < row; i++ )
            gameBoard[i]= new Cell[column];
    }
    /*-----------end of resizeLoadedFile----------*/
    int ConnectFourAbstract::play(){ //  computer play

        char letters[30];
        char move;    //letter array will keep letter according to entered size. move is keeping computer select letter
        int letterNum = 97,count =0;

        for(int i = 0; i < column ; i++){  
            letters[i] = letterNum; // letters according to entered size
            letterNum++;
            count++;
        }
        int count1 =0,count2=0,count3=0,count4=0,col=0; //counts will count how many X there are 
                                                        //if they entered consecutive 3 times vertical or horizontal
        move =letters[rand()%count]; // a random letter will select  in array;
        
        for(int i =row-1; i >= 0; i--){  // horizontal smart move select
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
                        move =(char)j+97;
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
    int ConnectFourAbstract::play(const char columnChoice){
        int rowVal,columnval;

        for(int i = row-1; i >=0; i--){   //game board is changing in here
            for(int j = 0; j < column; j++){
                if(gameBoard[i][j].getPositionCell() == columnChoice && gameBoard[i][j].getCellType() == EMPTY ){
                rowVal = gameBoard[i][j].getRowNumber();
                columnval =j;
                if(flag == 1) gameBoard[rowVal][columnval].setCellType(USER1);
                if(flag == 2) gameBoard[rowVal][columnval].setCellType(USER2);
                displayGame();
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
    int ConnectFourAbstract::getcheckColumnFull(const char letter)const{
        int count = 0;
        int col =letter-97;
        // X and O are counting and count is equal heigh, return will be 1
        for(int i =row-1; i >= 0; i--){
            if(gameBoard[i][col].getCellType() == USER1 || gameBoard[i][col].getCellType() == USER2 
                || gameBoard[i][col].getCellType() == SPACE ||gameBoard[i][col].getCellType() ==COM )
               count++;
        }  
        if(count == row) return 1;
        else return 0;
    }
    /*-----------end of getcheckColumnFull----------*/
    int ConnectFourAbstract::getcheckLetterCorrect(const char letter)const{
        int firstnum1= 65,firstnum2=97,flag = 0;

        for(int i = 0; i < column ; i++){  //assignment letter
            if(letter == firstnum1 ||  letter==firstnum2) flag = 1; // letter checking
                firstnum1++;
                firstnum2++;
        }
        if(flag == 1) return 1; // if  letter correct, return will be 1
        else return 2;   // else return will be 2
        return 0;   
    }
    /*-----------end of getcheckLetterCorrect----------*/
    int ConnectFourAbstract::getCheckBoardFull()const{
        int countfull = 0;

        for( int i = 0 ; i< row ; i++){  //checking game board full or not
            for(int j = 0; j< column ; j++){
                if(gameBoard[i][j].getCellType() !=EMPTY) countfull++;
            }
        }
        if(countfull == row*column) 
            return 1; //if full, returned number will be 1 
        return 0;
    }
    /*-----------end of getCheckBoardFull----------*/
    const void ConnectFourAbstract::displayGame() const{
        cout<<endl;
        for(int k = 0; k< column;k++){
            cout<<gameBoard[0][k].getPositionCell();
        }
        cout<<endl;
          for(int i=0; i < row ; i++){
            for(int j = 0; j < column; j++){ 
                if(gameBoard[i][j].getCellType() == SPACE) cout<<" " ; // according to game type, print will X,O or ' '
                if(gameBoard[i][j].getCellType() == EMPTY) cout<<"*" ;
                if(gameBoard[i][j].getCellType() == USER1) cout<<"X" ;
                if(gameBoard[i][j].getCellType() == USER2 ) cout<<"O" ;
                if(gameBoard[i][j].getCellType() == COM ) cout<<"C" ;
                if(gameBoard[i][j].getCellType() == LOWCOM ) cout<<"c" ;
                if(gameBoard[i][j].getCellType() == LOWUSER1 ) cout<<'x';
                if(gameBoard[i][j].getCellType() == LOWUSER2 ) cout<<'o';    
            }
            cout<<endl;   
        }
        cout<<endl;
    }

}

