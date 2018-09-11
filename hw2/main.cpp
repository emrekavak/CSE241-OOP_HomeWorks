/* Name = Emre KAVAK && Number = 151044085 && HW2 >> CONNECT FOUR WÝTH SAVE OR LOAD GAME << */

#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
using namespace std;
const int MAX_SIZE = 20 ;

void createBoard(char board[][MAX_SIZE], int& size);
//Precondition : Take input size from user between 4-6...-20
//Postcondition : Create a board according to the entered input
void userSelect(char& choiceUser);
//Precondition : Take letter input from user between P,p or C,c
//Postcondition : according to user input, game will play p v p or p v c
void fillUserSelect(char board[][MAX_SIZE], int & size,char & playerChoice);
//Precondition : Take letter input from p1,p2 or c between printed column
//Postcondition :Board will change 'X' or 'O' and will printed.
//Some check will do (true letter ,true or full column,winner etc.) with another functions in here.
int selectColumnNumber(char board[][MAX_SIZE], int size,char columnSelect, int numberColumn, int & columSum);
//Precondition : Entered column letter will select with help listColumn function in here.
//Postcondition : Column Number will return for change board 'X' or 'O'.
char moveComputerSelect(char board[][MAX_SIZE], int size);
//Precondition : if user selected C or c this function will run.
//Postcondition : Random letter will produce in here and returned char move for change board.
int letterCorrectCheck(char letterSelect, int size);
//Precondition : Selected letter will check true or false.
//Postcondition : if letter is true, return will be 1, else return will be 2; 
int checkColumnFull(char board[][MAX_SIZE], int size,char letterColumn);
//Precondition : Selected letter column will check empty or full
//Postcondition : if column is empty, return will be 0, else return will be 1; 
int checkWinner(char board[][MAX_SIZE], int size, int row, int column,char letterUser);
//Precondition : After user selected a column, board will checking 4* 'X' or 'O' ,
//are there horizontal, diagonal or vertical.? and board full will check in here.
//Postcondition : if there are 4* 'X' or 'O' horizontal, diagonal or vertical, return 1
//if board is full and there isn't no one winner, return 3;
int letterColumnNumber(char letter);
//Precondition : This function returned column number according to entered letter;
//Postcondition : return column number;
int saveFile(const char board[][MAX_SIZE], const int & size, const char & playerChoice, string fileName ="SAVEDGAME.TXT");
//Precondition : After user enter SAVE OR SAVE FILE OR SAVE FILE.TXT etc this function will star
//Postcondition : Save game according to user entered name.If user enter just SAVE, name will be SAVEDGAME.TXT
int loadFile(char board[][MAX_SIZE],int & changeSize, char & changePlayer,string nameOfFile);
//Precondition : After user enter LOAD FILE.TXT OR LOAD FILENAME etc this function will star
//Postcondition : Game board, user choice and board size will change according to loaded game file.
void printBoard(const char board[][20], const int size);
//Precondition : This function take board and size;
//Postcondition : according to board size, board will be printed

int main(){
    char firstBoard[MAX_SIZE][MAX_SIZE];
    
    for(int j = 0; j < MAX_SIZE; j++){ // board filling with '.'
        for(int k = 0; k < 20; k++)
            firstBoard[j][k] = '.';
    } 
    cout<<"\n"<<"----- Welcome to Connect Four Game ----- "<<endl;
    cout<<"\n"<<"* For save game, you should enter SAVE or SAVE FILENAME. If you just enter SAVE, file name will be SAVEDGAME.TXT"<<endl
              <<"* For load game, you should enter LOAD FILENAME."<<endl;
           
    
    int sizeNumber; // sizeNumber will keep entered size 
    createBoard(firstBoard,sizeNumber);
    
    char user; //user will be according to entered choice P or C
    userSelect(user);
    printBoard(firstBoard,sizeNumber);
    // game is playing in filluserSelect.User will enter abcd. and board will change
    fillUserSelect(firstBoard,sizeNumber,user); 
    return 0;
}
/*-----------end of main----------*/
void createBoard(char board[][MAX_SIZE],int& sizeNumber){
    int arr[9] ={4,6,8,10,12,14,16,18,20}, flag = 0;
   
    cout<<"\n"<<"Please enter board size ( between 4-6-8-...-20 )  : ";
    cin>>sizeNumber;
    cout<<endl;
    for(int i = 0; i<9; i++){
        if(arr[i] == sizeNumber) //correct size check
            flag = 1;
    }
    if(flag == 0) {
        cin.clear();
        cin.ignore();
        cerr<<"Invalid size!";
        createBoard(board,sizeNumber); 
    } 
}
/*-----------end of createBoard----------*/
void userSelect(char& choiceUser){
    auto let=choiceUser;
    int flag =0;
    
    cout<<"Please enter your choice for play versus Player (P) or Computer (C) : ";
    cin>>let;
    // Checking Correct versus player letter
    if(let == 'p' || let == 'P' || let == 'c' || let == 'C'  ) choiceUser = let;
    else{cout<<endl;
        while(flag == 0){
            cerr<<"Invalid letter! Please enter your choice for play versus Player (P) or Computer (C) :";
            cin.clear();
            cin.ignore();
            cin>>let;
            if(let == 'p' || let == 'P' || let == 'c' || let == 'C'  ){ 
            choiceUser = let;
            flag = 1;
            }
        }
    }
     cin.ignore();
}
/*-----------end of userSelect----------*/
void fillUserSelect(char board[][MAX_SIZE], int & size, char & playerChoice){
    char moveColumn,correntColumn,correntColumn1, letterUser1 ='X'; //letterUser1 will use for check win function
    string inputUser;
    
    while(1){
        do  {
            cout<<"Player1 (X), please select between columns : "; //Player1 column choice until enter correct format
            getline(cin,inputUser);
            if(inputUser.length()== 0)  cerr<<"Invalid column!! Player1 (X), please select between columns"<<endl; // enter empty control
        }while(inputUser == " " || inputUser.length() == 0); // input  space or empty control 
        
        if(inputUser.length()==1 && inputUser != " ") moveColumn =inputUser[0]; // user selected letter assignment
        
        string nameOffile,key1 ="SAVE",key2 ="LOAD",split =" ",find,token,loadName; // for save or load variables
        int flag,flag3;
        
        if(inputUser.length() > 1){ // if inputUser.length >1 , we assume user maybe entered LOAD or SAVE
            do  {
                find =inputUser.substr(0,inputUser.find(split)); //Separate input until find space
                if(find == key1){  // if first 4 char EQUAL key1(SAVE), saveFile function will start
                if(inputUser.length()== 4) flag = saveFile(board,size,playerChoice); //if user enter just SAVE,file name will default name "SAVEDGAME.TXT"
                if(inputUser.length()>4){  
                    token =inputUser.substr(5,inputUser.length());
                    if(token.length()==0) saveFile(board,size,playerChoice); //if there is a space entered like SAVE ,file name will default name "SAVEDGAME.TXT"
                    if(token.length()>=1 && token !=" ")    flag =saveFile(board,size,playerChoice,token); //save game with filename  
                }
                if(flag == 0 && token.length()>=1 && token !="     ") // checking save and output saved success
                    cout<<endl<<">>> Saved file Name :"<<token<<endl<<">>> You can continue..."<<endl;
                else if(flag ==0)   cout<<endl<<">>> Saved File Name :"<<"SAVEDGAME.TXT "<<endl<<">>> You can continue..."<<endl; //default name print
                printBoard(board,size);
                    
                }else if(find == key2){ // if first 4 char egual key2(LOAD) loadFile function will start.
                    loadName =inputUser.substr(5,inputUser.length()); // load name is keeping user's entered file name 
                    flag3 = loadFile(board,size,playerChoice,loadName); // file loading
                    if(flag3==0)    cout<<endl<<">>> Loaded File Name :"<<loadName<<endl<<">>> You can continue..."<<endl; // success loaded print
                    printBoard(board,size);
                }   
                if( find == key1 || find == key2)   cout<<"Player1 (X), please select between columns : "; // after save or load, again user input
                else cerr<<"Invalid column!! Player1 (X), please select between columns :"; // if user hasn't entered SAVE OR LOAD, print will be  error
                getline(cin,inputUser);
                if(inputUser.length()==1) moveColumn =(char)inputUser[0]; // assignment user column letter choice  
                
            }while(inputUser.length() > 1 || inputUser ==" " || inputUser.length() == 0 ); // user input check
        } //if end
        //Checking column is full or empty && Checking correct column letter
        if(checkColumnFull(board,size,moveColumn) == 1 || letterCorrectCheck(moveColumn,size) == 2){ 
            //if column is full or letter is wrong, while loop will continue until p1 enter correct column, letter
            do  {
                if(checkColumnFull(board,size,moveColumn) == 1)
                    cerr<<"Column is full!! Player1 (X) , please select between columns : ";
                if(letterCorrectCheck(moveColumn,size) == 2) 
                    cerr<<"Invalid column!! Player1 (X), please select between columns : ";
                getline(cin,inputUser);
                moveColumn =inputUser[0];
            }while(checkColumnFull(board,size,moveColumn) == 1 || letterCorrectCheck(moveColumn,size) == 2 );                   
        }//if end
        //selectColumnNumber is produce column number according to entered letters
        //column number is keeping column number, minesRow is keeping column how many letters are in the column.
        int columnNumber=0,minesRow = 0;
        columnNumber = selectColumnNumber(board,size,moveColumn,columnNumber,minesRow);
        // row1 is  keeping which row should be change according to how man letters are in the column.
        int row1 = size-minesRow-1;
        if(row1>=0 ){
            if(board[row1][columnNumber] =='.' && inputUser.length()==1){ // According to p1 entered, this column will be 'X'
                board[row1][columnNumber] = 'X'; 
                printBoard(board,size);
            }    
            if(checkWinner(board,size,row1,columnNumber,letterUser1)==1){  // checking p1 won or not 
                cout<<"!!!!! Congratulations  Player1 (X). You have won !!!!! "<<endl;
                checkWinner(board,size,row1,columnNumber,letterUser1);
                printBoard(board,size);
                exit(-1);
            }
            if(checkWinner(board,size,row1,columnNumber,letterUser1) == 3 ){ // checking board full  or empty 
                cout<<"!!!!! No a winner. Board is full !!!!! "<<endl;
                printBoard(board,size);
                exit(-1);
            }
        }//row1>=0 end
        else fillUserSelect(board,size,playerChoice); 
/* -------------------- Player2 start-------------------*/ 
        char moveColumn1,letterUser2 ='O'; //letterUser2 will use for check win function
        string inputUser2;
        if(playerChoice == 'p' || playerChoice == 'P'){     //if user choice p, p2 will play and enter column choice
            do  {
                cout<<"Player2 (O) , please select between columns : "; //Player2 column choice, until enter correct format
                getline(cin,inputUser2);
                if(inputUser2.length()== 0) cerr<<"Invalid column!! Player2 (O), please select between columns"<<endl; //empty control 
            }while(inputUser2 == " " || inputUser2.length() == 0);  //  input space or empty control 
        }        
        if(inputUser2.length()==1 && inputUser != " ") moveColumn1 = inputUser2[0]; // user selected letter assignment
        
        int flag2,flag4;
        if(inputUser2.length() > 1){ // if string >1 , we assume user maybe entered load or save
            do  {
                find =inputUser2.substr(0,inputUser2.find(split));  //Separate input until find space
                if(find == key1){   // if first 4 char egual key1(SAVE) saveFile function will start
                    if(inputUser2.length()== 4) flag2 = saveFile(board,size,playerChoice);  //save game if user enter SAVE
                    if(inputUser2.length()>4){  
                        token =inputUser2.substr(5,inputUser2.length());
                        if(token.length()==0) saveFile(board,size,playerChoice); //if there is a space entered like SAVE ,file name will default name "SAVEDGAME.TXT"
                        if(token.length()>=1 && token !=" ")    flag2 =saveFile(board,size,playerChoice,token); //save if user enter filename
                    }
                    if(flag2 == 0 && token.length()>=1 && token !="     ")
                         cout<<endl<<">>> Saved file Name :"<<token<<endl<<">>> You can continue..."<<endl;
                    else if(flag2 ==0)  cout<<endl<<">>> Saved File Name :"<<"SAVEDGAME.TXT "<<endl<<">>> You can continue..."<<endl;
                    printBoard(board,size);
                }
                else if(find == key2){ // if first 4 char EQUAL key2(LOAD) loadFile function will start.
                     loadName =inputUser2.substr(5,inputUser2.length()); // load name is keeping user's entered file name 
                     flag4 = loadFile(board,size,playerChoice,loadName); // file loading
                     if(flag4==0)   cout<<endl<<">>> Loaded File Name :"<<loadName<<endl<<">>> You can continue..."<<endl;
                     printBoard(board,size);
                }
                if( find == key1 || find == key2)   
                    cout<<"Player2 (O), please select between columns : "; // after save or load, again user input
                else cerr<<"Invalid column!! Player2 (O), please select between columns :";     // if user hasn't entered SAVE OR LOAD, print will be  error
                getline(cin,inputUser2);
                if(inputUser2.length()==1) moveColumn1 =(char)inputUser2[0]; // assignment user column letter choice  
                
            }while(inputUser2.length() > 1 || inputUser2 ==" " || inputUser.length() == 0);     // user input check
        }//if end
        //if user choice c, moveComputer will produce a letter and moveColumn1 will keep 
        if(playerChoice == 'c' || playerChoice == 'C'){ 
            moveColumn1 = moveComputerSelect(board,size);
            cout<<"Choice of Computer : "<<moveColumn1<<endl;    
        }
        if(checkColumnFull(board,size,moveColumn1) == 1 || letterCorrectCheck(moveColumn1,size) == 2){ //Checking column is full or empty 
            //if column is full or letter is wrong, while loop will continue until p2 enter correct column, letter 
            do  { 
                if(checkColumnFull(board,size,moveColumn1) == 1) 
                    cerr<<"Column is full!! Player2 (O) , please select correct column : ";
                if(letterCorrectCheck(moveColumn1,size) == 2)  
                    cerr<<"Invalid column! Player2 (O) , please select correct column : ";  
                getline(cin,inputUser2);
                moveColumn1 =inputUser2[0];
                
            }while(checkColumnFull(board,size,moveColumn1) == 1 || letterCorrectCheck(moveColumn1,size) == 2);  
        }
        //selectColumnNumber is produce column number according to entered letters and column number is keeping column number
        columnNumber = selectColumnNumber(board,size,moveColumn1,columnNumber,minesRow);
         // row2 is  keeping which row should be change according to how man letters are in the column.
        int row2 = size-minesRow-1;
        if(row2>=0 ){
            if(board[row2][columnNumber] =='.'){ 
                board[row2][columnNumber] = 'O'; // According to p2 entered, this column will be 'O'
                printBoard(board,size);
            } 
            if(checkWinner(board,size,row2,columnNumber,letterUser2) == 1 ){ // checking p2 or C won or not
                    // if user entered P and p2 won
                if(playerChoice == 'p' || playerChoice == 'P'){
                    cout<<"!!!!! Congratulations  Player2 (O). You have won !!!!!"<<endl;
                    checkWinner(board,size,row2,columnNumber,letterUser2);
                    printBoard(board,size);
                    exit(-1); 
                }
                // if user entered C and C won
                if(playerChoice == 'c' || playerChoice == 'C'){
                    cout<<"!!!!! Computer won !!!!!"<<endl;
                    checkWinner(board,size,row2,columnNumber,letterUser2);
                    printBoard(board,size);
                    exit(-1);
                }
            }  // checking board full  or empty 
            if(checkWinner(board,size,row2,columnNumber,letterUser2) == 3 ){
                cout<<"!!!!! No a winner. Board is full !!!!!  "<<endl;
                printBoard(board,size);
                exit(-1);
            }
        } // if row>2=0 end 
        else fillUserSelect(board,size,playerChoice); 
        /* -------------------- Player2 end-------------------*/ 
             cin.clear();
    }//while end
} 
/*-----------end of fillUserSelect--------------*/
int selectColumnNumber(char board[][MAX_SIZE], int size,char columnSelect, int numberColumn, int & columnSum){
    int columnNumber = letterColumnNumber(columnSelect), count1 = 0; //listColumn is produce column number
    
    for(int i = size; i>=0; i--) //column is counting how many X or O there are
        if(board[i][columnNumber] == 'X' || board[i][columnNumber] == 'O') count1++;          
    if(columnSum < size) columnSum = count1;    // if column < size, column will be count1 and will return
    return  columnNumber;
}
/*-----------end of selectColumnNumber----------*/
char moveComputerSelect(char board[][MAX_SIZE], int size){
    char arr[MAX_SIZE],move;    //arr array will keep letter according to entered size. move is keeping computer select letter
    int letterNum = 97,count =0;
    
    for(int i = 0; i < size ; i++){  
        arr[i] = letterNum; //assignment letters according to entered size
        letterNum++;
        count++;
    }
    int count1 =0,count2=0,count3=0,count4=0,column=0; //counts will count how many X there are if they entered consecutive 3 times vertical or horizontal
    
    move =arr[rand()%count]; // random will select a letter in array;
    for(int i =size-1; i >= 0; i--){ 
        for(int j =0 ; j<size; j++){
            if(board[i][j] == 'X'){
                for(int k = 0; k < 4; k++){
                    if(board[i][j+k] == 'X' && j+k < size ){ 
                    count1++;  
                    }
                    if(count1 ==3){
                    count2 = count1;
                    if(board[i][j+k+1] == '.' && j+k+1 < size ) column = j+k;
                    //column will keep column number if there are 3 times 'X' horizontal
                    }   
                }
            count1=0;
            }
        }
    }
    if(count2 == 3) move =(char)column+97; // if there are 3 times 'X' horizontal, computer letter will be according to column number +97
    for(int i =size-1; i >= 0; i--){ 
        for(int j =size-1 ; j >= 0; j--){
            if(board[j][i] == 'X'){
                for(int k = 0; k < 4; k++){
                    if(board[j-k][i] == 'X' && j-k >=0 ) 
                        count3++;  
                    if(count3 ==3){
                    count4 = count3;
                        if(board[j-k-1][i] == '.' && j-k-1 >=0 )
                            column = i; 
                    }       //column will keep column number if there are 3 times 'X' vertical
                }
                        count3=0;
            }
        }
    }
    if(count4 == 3) move=column+97; // if there are 3 times 'X' vertical, computer letter will be according to column number +97
    if(checkColumnFull(board,size,move) == 1){ // if selected column is full, move will change until find a '.';
        for(int i =0; i<size; i++){ 
            for(int j =0 ; j<size; j++){
                if(board[i][j] == '.'){    
                    decltype(move)newlet; //decltype example;
                    newlet = j+97;
                    move =newlet;  
                }
            }
        }
    }
    return move;
}
/*-----------end of moveComputerSelect----------*/
int letterCorrectCheck(char letterSelect, int size){
    auto firstnum1= 65,firstnum2=97,flag = 0;
    
    for(int i = 0; i < size ; i++){  //assignment letter
        if(letterSelect == firstnum1 || letterSelect == firstnum2 )
            flag = 1;
            firstnum1++;
            firstnum2++;
    }
    if(flag == 1) return 1;
    else return 2;
    
    return 0;
}
/*-----------end of letterCorrectCheck----------*/
int checkColumnFull(char board[][MAX_SIZE], int size,char letterColumn){
    int column =letterColumnNumber(letterColumn), count = 0;
    
    for(int i =0; i < size; i++){
        if(board[i][column] == 'X' || board[i][column] == 'O') 
            count++;          
    }
    if(count == size) return 1;
        else return 0;
}
/*-----------end of checkColumnFull-------------*/
int checkWinner(char board[][MAX_SIZE], int size, int row, int column, char letterUser){
    int count1 = 0, count2 = 0,count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0,
        count9 = 0, count10 = 0, count11=0,count12 =0, count13=0; // counts will count X or O according to selected row and column
    
    for(int i=0; i<4; i++){
        if( row+i < size && board[row+i][column] == letterUser) count1++; 	// vertical count     
        if( column-i >= 0 && board[row][column-i] == letterUser) count2++;	// horizontal count xxx-                     
        if( column+i < size && board[row][column+i] == letterUser) count3++;	// horizontal count -xxx 
        if(column+i-1 >= 0 && column+i-1 < size && board[row][column+i-1] == letterUser) count4++; // horizontal count x-xx                      
        if(column+i-2 >= 0 && column+i-2 < size && board[row][column+i-2] == letterUser) count5++; // horizontal count xx-x   
    }
    for(int j = 0; j<4; j++){                                                                                                    
        if(row +j < size && column-j >= 0 && board[row+j][column-j] == letterUser) count6++; // diagonal1 count -xxx
        if(row -j >=0 && column+j < size && board[row-j][column+j] == letterUser) count8++;  // diagonal1 count xxx-
        if(row -j >=0 && column-j >= 0 && board[row-j][column-j] == letterUser) count7++;    // diagonal2 count -xxx       
        if(row+j < size && column+j < size && board[row+j][column+j] == letterUser) count9++;// diagonal2 count xxx-     
    } 
    for(int m = 0; m<=4; m++){ 
        if(row + m -1 < size && row + m -1 >=0 && column+m-1 >=0 && column+m-1 < size && board[row + m - 1][column+m-1] == letterUser) 
            count10++; // diagonal2  count x-xxx   
        if(row + m < size && row + m -1 >=0 && column-m+1 >=0 && column-m-1 < size && board[row + m - 1][column-m+1] == letterUser) 
            count11++; // diagonal1 count x-xxx          
        if(row + m -2 < size &&  row + m -2 >=0 && column+m-2 >=0 && column+m-2 < size && board[row + m - 2][column+m-2] == letterUser) 
            count12++; // diagonal2 count xx-x                     
        if(row + m -2 < size && row + m -2 >=0 && column-m +2 >= 0 && column-m+2 < size && board[row + m - 2][column - m + 2] == letterUser) 
            count13++; // diagonal1 count xx-x      
    }
    // after if there is a won, letters will be small according to letterUser(letterUser 'X' or 'O')
    if(count1 == 4 || count2 == 4 || count3 == 4 || count4 == 4 || count5 == 4 || count6 == 4 || count7 == 4 || count8 == 4 || count9 == 4 || 
    count10 == 4 || count11 == 4 || count12 == 4 || count13 == 4 ){
        for(int k = 0; k <4; k++){
            if(count1 == 4)
                board[row+k][column] = letterUser+' ';              
            if(count2 == 4 && count3 != 4 && count4 != 4 && count5 != 4) 
                board[row][column-k] = letterUser+' ';             
            if(count3 == 4 && count2 != 4 && count4 != 4 && count5 != 4) 
                board[row][column+k] = letterUser+' ';             
            if(count4 == 4 && count5 !=4 ) 
                board[row][column+k-1] = letterUser+' '; 
            if(count5 == 4 ) 
                board[row][column+k-2] = letterUser+' '; 
            if(count6 == 4)
                board[row+k][column-k] = letterUser+' ';              
            if(count7 == 4)
                board[row-k][column-k] = letterUser+' ';            
            if(count8 == 4)
                board[row-k][column+k] = letterUser+' ';             
            if(count9 == 4)
                board[row+k][column+k] = letterUser+' ';          
            if(count10 == 4)
                board[row + k - 1][column+k-1] = letterUser+' ';          
            if(count11 == 4)
                board[row + k - 1][column-k+1] = letterUser+' ';            
            if(count12 == 4)
                board[row + k - 2][column+k-2] = letterUser+' ';           
            if(count13 == 4 && count11 !=4){
                if(board[row + k - 2][column - k + 2] ==letterUser) board[row + k - 2][column - k + 2] = letterUser+' ';
            }
        }
            return 1;
    }
    int countfull = 0;
    
    for( int i = 0 ; i< size ; i++){  //checking game board full or not
        for(int j = 0; j< size ; j++){
            if(board[i][j] !='.') countfull++;
        }
    }
    if(countfull == size*size) 
        return 3; //if full, returned number will be 3  
    return 0;
}
/*-----------end of checkWinner----------*/
int letterColumnNumber(char letter){
    char listlet[MAX_SIZE];
    int column; int letters = 97;
    
    for(int i = 0; i < MAX_SIZE ; i++){ //assignment letters
        listlet[i] = letters;
        letters++;
    }
    for(int i=0; i<MAX_SIZE; i++){ // according to entered letter, listColumn will return column number
        if(listlet[i] == letter || listlet[i]-32 == letter)
            column =i;
    }
    return column;
}
/*-----------end of letterColumnNumber----------*/
int saveFile(const char  board[][MAX_SIZE], const int & size, const char & playerChoice,string fileName){
    ofstream fileWrite;
    
    fileWrite.open(fileName, ios::out); //saved file according to fileName
    if(!fileWrite){
        cerr<<endl<<"Error save file!!!"; //checking file open or not.if not, return will be -1
        return -1;
    }
    fileWrite<<size<<endl; // user's entered board size number will write first line in file.
    fileWrite<<playerChoice<<endl; // user's entered player choice P or C  will write second line in file.
    for(int i = 0; i < size; i++){ // and finally, current board will write in file.
        for(int j = 0; j<size; j++){
            fileWrite<<board[i][j];
        }
        fileWrite<<"\n";
    }
    fileWrite.close();
    return 0;
}
/*-----------end of saveFile----------*/
int loadFile(char board[][MAX_SIZE],int & changeSize, char & changePlayer, string nameOfFile){
    string loadSize,choiceOfPlayer, boardload;
 
    ifstream fileload(nameOfFile,ios::in); // according to user entered file name, file will open
    if(!fileload){
        cerr<<endl<<"Error open file !!!"<<endl; // checking file opening
        return -1;           
    }else{
        
    getline(fileload,loadSize); // first board size reading in first line.
    if(loadSize.length() == 0){
    	cerr<<endl<<"Error open file !!!"<<endl; // checking file opening
        return -1;           
	}
    changeSize =stoi(loadSize); // stoi is a function can do conver a string to an interger.So board size is changing
    getline(fileload,choiceOfPlayer); // player choice reading in file P or C
    changePlayer =choiceOfPlayer[0];
    auto i=0;
        while(getline(fileload,boardload)){ // reading saved board. So board will change.
            for(int j=0; j<changeSize;j++){
              board[i][j]=boardload[j]; 
            }
        i++;    
        }
    }
    fileload.close();
    return 0;
}
/*-----------end of loadFile----------*/
void printBoard(const char board[][MAX_SIZE],const int size){
    char arr[MAX_SIZE]; auto letter = 97;
    // according to entered size, array  will fill letters
    cout<<endl;
    for(int i = 0; i < size ; i++){ //assignment letters
        arr[i] = letter;
        letter++;
    }
    for(int m = 0; m < size ; m++) //print letters
        cout<<arr[m];
    cout<<endl;
    for(int j = 0; j < size; j++){ // print board 
       for(int k = 0; k < size; k++)
           cout<< board[j][k];
           cout<<endl;
     }
    cout<<endl;
}
/*-----------end of printBoard------------------*/
