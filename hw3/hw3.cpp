/* Name = Emre KAVAK && Number = 151044085 && HW3 >> CONNECT FOUR WİTH OBJECTS << */
#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class ConnectFour
{
public:
    ConnectFour();
    ConnectFour(int width, int height); 
    ConnectFour(int width, int height,int objeNumber);
    
    inline int getWidth(){ return widthBoard;};
    inline int getHeight(){ return heightBoard;};
    
    int getcheckColumnFull(const char letter)const;
    int getCheckBoardFull()const;
    int getcheckLetterCorrect(const char letter)const;
    int getcheckWinner(const int row,const int column,const char letterUser);
    void setFillBoard();
    int setObjects(const string objeName);
    static int setLivingCells();
    
    void play();
    int play(const char columnChoice);
    int playGame();
    int playObjects();
    int resizeLoadedFile();

    const int saveFile( const string fileName);
    const int loadFile( const string fileName);
    const bool compareObjects(ConnectFour & object);
    const void displayGame()const;
    
private:
    class Cell{
    public:
            char positionCell; // a,b,c
            int rowNumber; // 0,1,2,3
            char cellType; // . X O   
    };
       
    vector<vector<Cell> >gameCells;
    int widthBoard;
    int heightBoard;
    char userChoice; // p or c
    char gameMode; 
    int flag; //for user 1 and 2 flag 
    int objeNo; // objects numbers (1,2,3,4,5)
    static int numberlivingCells ;
    int winnerObjeFlag ;//for winner object, this will be 1
};
int ConnectFour::numberlivingCells =0; // static variable
int countObjectWinner = 0; // this variable is keeping winner object no;

int main(int argc, char** argv) {
    
    ConnectFour a(2,2); // default object is creating
    char selectedMode;
    int flag = 0; // for hame mode control
    
    cout<<"\n"<<"----- Welcome to Connect Four Game ----- "<<endl;
    cout<<"\n"<<"* For save game, you should enter SAVE FILENAME."<<endl;
    cout<<"* For load game, you should enter LOAD FILENAME."<<endl;
    cout<<"* Note : You can only LOAD or SAVE when choosing a column"<<endl;
              
    do{ cout<<endl;
        cout<<"Please enter Game Mode ( M or S ) :"; //game mode select
        cin>>selectedMode;
        if(selectedMode == 'M'|| selectedMode == 'm'|| selectedMode == 'S' || selectedMode == 's') flag =0;
        else flag =1;
        if(flag == 1){ //game mode control  
            cerr<<"Invalid mode!!"<<endl;
            cin.clear();
            cin.ignore();
        }
        cout<<endl;
    }while(flag ==1);
            
    if(selectedMode == 'S' || selectedMode == 's') a.playGame(); // single mode select
    if(selectedMode == 'M' || selectedMode == 'm'){ //multi mode select
   
    string one ="object1",two="object2",three="object3",four="object4",five="object5"; //object name for print
    //if game mode is M(multi) 5 objects are creating
    ConnectFour obje1(2,2,1),obje2(2,2,2),obje3(2,2,3),obje4(2,2,4),obje5(2,2,5);
    obje1.setObjects(one); //objects are setting and names sending with setObjects
    obje2.setObjects(two);
    obje3.setObjects(three);
    obje4.setObjects(four);
    obje5.setObjects(five);
    
    while(countObjectWinner!=5){ //multi mode continue until all object win. countObjectWinner is a glbal variable
    int obNo;
        do{
            cout<<"Please enter Object No between ( 1-2-3-4-5 ) :"; // objeNo control
            cin>>obNo;
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
        obje2.compareObjects(obje1); // compareObjects, compare object with before object 
    }
    if(obNo == 3) {
        obje3.playObjects();
        obje3.compareObjects(obje2);
    }
    if(obNo == 4) {
        obje4.playObjects();
        obje4.compareObjects(obje3);
    }
    if(obNo == 5) {
        obje5.playObjects();
        obje5.compareObjects(obje4);
    }

    }//while end
    if(countObjectWinner==5) cout<<"!!!!! GAME END !!!!!"<<endl;
    }//if end
    return 0;
}
/*-----------end of main----------*/
ConnectFour::ConnectFour(int width, int height) // single mode ,board resize
                                    :widthBoard(width),heightBoard(height){
    gameCells.resize(heightBoard,vector<Cell>(widthBoard));
}
/*-----------end of Constructor----------*/

ConnectFour::ConnectFour(int width, int height,int objeNumber) // multi mode, objects with object no
                                    :widthBoard(width),heightBoard(height),objeNo(objeNumber){
    gameCells.resize(heightBoard,vector<Cell>(widthBoard));
}
/*-----------end of Constructor----------*/
ConnectFour::ConnectFour() // default objects width and height
                        :widthBoard(1),heightBoard(1){
}
/*-----------end of Constructor----------*/
int ConnectFour::playGame(){ // single mode game starting
    char selectedMode,moveColumn; // selected mode and column letter variables
    string letterChoice1;
    
    int numOfWith;
    gameMode ='s'; // game mode assignment
    do{
        cout<<"Please enter With :"; //width enter
        cin>>numOfWith;
        if(cin.fail()){
            cerr<<"invalid size"<<endl;
            cin.clear();
            cin.ignore();
            cout<<"Please enter With :";
            cin>>numOfWith;
        }
    }while(cin.fail());
    widthBoard = numOfWith;
    
    int numOfHeight; 
    do{
        cout<<"Please enter Height :"; //height enter
        cin>>numOfHeight;
        if(cin.fail()){
            cerr<<"invalid size"<<endl;
            cin.clear();
            cin.ignore();
            cout<<"Please enter height :";
            cin>>numOfHeight;
        }
    }while(cin.fail());
    heightBoard = numOfHeight;
    
    char selectedPlayer;
    int letterflag=0;
    do{
        cout<<"Please enter play versus Player(P) or Computer(C)  :"; //player choice enter
        cin>>selectedPlayer;
         if(selectedPlayer == 'P' || selectedPlayer == 'C' || selectedPlayer == 'p' || selectedPlayer == 'c')
             letterflag = 1;
         if(letterflag == 0){
            cerr<<"invalid letter"<<endl;
            cin.clear();
            cin.ignore();   
         }
    }while(letterflag == 0);
    userChoice = selectedPlayer;
    
    setFillBoard(); // according to entered sizes, board creating
    displayGame();
    
    cin.ignore();
    while(1){
        do  {
        cout<<"Player1 (X), please select between columns : "; //Player1 column choice until enter correct format
        getline(cin,letterChoice1);
        if(letterChoice1.length()== 0)  cerr<<"Invalid column!! Player1 (X), please select between columns"<<endl; // enter empty control
    }while(letterChoice1 == " " || letterChoice1.length() == 0); // input  space or empty control 
       
    if(letterChoice1.length()==1 && letterChoice1 != " ") moveColumn =letterChoice1[0]; 
    if(moveColumn < 97) moveColumn = moveColumn + 32; // checking letter low or uppercase
    
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
            if(letterChoice1.length()==1) moveColumn =letterChoice1[0]; // assignment user column letter choice  

        }while(letterChoice1.length() > 1 || letterChoice1 ==" " || letterChoice1.length() == 0 ); // user input check
    }
    
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
    flag = 1; // for change board 'X'.This flag is using in play funciton
    if(moveColumn < 97) moveColumn = moveColumn + 32; // if letter uppercase, letter will be lowercase
    if(play(moveColumn)==1) exit(1);  // board changing according to entered column.İf thereis a winner , game will be stop   
/* -------------------- Player2 start-------------------*/ 
    string letterChoice2;
    char moveColumn1;
    if(userChoice == 'P' || userChoice == 'p'){
    do  {
        cout<<"Player2 (O) , please select between columns : "; //Player2 column choice, until enter correct format
        getline(cin,letterChoice2);
        if(letterChoice2.length()== 0) cerr<<"Invalid column!! Player2 (O), please select between columns"<<endl; //empty control 
    }while(letterChoice2 == " " || letterChoice2.length() == 0);  //  input space or empty control 
 
    if(letterChoice2.length()==1 && letterChoice2 != " ") moveColumn1 =letterChoice2[0]; // assigment letter column 
    if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
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
            if( find == key1 || find == key2)   cout<<"Player2 (O), please select between columns : "; // after save or load, again user input
            else cerr<<"Invalid column!! Player2 (O), please select between columns :"; // if user hasn't entered SAVE OR LOAD, print will be  error
            getline(cin,letterChoice2);
            if(letterChoice2.length()==1) moveColumn1 =letterChoice1[0]; // assignment user column letter choice  

        }while(letterChoice2.length() > 1 || letterChoice2 ==" " || letterChoice2.length() == 0 ); // user input check
    }
    if(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2){ // control column full or letter invalid
        do  {
            if(getcheckColumnFull(moveColumn1) == 1)
                cerr<<"Column is full!! Player2 (O) , please select between columns : ";
            if(getcheckLetterCorrect(moveColumn1) == 2) 
                cerr<<"Invalid column!! Player2 (O), please select between columns : ";
            getline(cin,letterChoice2);
            moveColumn1 =letterChoice2[0];
        }while(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2); 
    }
    
    flag = 2;
    if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
    if(play(moveColumn1)==1) exit(1);
    } //player 2 end

    if(userChoice == 'C' || userChoice == 'c') play(); // if computer selected, computer will select a letter   
    }//while end;
   return 0;
}
/*-----------end of playGame----------*/
void ConnectFour::setFillBoard(){ // according to entered width and height, game creating
    
    gameCells.clear(); // before, board clearing
    gameCells.resize(heightBoard,vector<Cell>(widthBoard)); // board resizing
    for(int i = 0; i < heightBoard; i++){
    int letternum = 97;
        for(int j = 0; j < widthBoard; j++,letternum++){ //board filling
            gameCells[i][j].positionCell = letternum; // a b c d... assignment
            gameCells[i][j].rowNumber = i;            //0 1 2 3 ... assignment
            gameCells[i][j].cellType = '.';           // '.' assignment
         }
    }
}
/*-----------end of setFillBoard----------*/
void ConnectFour::play(){ //  computer play
    
    vector<char>letters(widthBoard);
    char move;    //arr array will keep letter according to entered size. move is keeping computer select letter
    int letterNum = 97,count =0;
    
    for(int i = 0; i < widthBoard ; i++){  
        letters[i] = letterNum; //assignment letters according to entered size
        letterNum++;
        count++;
    }
    int count1 =0,count2=0,count3=0,count4=0,column=0; //counts will count how many X there are if they entered consecutive 3 times vertical or horizontal

    move =letters[rand()%count]; // random will select a letter in array;
    for(int i =heightBoard-1; i >= 0; i--){ 
        for(int j =0 ; j<widthBoard; j++){
            if(gameCells[i][j].cellType == 'X'){
                for(int k = 0; k < 4; k++){
                    if(gameCells[i][j+k].cellType == 'X' && j+k < widthBoard ){ 
                    count1++;  
                    }
                    if(count1 ==3){
                    count2 = count1;
                    if(gameCells[i][j+k+1].cellType == '.' && j+k+1 < widthBoard ) column = j+k;
                    //column will keep column number if there are 3 times 'X' horizontal
                    }   
                }
            count1=0;
            }
        }
    }
  
    if(count4 == 3) move=column+97; // if there are 3 times 'X' vertical, computer letter will be according to column number +97
    if(getcheckColumnFull(move) == 1){ // if selected column is full, move will change until find a '.';
        for(int i =0; i<heightBoard; i++){ 
            for(int j =0 ; j<widthBoard; j++){
                if(gameCells[i][j].cellType == '.'){                  
                    move = j+97;
                }
            }
        }
    }
    int minesRow = 0,row;
    cout<<"Computer Played :"<<move<<endl;
    // according to  computer's letter, game BOARD changing
    for(int i = heightBoard-1; i >= 0; i--){
        for(int j = 0; j < widthBoard; j++){
            if(gameCells[i][j].positionCell == move && gameCells[i][j].cellType =='.'){
                row = gameCells[i][j].rowNumber;
                gameCells[row][j].cellType ='O';
                displayGame();
                setLivingCells(); //living cell 
                i=0;
                j=widthBoard;
            }
        }
    }
     if(getCheckBoardFull()==1){ // checking board full  or empty 
                    cout<<"!!!!! No a winner. Board is full !!!!! "<<endl;
                    displayGame();
                    exit(1);
        }
}
/*-----------end of play----------*/
int ConnectFour::play(const char columnChoice){
    int row,column;
    char letterUser1 ='X', letterUser2='O';

    for(int i = heightBoard-1; i >= 0; i--){
        for(int j = 0; j < widthBoard; j++){
            if(gameCells[i][j].positionCell == columnChoice && gameCells[i][j].cellType =='.'){
            row = gameCells[i][j].rowNumber;
            column =j;
            if(flag == 1) gameCells[row][column].cellType ='X';
            if(flag == 2) gameCells[row][column].cellType ='O';
            displayGame();
            setLivingCells(); 
            i=0;
            j=widthBoard;
            }
        }
    }
    if(flag==1){ //player 1
        if(getcheckWinner(row,column,letterUser1)==1){  // checking p1 won or not 
            cout<<"!!!!! Congratulations  Player1 (X). You have won !!!!! "<<endl;
            getcheckWinner(row,column,letterUser1);
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
         if(getcheckWinner(row,column,letterUser2)==1){  // checking p1 won or not 
            if(userChoice =='C' or userChoice =='c') cout<<"!!!!! Computer Wİnner !!!!!"<<endl;
            cout<<"!!!!! Congratulations  Player2 (O). You have won !!!!! "<<endl;
            getcheckWinner(row,column,letterUser1);
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
/*-----------end of play----------*/
int ConnectFour::getcheckColumnFull(const char letter)const{
    int count = 0;
    int column =letter-97;
    // X and O are counting and count is equal heigh, return will be 1
    for(int i =heightBoard-1; i >= 0; i--){
         if(gameCells[i][column].cellType == 'X' || gameCells[i][column].cellType == 'O' )
           count++;
    }  
    if(count == heightBoard) return 1;
    else return 0;
}
/*-----------end of getcheckColumnFull----------*/
int ConnectFour::getcheckLetterCorrect(const char letter)const{
    int firstnum1= 65,firstnum2=97,flag = 0;
    
    for(int i = 0; i < widthBoard ; i++){  //assignment letter
        if(letter == firstnum1 ||  letter==firstnum2) flag = 1;
            firstnum1++;
            firstnum2++;
    }
    if(flag == 1) return 1;
    else return 2;
    return 0;   
}
/*-----------end of getcheckLetterCorrect----------*/
int ConnectFour::getcheckWinner(const int row,const int column,const char letterUser){
    int count1 = 0, count2 = 0,count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0,
        count9 = 0, count10 = 0, count11=0,count12 =0, count13=0; // counts will count X or O according to selected row and column
     
    for(int i=0; i<4; i++){
        if( row+i < heightBoard && gameCells[row+i][column].cellType == letterUser) count1++; 	// vertical count     
        if( column-i >= 0 && gameCells[row][column-i].cellType == letterUser) count2++;	// horizontal count xxx-                     
        if( column+i < widthBoard && gameCells[row][column+i].cellType == letterUser) count3++;	// horizontal count -xxx 
        if(column+i-1 >= 0 && column+i-1 < widthBoard && gameCells[row][column+i-1].cellType == letterUser) count4++; // horizontal count x-xx                      
        if(column+i-2 >= 0 && column+i-2 < widthBoard && gameCells[row][column+i-2].cellType == letterUser) count5++; // horizontal count xx-x   
    }
    for(int j = 0; j<4; j++){                                                                                                    
        if(row +j < heightBoard && column-j >= 0 && gameCells[row+j][column-j].cellType == letterUser) count6++; // diagonal1 count -xxx
        if(row -j >=0 && column+j < heightBoard && gameCells[row-j][column+j].cellType == letterUser) count8++;  // diagonal1 count xxx-
        if(row -j >=0 && column-j >= 0 && gameCells[row-j][column-j].cellType == letterUser) count7++;    // diagonal2 count -xxx       
        if(row+j < heightBoard && column+j < widthBoard && gameCells[row+j][column+j].cellType == letterUser) count9++;// diagonal2 count xxx-     
    } 
    for(int m = 0; m<=4; m++){ 
        if(row + m -1 < heightBoard && row + m -1 >=0 && column+m-1 >=0 && column+m-1 < widthBoard && gameCells[row + m - 1][column+m-1].cellType == letterUser) 
            count10++; // diagonal2  count x-xxx   
        if(row + m < heightBoard && row + m -1 >=0 && column-m+1 >=0 && column-m-1 < widthBoard && gameCells[row + m - 1][column-m+1].cellType == letterUser) 
            count11++; // diagonal1 count x-xxx          
        if(row + m -2 < heightBoard &&  row + m -2 >=0 && column+m-2 >=0 && column+m-2 < widthBoard && gameCells[row + m - 2][column+m-2].cellType == letterUser) 
            count12++; // diagonal2 count xx-x                     
        if(row + m -2 < heightBoard && row + m -2 >=0 && column-m +2 >= 0 && column-m+2 < widthBoard && gameCells[row + m - 2][column - m + 2].cellType == letterUser) 
            count13++; // diagonal1 count xx-x      
    }
    // after if there is a won, letters will be small according to letterUser(letterUser 'X' or 'O')
    if(count1 == 4 || count2 == 4 || count3 == 4 || count4 == 4 || count5 == 4 || count6 == 4 || count7 == 4 || count8 == 4 || count9 == 4 || 
    count10 == 4 || count11 == 4 || count12 == 4 || count13 == 4 ){
        for(int k = 0; k <4; k++){
            if(count1 == 4)
                gameCells[row+k][column].cellType = letterUser+' ';              
            if(count2 == 4 && count3 != 4 && count4 != 4 && count5 != 4) 
                gameCells[row][column-k].cellType = letterUser+' ';             
            if(count3 == 4 && count2 != 4 && count4 != 4 && count5 != 4) 
                gameCells[row][column+k].cellType = letterUser+' ';             
            if(count4 == 4 && count5 !=4 ) 
                gameCells[row][column+k-1].cellType = letterUser+' '; 
            if(count5 == 4 ) 
                gameCells[row][column+k-2].cellType = letterUser+' '; 
            if(count6 == 4)
                gameCells[row+k][column-k].cellType = letterUser+' ';              
            if(count7 == 4)
                gameCells[row-k][column-k].cellType= letterUser+' ';            
            if(count8 == 4)
                gameCells[row-k][column+k].cellType = letterUser+' ';             
            if(count9 == 4)
                gameCells[row+k][column+k].cellType = letterUser+' ';          
            if(count10 == 4)
                gameCells[row + k - 1][column+k-1].cellType = letterUser+' ';          
            if(count11 == 4)
                gameCells[row + k - 1][column-k+1].cellType = letterUser+' ';            
            if(count12 == 4)
                gameCells[row + k - 2][column+k-2].cellType = letterUser+' ';           
            if(count13 == 4 && count11 !=4){
                if(gameCells[row + k - 2][column - k + 2].cellType ==letterUser) gameCells[row + k - 2][column - k + 2].cellType = letterUser+' ';
            }
        }
            return 1;
    }
    return 0;   
}
/*-----------end of getcheckWinner----------*/
int ConnectFour::getCheckBoardFull()const{
    int countfull = 0;
    
    for( int i = 0 ; i< heightBoard ; i++){  //checking game board full or not
        for(int j = 0; j< widthBoard ; j++){
            if(gameCells[i][j].cellType !='.') countfull++;
        }
    }
    if(countfull == heightBoard*widthBoard) 
        return 1; //if full, returned number will be 1 
    return 0;
}
/*-----------end of getCheckBoardFull----------*/
const int ConnectFour::saveFile(const string fileName){
    ofstream fileWrite;
    fileWrite.open(fileName.c_str(), ios::out); //saved file according to fileName
    if(!fileWrite){
        cerr<<endl<<"Error save file!!!"; //checking file open or not.if not, return will be -1
        return -1;
    }
    if(gameMode =='m') fileWrite<<objeNo<<endl; //if game mode multi, objeNo will saved
    
    fileWrite<<heightBoard<<endl;   // user's entered board height number will write first line in file.
    fileWrite<<widthBoard<<endl;    // writing width
    fileWrite<<userChoice<<endl;    //user's entered player choice P or C  will write third line in file.
    for(int i = 0; i < heightBoard; i++){ // and finally, current board cellType write in file.
        for(int j = 0; j<widthBoard; j++){
            fileWrite<<gameCells[i][j].cellType; //cellType writing
        }
        fileWrite<<"\n";
    }
    fileWrite.close();
    return 0;    
}
/*-----------end of saveFile----------*/
const int ConnectFour::loadFile(const string fileName){

    string boardload;
    ifstream fileload(fileName.c_str(),ios::in); // according to user entered file name, file will open
    if(!fileload){
        cerr<<endl<<"Error open file !!!"<<endl; // checking file opening
        return -1; 
    }else{
    if(gameMode =='m'){ //if game mode multi, objeNo will assignment
        getline(fileload,boardload); 
        objeNo =stoi(boardload);
    }
    getline(fileload,boardload); // first, board height reading in first line.
    heightBoard =stoi(boardload);
    getline(fileload, boardload);//width reading 
    widthBoard = stoi(boardload);
    getline(fileload, boardload);//user choice reading
    userChoice = boardload[0];
    resizeLoadedFile();  // game resizing according to height and width in file
    int i=0;
        while(getline(fileload,boardload)){ // loading cellType (.,X,O) 
            for(int j=0; j<widthBoard;j++){
              gameCells[i][j].cellType=boardload[j]; 
            }
        i++;    
        }
    }
    fileload.close();
    return 0;
}
/*-----------end of loadFile----------*/
int ConnectFour::setObjects(const string objeName){ // after user choice Multi mode, user enter objects width and player choice in here
    int count=0;
    gameMode ='m';
    int widthOb;
    
    do{
        cout<<"Please enter width for "<<objeName<<":"; //object width
        cin>>widthOb;
        if(cin.fail()){
            cerr<<"invalid size"<<endl;
            cin.clear();
            cin.ignore();
            cout<<"Please enter width for "<<objeName<<":";
            cin>>widthOb;
        }
    }while(cin.fail());
    widthBoard = widthOb;
    
    int heightOb;
    do{
        cout<<"Please enter height for "<<objeName<<":"; //object height
        cin>>heightOb;
        if(cin.fail()){
            cerr<<"invalid size"<<endl;
        cin.clear();
        cin.ignore();
        cout<<"Please enter height for "<<objeName<<":";
        cin>>heightOb;
        }
    }while(cin.fail());
 
    heightBoard = heightOb;
    int letterflag =0;
    char versusOb;
    do{
        cout<<"Please enter play versus Player(P) or Computer(C)  :"; //object player choice
        cin>>versusOb;
        if(versusOb == 'P' || versusOb == 'C' || versusOb == 'p' || versusOb == 'c')
            letterflag = 1;
        if(letterflag == 0){
            cerr<<"invalid letter"<<endl;
            cin.clear();
            cin.ignore();   
        }
    }while(letterflag == 0);
  
    userChoice = versusOb;
    setFillBoard();  // objects creating
    displayGame();
}
/*-----------end of setObjects----------*/
int ConnectFour::playObjects(){ // Multi game, player in here
    
    string letterChoice1;
    char moveColumn;
    displayGame();
    flag =1;
    cin.ignore();
    if( winnerObjeFlag !=1) {
        do  {
         cout<<"Player1 (X), please select between columns : "; //Player1 column choice until enter correct format
         getline(cin,letterChoice1);
         if(letterChoice1.length()== 0)  cerr<<"Invalid column!! Player1 (X), please select between columns"<<endl; // enter empty control
    }while(letterChoice1 == " " || letterChoice1.length() == 0); // input  space or empty control 

    if(letterChoice1.length()==1 && letterChoice1 != " ") moveColumn =letterChoice1[0]; 
    if(moveColumn < 97) moveColumn = moveColumn + 32;
   
    string nameOffile,key1 ="SAVE",key2 ="LOAD",split =" ",find,token,loadName; // for save or load variables
    int flag5,flag3;
    
    if(letterChoice1.length() > 1){ // if letterChoice1.length >1 , we assume user maybe entered LOAD or SAVE
        do  {
            find =letterChoice1.substr(0,letterChoice1.find(split)); //Separate input until find space
            if(find == key1){  // if first 4 char EQUAL key1(SAVE), saveFile function will start
            if(letterChoice1.length()>4){  
                token =letterChoice1.substr(5,letterChoice1.length());

                if(token.length()>=1 && token !=" ")    flag5 =saveFile(token); //save game with filename  
            }
            if(flag5 == 0 && token.length()>=1 && token !="     "){// checking save and output saved success
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

        }while(letterChoice1.length() > 1 || letterChoice1 ==" " || letterChoice1.length() == 0 ); // user input check
    }
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
    if(letterChoice1.length()==1 && letterChoice1 != " ") moveColumn =letterChoice1[0]; 
    if(moveColumn < 97) moveColumn = moveColumn + 32;

    play(moveColumn);
      }//winner if end
       else cerr<<"This object winner before"<<endl;    
/* -------------------- Player2 start-------------------*/ 
    string letterChoice2;
    char moveColumn1;

    flag =2;
    if(winnerObjeFlag !=1){ //  object winner control, if object win winnerObjeFlag will be 1
        
    if(userChoice == 'p' || userChoice == 'P' ){
        do  {
            cout<<"Player2 (O) , please select between columns : "; //Player2 column choice, until enter correct format
            getline(cin,letterChoice2);
            if(letterChoice2.length()== 0) cerr<<"Invalid column!! Player2 (O), please select between columns"<<endl; //empty control 
        }while(letterChoice2 == " " || letterChoice2.length() == 0);  //  input space or empty control 
    
    if(letterChoice2.length()==1 && letterChoice2 != " ") moveColumn1 =letterChoice2[0];
    
    if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
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
            if( find == key1 || find == key2)   cout<<"Player2 (O), please select between columns : "; // after save or load, again user input
            else cerr<<"Invalid column!! Player2 (O), please select between columns :"; // if user hasn't entered SAVE OR LOAD, print will be  error
            getline(cin,letterChoice2);
            if(letterChoice2.length()==1) moveColumn1 =letterChoice1[0]; // assignment user column letter choice  

        }while(letterChoice2.length() > 1 || letterChoice2 ==" " || letterChoice2.length() == 0 ); // user input check
    }
    
    if(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2){
        do  {
            if(getcheckColumnFull(moveColumn1) == 1)
                cerr<<"Column is full!! Player2 (O) , please select between columns : ";
            if(getcheckLetterCorrect(moveColumn1) == 2) 
                cerr<<"Invalid column!! Player2 (O), please select between columns : ";
            getline(cin,letterChoice2);
            moveColumn1 =letterChoice2[0];
        }while(getcheckColumnFull(moveColumn1) == 1 || getcheckLetterCorrect(moveColumn1) == 2); 
    }
    if(moveColumn1 < 97) moveColumn1 = moveColumn1 + 32;
    play(moveColumn1);

    }
    if(userChoice == 'C' || userChoice == 'c'){
        play();
    }
    }else cerr<<"This object winner before"<<endl;  //if object winned, cerr will star     
}
/*-----------end of playObjects----------*/
int ConnectFour::setLivingCells(){ // living cells are increasing
    numberlivingCells++;
    if(numberlivingCells % 2 ==0) cout<<"Living Cells = "<<numberlivingCells<<endl;
    return 0;
}
const bool ConnectFour::compareObjects(ConnectFour & object){ // compare Object with before object
    int count = 0,count1=0;
    //first main object is counting
    for(int i =0; i< heightBoard;i++){
        for(int j =0; j< widthBoard;j++){
            if(gameCells[i][j].cellType =='X' || gameCells[i][j].cellType =='O')
                count++;
        }
    }
    //second function parameter (object) counting 
    for(int i =0; i< object.heightBoard;i++){
        for(int j =0; j< object.widthBoard;j++){
            if(object.gameCells[i][j].cellType =='X' || object.gameCells[i][j].cellType =='O')
                count1++;
        }
    }
    if(count<count1) { //comparison counts
        cout<<"Object"<<objeNo<<" < "<<"object"<<object.objeNo<<endl;
        return false;   
    }
     if(count>count1) {
        cout<<"Object"<<objeNo<<" > "<<"object"<<object.objeNo<<endl;
        return true;   
    }
}
/*-----------end of compareObjects----------*/
int ConnectFour::resizeLoadedFile(){ // if a object file loaded, object will be resize
    gameCells.clear(); // before board clearing
    gameCells.resize(heightBoard,vector<Cell>(widthBoard)); // board resizing
      for(int i = 0; i < heightBoard; i++){
    int letternum = 97;
        for(int j = 0; j < widthBoard; j++,letternum++){ //board filling
            gameCells[i][j].positionCell = letternum; // a b c d... assignment
            gameCells[i][j].rowNumber = i;            //0 1 2 3 ... assignment
         }
    }
}
/*-----------end of resizeLoadedFile----------*/
const void ConnectFour::displayGame()const{ // game printing
    cout<<endl;
    for(int k = 0; k< widthBoard;k++){
        cout<<gameCells[0][k].positionCell;
    }
    cout<<endl;
    for(int i=0;i<heightBoard;i++){
        for(int j = 0; j < widthBoard; j++ ){
            cout<<gameCells[i][j].cellType;
        }
        cout<<endl;
    }
    cout<<endl;
}
/*-----------end of CONNECT FOUR GAME----------*/
