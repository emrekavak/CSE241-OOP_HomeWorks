/* Name = Emre KAVAK && Number = 151044085 && HW4 >> CONNECT FOUR WİTH DYNAMIC ARRAY << */
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
using namespace std;
//typeFormat for change board X O C and x o c and check board
typedef enum typeFormat{SPACE,EMPTY,USER1,USER2,COM, LOWUSER1, LOWUSER2, LOWCOM} TYPE;

class ConnectFour
{
public:
    ConnectFour(); // default constructor creating 5x5 game with board 
    ConnectFour(int rowValue, int columnValue); 
    //Precondition : rowValue > 0 && columnValue > 0
    //PostCondition : will resize gameBoard according to parameter
    ConnectFour(string fileName);
    //Precondition : string file game input
    //PostCondition :fillBoard() function will call and file will load
    ConnectFour(int rowNo, int columnNo,int objeNumber);
    //Precondition : this constructor for multi mode objects
    //PostCondition : 5 object will create with object no (like 1-2-3-4-5);
    ConnectFour(const ConnectFour& otherOb); // copy constructor
    ConnectFour& operator=(const ConnectFour & righSide); // assignment operator
    friend int multiMod();
    //Precondition : after gameMode select, if mode == M, this function will call
    //PostCondition : 5 object will create and game will play in this function with another functions
    int playGame(); // if game mode S or s, this function will call
    int play(); // if player choice C, this function will call and computer will play, board will change in here
    int play(const char columnChoice); // if player choice P, user selected column no will changed board in here
    int resizeLoadedFile(); // after load a file, this function will created new 2d board according to row and column
    const int saveFile( const string fileName); 
    //Precondition : user will input SAVE OR SAVE FILENAME OR SAVE FILENAME.TXT
    //PostCondition : gameBoard row,column,userChoice and board will save in file
    const int loadFile( const string fileName);
    //Precondition : user will input LOAD FILENAME OR LOAD FILENAME.TXT
    //PostCondition : gameBoard row,column,userChoice and board cells will save in file
    const void displayGame()const; // for display gameBoard
    
    int getColumn()const{ return column;} // for return column
    int getRow()const{return row;} // for return row
    int getGameMode()const{ return gameMode;} // for return gameMode
    int getUserChoice()const{ return userChoice;} // for return userChoice
    
    void setColumn( int colValue){ if(colValue >=0 ) column = colValue;} // for set column
    void setRow(int rowValue){ if(rowValue>=0) row = rowValue;}  // for set row
    void setGameMode(char gmode){ if(gmode == 'M'|| gmode == 'M' || gmode == 'M' || gmode == 'M') gameMode =gmode;}// for set gameMode
    void setUserChoice(char uChoice){ if(uChoice =='P' ||uChoice =='p' 
                        ||uChoice =='S' ||uChoice =='s' ) userChoice =uChoice;}// for set userChoice
    
    int getcheckColumnFull(const char letter)const; 
    //Precondition : checking board full or not
    //Postcondition : if board full, return will 1 else return will 0
    int getcheckLetterCorrect(const char letter)const; // for check letter correct or not
    int getcheckWinner(const int rowNum,const int columnNum,const int user);
    //Precondition : after user's selected column, this function will call
    //Postcondition : if user win, return 1 and lover case game board will create in here
    int getCheckBoardFull()const; // for check column full or not. if full return will 1 else return 0
    static int setLivingCells(); // for count changed all  cell
    
    bool operator==(const ConnectFour & other)const; // for compare two object with all information
    bool operator!=(const ConnectFour & other)const; // for compare two object with all information
    
    ~ConnectFour(); // destructor    
private:
    
    class Cell{
    public:
            Cell(); // default constructor creates cell cellType = USER!, rowNumber =0 and position='a'
            Cell(int temp);  // for cell type assignment
          
            int getCellType(){ return cellType;}const // for return cellType
            char getPositionCell(){ return positionCell;}const // for return position cells
            int getRowNumber(){ return rowNumber;}const // for return row number
            
            void setCellType(const int type){ if(type>=SPACE && type<=LOWCOM)cellType = type;}; //for set cellType
            void setPositionCell(const char position){ if(position>='a' && position<='z') positionCell = position;}; //for set position cell
            void setRowNumber(const int rowValue){ if(rowValue >= 0) rowNumber = rowValue;}; //for set Row number
            
            Cell& operator++(); //Prefix ++ operator overload
            Cell operator++(int); //Postfix ++ operator overload
            Cell& operator--(); //Prefix -- operator overload
            Cell operator--(int); //Postfix -- operator overload
            bool operator==(const Cell & other)const; //compare operator overload
            friend istream& operator>>(istream& inputStream,Cell& other); // output overload
            friend ostream& operator<<(ostream& outputStream,const Cell& other); //input overload
    private:     
            char positionCell; // a,b,c
            int rowNumber; // 0,1,2,3
            int cellType; // can be  SPACE,EMPTY,USER1, USER2, COM, LOWUSER1, LOWUSER2, LOWCOM         
    };
    friend ostream& operator<<(ostream& outputStream, const ConnectFour::Cell& other);// output overload for reach cell overload
    friend istream& operator>>(istream& inputStream,ConnectFour::Cell& other);//input overload for reach cell overload
    
    const int fillBoard(const string fileName); // after user entered filename, gameBoard will loading in this function with row,column etc.
    int setObjects(const string objeName); // for multi mode game(5 object) user enter file name, PVP or PVC in here.
    int playObjects(); //(multi mode) After finish getting information, multi mode game play in this function    
    Cell ** gameBoard; //2d Cell array
    int column; //column number for gameBoard
    int row;    //row number for gameBoard
    char userChoice; // can be P,p or C,c
    char gameMode;  // can be M,m or S,s
    int flag; //for user 1 and 2 flag  choice when board change X,O,C
    int objeNo; // for multi mode ,objects numbers (1,2,3,4,5)
    static int numberlivingCells ; //counting how many cell changed
    int winnerObjeFlag ;//if a object winner(M mode), this will be 1
};

int ConnectFour::numberlivingCells =0; // static variable
int countObjectWinner = 0; // this variable is keeping winner object no;

int multiMod(){ // for multi game play friend function
    int flag = 0; // for hame mode control
    string one ="object1",two="object2",three="object3",four="object4",five="object5"; //object name for print
    //if game mode is M(multi) 5 objects are creating
    ConnectFour obje1(2,2,1),obje2(2,2,2),obje3(2,2,3),obje4(2,2,4),obje5(2,2,5);
    obje1.setObjects(one); //objects are setting and names sending with setObjects
    obje2.setObjects(two);
    obje3.setObjects(three);
    obje4.setObjects(four);
    obje5.setObjects(five);
    
    while(countObjectWinner!=5){ //multi mode continue until all object win. countObjectWinner is a glbal variable
    string ob;
    int flagObno;;
    int obNo;
        do{
            cout<<"Please enter Object No between ( 1-2-3-4-5 ) :"; // objeNo control
            cin>>obNo;
            if(cin.eof()) exit(1);
            if(cin.fail()){
                cerr<<"invalid size"<<endl;
                cin.clear();
                cin.ignore();
                cout<<"Please enter Object No :";
                cin>>obNo;
        }
    }while(cin.fail());        
    // M mode is starting play
        if(obNo == 1) obje1.playObjects(); // according to selected object no number, object will start game
        if(obNo == 2) {
            obje2.playObjects();
            if(obje1 == obje2) cout<<"same object1 and object2"<<endl; // == operator using
        }
        if(obNo == 3) obje3.playObjects();
        if(obNo == 4) obje4.playObjects();
        if(obNo == 5) obje5.playObjects();
    }//while end
    if(countObjectWinner==5) cout<<"!!!!! GAME END !!!!!"<<endl;
}    
int main(int argc, char** argv) {
    ConnectFour a; // default object is creating
    a.playGame(); // gameStarting
    return 0;
}
/*-----------end of main----------*/
ConnectFour::Cell::Cell(){ // default constructor cell class
    cellType = USER1;
    rowNumber = 0;
    positionCell = 'a';
}
ConnectFour::Cell::Cell(int type){ // for cell type assignment
    cellType = type;
}
ConnectFour::ConnectFour():row(5),column(5){ //default constructor
    
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
ConnectFour::ConnectFour(int rowValue, int columnValue){ // resize constructor
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
/*-----------end of Constructor----------*/
ConnectFour::ConnectFour(string fileName){
    fillBoard(fileName); // this function will create gameBoard according to in file information
}
ConnectFour::ConnectFour(int rowNo, int columnNo,int objeNumber) // for multi mode constructor
                                    :row(rowNo),column(columnNo),objeNo(objeNumber){
    gameBoard = new Cell*[row]; //game board create
    for(int i = 0; i < row; i++ )
        gameBoard[i]= new Cell[column];    
}
/*-----------end of Constructor----------*/
ConnectFour::ConnectFour(const ConnectFour& otherOb){ // copy constructor

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
ConnectFour::~ConnectFour(){ //destructor
	for(int j = 0; j < row; j++)
            delete[]gameBoard[j];
    delete[]gameBoard;	
}
/*-----------end of destructor----------*/
ConnectFour& ConnectFour::operator=(const ConnectFour & righSide){

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
/*-----------end of = operator----------*/
bool ConnectFour::operator ==(const ConnectFour& other) const{ // two object compare ==
    int cellsFlag,rowAndColumnFlag;
    if(this->row == other.row && this->column == other.column && this->userChoice == other.userChoice ) rowAndColumnFlag =1;
    //compere object variables
    if(this == &other) return true;
    else if(rowAndColumnFlag == 1){
        for(int i = row-1; i>=0; i--){
            for(int k=0; k< column; k++){
                if(this->gameBoard[i][k].getCellType() == other.gameBoard[i][k].getCellType())
                    cellsFlag = 1; // if cells variables same
                else {
                    i=0;   //else loop will end
                    k=column;
                    cellsFlag =0;
                }
            }   
        }
    }
    return (cellsFlag == 1 && rowAndColumnFlag == 1) ;
}
/*-----------end of == operator----------*/
bool ConnectFour::operator!=(const ConnectFour & other)const{ // two object compare !=
    int cellsFlag,rowAndColumnFlag;
    
    if(this->row != other.row && this->column != other.column && this->userChoice != other.userChoice ) rowAndColumnFlag =1;
    //compere object variables
    if(this == &other) return true;
    else if(rowAndColumnFlag == 1){
        for(int i = row-1; i>=row; i--){
            for(int k=0; k< column; k++){
                if(this->gameBoard[i][k].getCellType() != other.gameBoard[i][k].getCellType())
                    cellsFlag = 1; // if cells variables not same
                else {
                    i=0;  //else loop will end
                    k=column;
                    cellsFlag =0;
                }   
            }
        }
    }
    return (cellsFlag == 1 && rowAndColumnFlag == 1) ;   
}
/*-----------end of != operator----------*/
ConnectFour::Cell& ConnectFour::Cell::operator++(){ //prefix
    switch(this->cellType){
        case EMPTY : this->cellType  = USER1; // Cell type will change
                    break;
        case USER1 : this->cellType  = USER2; 
                    break;
        case USER2 : this->cellType  = COM;
                    break;
        case COM   : this->cellType  = EMPTY;
                    break;
    }
    return *this;
}
/*-----------end of ++ operator----------*/
ConnectFour::Cell ConnectFour::Cell::operator++(int ignoreme){ //postfix
    int temp = this->getCellType();
    switch(cellType){
        case EMPTY : cellType  = USER1;
                    break;
        case USER1 : cellType  = USER2;
                    break;
        case USER2 : cellType  = COM;
                    break;
        case COM   :cellType  = EMPTY;    
                    break;
    }
    return Cell(temp);
}    
/*-----------end of ++ operator----------*/
ConnectFour::Cell& ConnectFour::Cell::operator--(){ //prefix
      switch(this->cellType){
        case EMPTY : this->cellType  = COM;
                    break;
        case USER1 : this->cellType  = EMPTY;
                    break;
        case USER2 : this->cellType  = USER1;
                    break;
        case COM   : this->cellType  = USER2;
                    break;
    }
    return *this;
}
/*-----------end of -- operator----------*/
ConnectFour::Cell ConnectFour::Cell::operator--(int ignoreme){ //postfix
    int temp = this->cellType;
     switch(this->cellType){
        case EMPTY : this->cellType  = COM;
                    break;
        case USER1 : this->cellType  = EMPTY;
                    break;
        case USER2 : this->cellType  = USER1;
                    break;
        case COM   : this->cellType  = USER2;
                    break;
    }
     return Cell(temp);
}
/*-----------end of -- operator----------*/
bool ConnectFour::Cell::operator==(const Cell & other)const{
    return (this->rowNumber==other.rowNumber && this->cellType==other.cellType && this->positionCell==other.positionCell);
}
/*-----------end of == operator----------*/
ostream& operator<<(ostream& outputStream, const ConnectFour::Cell & obOther){
    outputStream<< obOther.cellType;
    outputStream<< obOther.rowNumber;
    outputStream<< obOther.positionCell;
    return outputStream;    
}
/*-----------end of << operator----------*/
istream& operator>>(istream& inputStream,ConnectFour::Cell& other){
    inputStream>> other.cellType;
    inputStream>> other.rowNumber;
    inputStream>> other.positionCell;
    return inputStream;   
}
/*-----------end of >> operator----------*/
int ConnectFour::playGame(){
    int modeFlag=0;
    string mode;
    cout<<endl;
    
    do{ 
        cout<<"Please enter Game Mode ( M or S ) :"; //game mode select
        getline(cin,mode);
        if(mode.length()==1)
            if(mode[0] == 'M'|| mode[0] == 'm'|| mode[0] == 'S' || mode[0] == 's') modeFlag =1;
        if(modeFlag == 0) //game mode control  
            cerr<<"Invalid mode!!"<<endl;
        cout<<endl;
    }while(modeFlag ==0);
    gameMode = mode[0]; //game mode change
    
    if(gameMode=='S' || gameMode== 's'){ //single mode play
        string nameFile;
    do{ 
        cout<<"Please enter file name :"; //file name input
        getline(cin,nameFile);
    }while(fillBoard(nameFile)==1);
  
    string selectedPlayer;
    int letterflag=0;
    do{
        cout<<"Please enter play versus Player(P) or Computer(C)  :"; //player choice enter
        getline(cin,selectedPlayer);
        if(selectedPlayer.length()==1){
        if(selectedPlayer[0] == 'P' || selectedPlayer[0] == 'C' || selectedPlayer[0] == 'p' || selectedPlayer[0] == 'c')
            letterflag = 1;
        }
        if(letterflag == 0) cerr<<"invalid letter"<<endl; 
    }while(letterflag == 0);
    userChoice = selectedPlayer[0];
    displayGame();
    
    string letterChoice1;
    while(1){
    
    char moveColumn;
    do{
        cout<<"Player1 (X), please select between columns : "; //Player1 column choice until enter correct format
        getline(cin,letterChoice1); 
    }while(letterChoice1 == " "); // input  space or empty control 
    
    if(letterChoice1.length()==1 && letterChoice1 != " ") moveColumn =letterChoice1[0];
    if(moveColumn < 97) moveColumn = moveColumn + 32;//if input letter upper , input will low
    
    string nameOffile,key1 ="SAVE",key2 ="LOAD",split =" ",find,token,loadName; // for save or load variables
    int flag5,flag3; // checking variables
    
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
            if( find == key1 || find == key2)   cout<<"Player1 (X), please select between columns : "; // after save or load, again user input
            else cerr<<"Invalid column!! Player1 (X), please select between columns :"; // if user hasn't entered SAVE OR LOAD, print will be  error
            getline(cin,letterChoice1);
            if(letterChoice1.length()==1) moveColumn =letterChoice1[0];
        }while(letterChoice1.length() > 1 || letterChoice1 ==" "); // user input check
    }
    if(letterChoice1.length()==1) moveColumn =letterChoice1[0]; // assignment user column letter choice  
    if(moveColumn < 97) moveColumn = moveColumn + 32;
    if(getcheckColumnFull(moveColumn) == 1 || getcheckLetterCorrect(moveColumn) == 2){ // checking letter and column
        do {
            if(getcheckColumnFull(moveColumn) == 1)
                cerr<<"Column is full!! Player1 (X) , please select between columns : ";
            if(getcheckLetterCorrect(moveColumn) == 2) 
                cerr<<"Invalid column!! Player1 (X), please select between columns : ";       
            getline(cin,letterChoice1);
            moveColumn =letterChoice1[0];
        }while(getcheckColumnFull(moveColumn) == 1 || getcheckLetterCorrect(moveColumn) == 2 ); 
    }
    flag = 1; // for change board 'X'.This flag is using in play function
    if(moveColumn < 97) moveColumn = moveColumn + 32; // if letter uppercase, letter will be lowercase
    if(play(moveColumn)==1) exit(1);  // board changing according to entered column.If there is a winner , game will be stop   
/* -------------------- Player2 start-------------------*/ 
    string letterChoice2;
    char moveColumn1;
    
    if(userChoice == 'P' || userChoice == 'p'){
    do  {
        cout<<"Player2 (O) , please select between columns : "; //Player2 column choice, until enter correct format
        getline(cin,letterChoice2);
        if(letterChoice2.length()==1 && letterChoice2 != " ") moveColumn1 =letterChoice2[0];
        if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
        if(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2) 
            cerr<<"Invalid column!! Player2 (O), please select between columns"<<endl; //empty control 
    }while(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2);  //  input space or empty control 
 
    int flag2,flag4; // for save and load flags
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
            
            if( find == key1 || find == key2 )   cout<<"Player2 (O), please select between columns : "; // after save or load, again user input
            else cerr<<"Invalid column!! Player2 (O), please select between columns :"; // if user hasn't entered SAVE OR LOAD, print will be  error
           
                getline(cin,letterChoice2);
            if(letterChoice2.length()==1) moveColumn1 =letterChoice1[0]; // assignment user column letter choice  
            if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32; // checking letter low or uppercase
            
        }while(letterChoice2.length() > 1 || letterChoice2 ==" "); // user input check
    }

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
    
    flag = 2;
    if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
    if(play(moveColumn1)==1) exit(1);
    } //player 2 end
    if(userChoice == 'C' || userChoice == 'c') play(); // if computer selected, computer will select a letter
    }//while end;
    
    } // if mode end
    if(gameMode == 'm' || gameMode =='M') multiMod(); // if game mode multi, this function will play multi game
   return 0;
}
/*-----------end of playGame----------*/
const int ConnectFour::fillBoard(const string fileName){ // according to file, board will create
    string readFile,read;
    int widthCount =0,rowCount=0,readWidth=0,widthMax=0;
    
    ifstream fileload(fileName.c_str(),ios::in);
 
    if(fileload){
        for(int j = 0; j < row; j++)
            delete[]gameBoard[j];
        delete[]gameBoard;
    }
    else {
        cout<<"File not open..."<<endl;
        return 1;
    }
    while(fileload)
    {
        getline(fileload,readFile); //file reading
        for(int i=0;i<readFile.length();i++){
                widthCount++; // column reading
                if(widthMax<widthCount){
                    widthMax = widthCount;
                    widthCount = 0;
                }
        }
        widthCount = 0;
        if(fileload)rowCount++; // row reading
    }
    fileload.close(); 
    row = rowCount; // new board start create
    column = widthMax;
    gameBoard = new Cell*[row];
    for(int i = 0; i < row; i++ )
        gameBoard[i]= new Cell[column]; 
    ifstream load(fileName.c_str(),ios::in);
    int m=0,letternum;
   
    while(load)
    {   
        letternum = 97;
        getline(load,read);
        for(int k=0; k <column;k++,letternum++){ //assigment board ' ' or '*',position, row number
            if(m<row){
            gameBoard[m][k].setPositionCell(letternum);
            gameBoard[m][k].setRowNumber(m);
            if(read[k]==' ') gameBoard[m][k].setCellType(SPACE);
            if(read[k]== '*') gameBoard[m][k].setCellType(EMPTY);        
            }
        }
       if(load) m++;   
    }
    displayGame();
    load.close(); 
    return 0;
 }

const int ConnectFour::saveFile(const string fileName){
    ofstream fileWrite;
    fileWrite.open(fileName.c_str(), ios::out); //saved file according to fileName
    if(!fileWrite){
        cerr<<endl<<"Error save file!!!"; //checking file open or not.if not, return will be -1
        return -1;
    }
    if(gameMode =='m') fileWrite<<objeNo<<endl; //if game mode multi, objeNo will saved
    
    fileWrite<<row<<endl;   // user's entered board height number will write first line in file.
    fileWrite<<column<<endl;    // writing width
    fileWrite<<userChoice<<endl;    //user's entered player choice P or C  will write third line in file.
    for(int i = 0; i < row; i++){ // and finally, current board cellType write in file.
        for(int j = 0; j<column; j++){
            if(gameBoard[i][j].getCellType() == SPACE) fileWrite<<' '; //cell information writing
            if(gameBoard[i][j].getCellType()== EMPTY) fileWrite<<'*';
            if(gameBoard[i][j].getCellType() == USER1) fileWrite<<'x';
            if(gameBoard[i][j].getCellType() == USER2) fileWrite<<'O';
            if(gameBoard[i][j].getCellType()== COM) fileWrite<<'C';
        }
        fileWrite<<"\n";
    }
    fileWrite.close();
    return 0;    
}
const int ConnectFour::loadFile(const string fileName){

    string boardload;
    ifstream fileload(fileName.c_str(),ios::in); // according to user entered file name, file will open
    if(!fileload){
        cerr<<endl<<"Error open file !!!"<<endl; // checking file opening
        return -1; 
    }else{
       
     for(int j = 0; j < row; j++)
            delete[]gameBoard[j];
        delete[]gameBoard;// before board clearing   
        
    if(gameMode =='m'){ //if game mode multi, objeNo will assignment
        getline(fileload,boardload); 
        objeNo =stoi(boardload);
    }
    getline(fileload,boardload); // first, board height reading in first line.
    row =stoi(boardload);
   
    getline(fileload, boardload);//width reading 
    column = stoi(boardload);
    getline(fileload, boardload);//user choice reading
    userChoice = boardload[0];
    resizeLoadedFile();  // game resizing according to height and width in file
    int m=0,letternum;
    
    while(fileload)
    {   
        letternum = 97;
        getline(fileload,boardload);
        for(int k=0; k <column;k++,letternum++){ //assigment board ' ' or '*'
            if(m<row){
            gameBoard[m][k].setPositionCell(letternum);
            gameBoard[m][k].setRowNumber(m);
            if(boardload[k]==' ') gameBoard[m][k].setCellType(SPACE); //cell information writing
            if(boardload[k]== '*') gameBoard[m][k].setCellType(EMPTY);
            if(boardload[k]== 'x') gameBoard[m][k].setCellType(USER1); 
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
int ConnectFour::resizeLoadedFile(){ // if a object file loaded, object will be resize
     
    gameBoard = new Cell*[row];
    for(int i = 0; i < row; i++ )
        gameBoard[i]= new Cell[column];
}

int ConnectFour::play(){ //  computer play
    
    char letters[30];
    char move;    //arr array will keep letter according to entered size. move is keeping computer select letter
    int letterNum = 97,count =0;
    
    for(int i = 0; i < column ; i++){  
        letters[i] = letterNum; //asothersignment letters according to entered size
        letterNum++;
        count++;
    }
    int count1 =0,count2=0,count3=0,count4=0,col=0; //counts will count how many X there are if they entered consecutive 3 times vertical or horizontal

    move =letters[rand()%count]; // random will select a letter in array;
    for(int i =row-1; i >= 0; i--){ 
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
    /**/
    for(int i =row-1; i >= 0; i--){ 
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
    
    if(count4 == 3) move=col+97; // if there are 3 times 'X' vertical, computer letter will be according to column number +97
    if(getcheckColumnFull(move) == 1){ // if selected column is full, move will change until find a '.';
        for(int i =0; i<row; i++){ 
            for(int j =0 ; j<column; j++){
                if(gameBoard[i][j].getCellType() == EMPTY){ 
                    decltype(move)newlet;
                    newlet = j+97;
                    move = newlet;
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
                setLivingCells(); //living cell 
                i=0;
                j=column;
            }
        }
         
    }
    if(getcheckWinner(rowVal,columnval,COM)==1){  // checking p1 won or not 
                cout<<"!!!!! Computer Wİnner !!!!!"<<endl;
                displayGame();
                winnerObjeFlag =1; // if a object is winner, winnerObject will be 1 
                countObjectWinner++;
                exit(1);
    }
    if(getCheckBoardFull()==1){ // checking board full  or empty 
        cout<<"!!!!! No a winner. Board is full !!!!! "<<endl;
        displayGame();
        exit(1);
    }
    return 0;
}
int ConnectFour::play(const char columnChoice){
    int rowVal,columnval;

    for(int i = row-1; i >=0; i--){
        for(int j = 0; j < column; j++){
            if(gameBoard[i][j].getPositionCell() == columnChoice && gameBoard[i][j].getCellType() == EMPTY ){
            rowVal = gameBoard[i][j].getRowNumber();
            columnval =j;
            if(flag == 1) gameBoard[rowVal][columnval].setCellType(USER1);
            if(flag == 2) gameBoard[rowVal][columnval].setCellType(USER2);
            displayGame();
            setLivingCells(); 
            i=0;
            j=column;
            }
        }
    }
    if(flag==1){ //player 1
        if(getcheckWinner(rowVal,columnval,USER1)==1){  // checking p1 won or not 
            cout<<"!!!!! Congratulations  Player1 (X). You have won !!!!! "<<endl;
            
            displayGame();
            winnerObjeFlag =1; // if a object is winner, winnerObject will be 1 
            countObjectWinner++;
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
            winnerObjeFlag =1; // if a object is winner, winnerObject will be 1 
            countObjectWinner++;
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
int ConnectFour::getcheckColumnFull(const char letter)const{
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

int ConnectFour::getcheckLetterCorrect(const char letter)const{
    int firstnum1= 65,firstnum2=97,flag = 0;
    
    for(int i = 0; i < column ; i++){  //assignment letter
        if(letter == firstnum1 ||  letter==firstnum2) flag = 1;
            firstnum1++;
            firstnum2++;
    }
    if(flag == 1) return 1;
    else return 2;
    return 0;   
}
int ConnectFour::setLivingCells(){ // living cells are increasing
    numberlivingCells++;
    if(numberlivingCells % 2 ==0) cout<<"Living Cells = "<<numberlivingCells<<endl;
    return 0;
}
int ConnectFour::getcheckWinner(const int rowNum,const int columnNum,const int user){
    int count1 = 0, count2 = 0,count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0,
        count9 = 0, count10 = 0, count11=0,count12 =0, count13=0; // counts will count X or O according to selected row and column
   
    for(int i=0; i<4; i++){
        if( rowNum+i < row && gameBoard[rowNum+i][columnNum].getCellType() == user) count1++; 	// vertical count     
        if( columnNum-i >= 0 && gameBoard[rowNum][columnNum-i].getCellType() == user) count2++;	// horizontal count xxx-                     
        if( columnNum+i < column && gameBoard[rowNum][columnNum+i].getCellType() == user) count3++;	// horizontal count -xxx 
        if(columnNum+i-1 >= 0 && columnNum+i-1 < column && gameBoard[rowNum][columnNum+i-1].getCellType() == user) count4++; // horizontal count x-xx                      
        if(columnNum+i-2 >= 0 && columnNum+i-2 < column && gameBoard[rowNum][columnNum+i-2].getCellType() == user) count5++; // horizontal count xx-x   
    }
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
    // after if there is a won, letters will be small according to letterUser(letterUser 'X' or 'O')
    if(count1 == 4 || count2 == 4 || count3 == 4 || count4 == 4 || count5 == 4 || count6 == 4 || count7 == 4 || count8 == 4 || count9 == 4 || 
    count10 == 4 || count11 == 4 || count12 == 4 || count13 == 4 ){
        if(user == 2) flagLower = LOWUSER1; // lowercase
        if(user == 3) flagLower = LOWUSER2;
        if(user == 4) flagLower = LOWCOM;
        for(int k = 0; k <4; k++){
            if(count1 == 4) gameBoard[rowNum+k][columnNum].setCellType(flagLower);              
            if(count2 == 4 && count3 != 4 && count4 != 4 && count5 != 4) gameBoard[rowNum][columnNum-k].setCellType(flagLower);              
            if(count3 == 4 && count2 != 4 && count4 != 4 && count5 != 4) gameBoard[rowNum][columnNum+k].setCellType(flagLower);              
            if(count4 == 4 && count5 !=4 ) gameBoard[rowNum][columnNum+k-1].setCellType(flagLower); 
            if(count5 == 4) gameBoard[rowNum][columnNum+k-2].setCellType(flagLower); 
            if(count6 == 4) gameBoard[rowNum+k][columnNum-k].setCellType(flagLower);              
            if(count7 == 4) gameBoard[rowNum-k][columnNum-k].setCellType(flagLower);             
            if(count8 == 4) gameBoard[rowNum-k][columnNum+k].setCellType(flagLower);            
            if(count9 == 4) gameBoard[rowNum+k][columnNum+k].setCellType(flagLower);          
            if(count10 == 4) gameBoard[rowNum + k - 1][columnNum+k-1].setCellType(flagLower);          
            if(count11 == 4) gameBoard[rowNum + k - 1][columnNum-k+1].setCellType(flagLower);           
            if(count12 == 4) gameBoard[rowNum + k - 2][columnNum+k-2].setCellType(flagLower);            
            if(count13 == 4 && count11 !=4){
            if(gameBoard[rowNum + k - 2][columnNum - k + 2].getCellType() ==user) gameBoard[rowNum + k - 2][columnNum - k + 2].setCellType(flagLower); 
            }
        }
        return 1;
    }
    return 0;   
}
int ConnectFour::getCheckBoardFull()const{
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
int ConnectFour::setObjects(const string objeName){ // after user choice Multi mode, user enter objects width and player choice in here
    gameMode ='m';
    string nameFile;
    do{ 
        cout<<"Please enter file name for"<<objeName<<" :";
        getline(cin,nameFile);
    }while(fillBoard(nameFile)==1);
    
    string selectedPlayer;
    int letterflag=0;
    do{
        cout<<"Please enter play versus Player(P) or Computer(C)  :"; //player choice enter
        getline(cin,selectedPlayer);
        if(selectedPlayer.length()==1){
         if(selectedPlayer[0] == 'P' || selectedPlayer[0] == 'C' || selectedPlayer[0] == 'p' || selectedPlayer[0] == 'c')
             letterflag = 1;
        }
         if(letterflag == 0)
            cerr<<"invalid letter"<<endl; 
    }while(letterflag == 0);
    userChoice = selectedPlayer[0];
    displayGame();
}
int ConnectFour::playObjects(){ // Multi game objects input
    
    string letterChoice1;

    displayGame();
    flag =1;
    cin.ignore();
    if( winnerObjeFlag !=1) { // if this object isnt a winner check
        char moveColumn;
    do  {
            cout<<"Player1 (X), please select between columns : "; //Player1 column choice until enter correct format
            getline(cin,letterChoice1); 
        }while(letterChoice1 == " "); // input  space or empty control 
    
    if(letterChoice1.length()==1 && letterChoice1 != " ") moveColumn =letterChoice1[0];
    if(moveColumn < 97) moveColumn = moveColumn + 32;
   
    string nameOffile,key1 ="SAVE",key2 ="LOAD",split =" ",find,token,loadName; // for save or load variables
    int flag5,flag3;
    
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
            if( find == key1 || find == key2)   cout<<"Player1 (X), please select between columns : "; // after save or load, again user input
            else cerr<<"Invalid column!! Player1 (X), please select between columns :"; // if user hasn't entered SAVE OR LOAD, print will be  error
            getline(cin,letterChoice1);
            if(letterChoice1.length()==1) moveColumn =letterChoice1[0]; // assignment user column letter choice  
            if(moveColumn < 97) moveColumn = moveColumn + 32;
        }while(letterChoice1.length() > 1 || letterChoice1 ==" "); // user input check
    }
    
    if(getcheckColumnFull(moveColumn) == 1 || getcheckLetterCorrect(moveColumn) == 2){ // checking letter and column
      do {
          if(getcheckColumnFull(moveColumn) == 1)
              cerr<<"Column is full!! Player1 (X) , please select between columns : ";
          if(getcheckLetterCorrect(moveColumn) == 2) 
              cerr<<"buu Invalid column!! Player1 (X), please select between columns : ";       
          getline(cin,letterChoice1);
          moveColumn =letterChoice1[0];
      }while(getcheckColumnFull(moveColumn) == 1 || getcheckLetterCorrect(moveColumn) == 2 ); 
    }
    if(letterChoice1.length()==1 && letterChoice1 != " ") moveColumn =letterChoice1[0]; 
    if(moveColumn < 97) moveColumn = moveColumn + 32;

    play(moveColumn);
      }//winner if end
    else cerr<<"This object winner before"<<endl;   // winner object output 
/* -------------------- Player2 start-------------------*/ 
    string letterChoice2;
    char moveColumn1;

    flag =2;
    if(winnerObjeFlag !=1){ //  object winner control, if object win winnerObjeFlag will be 1
        
    if(userChoice == 'p' || userChoice == 'P' ){
        do  {
        cout<<"Player2 (O) , please select between columns : "; //Player2 column choice, until enter correct format
        getline(cin,letterChoice2);
        if(letterChoice2.length()==1 && letterChoice2 != " ") moveColumn1 =letterChoice2[0];
        if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
        if(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2) 
            cerr<<"bup2 Invalid column!! Player2 (O), please select between columns"<<endl; //empty control 
       
    }while(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2);  //  input space or empty control 
    
    int flag2,flag4;
    string nameOffile,key1 ="SAVE",key2 ="LOAD",split =" ",find,token,loadName; // for save or load variables
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
            
            if( find == key1 || find == key2 )   cout<<"Player2 (O), please select between columns : "; // after save or load, again user input
            else cerr<<" Invalid column!! Player2 (O), please select between columns :"; // if user hasn't entered SAVE OR LOAD, print will be  error
           
                getline(cin,letterChoice2);
            if(letterChoice2.length()==1) moveColumn1 =letterChoice1[0]; // assignment user column letter choice  
            if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32; // checking letter low or uppercase
            
        }while(letterChoice2.length() > 1 || letterChoice2 ==" "); // user input check
    }
    if(letterChoice1.length()==1) moveColumn1 =letterChoice1[0];
    if(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2){
        do  {
            if(getcheckColumnFull(moveColumn1) == 1)
                cerr<<"Column is full!! Player2 (O) , please select between columns : ";
            if(getcheckLetterCorrect(moveColumn1) == 2) 
                cerr<<" Invalid column!! Player2 (O), please select between columns : ";
            getline(cin,letterChoice2);
            moveColumn1 =letterChoice2[0];
        }while(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2); 
    }
    if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
    play(moveColumn1);

    }
    if(userChoice == 'C' || userChoice == 'c') play();

    }else cerr<<"This object winner before"<<endl;  //if object winned, cerr will star     
}
/*-----------end of playObjects----------*/
const void ConnectFour::displayGame() const{
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

