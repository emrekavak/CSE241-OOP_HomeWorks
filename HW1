/* Name = Emre KAVAK && Number = 151044085 && HW1 >> CONNECT FOUR << && Date Sent = 01.10.2017 && Time = 21:00 */

#include<iostream>
#include<cstdlib>
using namespace std;
const int MAX_SIZE = 20 ;

void createBoard(char board[][MAX_SIZE], int& size);
//Precondition : Take input size from user between 4-6...-20
//Postcondition : Create a board according to the entered input
void userSelect(char& choiceUser);
//Precondition : Take letter input from user between P,p or C,c
//Postcondition : according to user input, game will play p v p or p v c
void fillUserSelect(char board[][MAX_SIZE], int size,char playerChoice);
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
void printBoard(char board[][20], int size);
//Precondition : This function take board and size;
//Postcondition : according to board size, board will be printed

int main(){
    int firstSize = 8;
    char firstBoard[MAX_SIZE][MAX_SIZE];
    
    for(int j = 0; j < MAX_SIZE; j++){ // board filling with '.'
        for(int k = 0; k < 20; k++)
            firstBoard[j][k] = '.';
    } 
    cout<<"\n"<<"----- Welcome to Connect Four Game ----- "<<endl;
    // sizeNumber will keep entered size 
    int sizeNumber; 
    createBoard(firstBoard,sizeNumber);
    //user will be according to entered choice P or C
    char user;
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
        cout<<"Invalid size!";
        createBoard(board,sizeNumber); 
    } 
}
/*-----------end of createBoard----------*/
void userSelect(char& choiceUser){
    char let;
    int flag =0;
    
    cout<<"Please enter your choice for play versus Player (P) or Computer (C) : ";
    cin>>let;
    // Checking Correct versus player letter
    if(let == 'p' || let == 'P' || let == 'c' || let == 'C'  ) choiceUser = let;
    else{cout<<endl;
        while(flag == 0){
            cout<<"Invalid letter! Please enter your choice for play versus Player (P) or Computer (C) :";
            cin.clear();
            cin.ignore();
            cin>>let;
            if(let == 'p' || let == 'P' || let == 'c' || let == 'C'  ){ 
            choiceUser = let;
            flag = 1;
            }
        }
    }
}
/*-----------end of userSelect----------*/
void fillUserSelect(char board[][MAX_SIZE], int size, char playerChoice){
    char moveColumn,correntColumn,correntColumn1, letterUser1 ='X';
    
    while(1){
        //Player1 column choice
        cout<<"Player1 (X), please select between columns : ";
        cin>>moveColumn;
        //Checking correct column letter
        while(letterCorrectCheck(moveColumn,size) == 2 ){ 
            cin.clear();
            cin.ignore();
            cout<<"Invalid letter! Player1 (X), please select correct column : ";
            cin>>moveColumn;
        }
        //Checking column is full or empty
        if(checkColumnFull(board,size,moveColumn) == 1){ 
            correntColumn = moveColumn;
            //if column is full or letter is wrong, while loop will continue until p1 enter correct column, letter
            while(checkColumnFull(board,size,correntColumn) == 1 || letterCorrectCheck(correntColumn,size) == 2 ){ 
                if(checkColumnFull(board,size,correntColumn) == 1)
                    cout<<"Column is full!! Player1 (X) , please select between columns : ";
                if(letterCorrectCheck(correntColumn,size) == 2) 
                    cout<<"Invalid column!! Player1 (X), please select between columns : ";
                cin>>correntColumn;   
            } 
            moveColumn = correntColumn;  
        } 
        //selectColumnNumber is produce column number according to entered letters
        //column number is keeping column number, minesRow is keeping column how many letters are in the column.
        int columnNumber=0,minesRow = 0;
        columnNumber = selectColumnNumber(board,size,moveColumn,columnNumber,minesRow);
        // row1 is  keeping which row should be change according to how man letters are in the column.
        int row1 = size-minesRow-1;
        if(row1>=0 ){
            if(board[row1][columnNumber] =='.'){ // According to p1 entered, this column will be 'X'
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
        char moveColumn1,letterUser2 ='O';;
        if(playerChoice == 'p' || playerChoice == 'P'){ //if user choice p, p2 will play and enter column choice
            cout<<"Player2 (O) , please select between columns : ";
            cin>>moveColumn1;    
        }
        //if user choice c, moveComputer will produce a letter and moveColumn1 will keep 
        if(playerChoice == 'c' || playerChoice == 'C'){ 
            moveColumn1 = moveComputerSelect(board,size);
            cout<<"Choice of Computer : "<<moveColumn1<<endl;    
        }
        while(letterCorrectCheck(moveColumn1,size) == 2 ){ // letter check
            cout<<"Invalid column! Player2 (O) , please select between columns : ";
            cin>>moveColumn1;
            cout<<endl;
        }
        if(checkColumnFull(board,size,moveColumn1) == 1){ //Checking column is full or empty 
            correntColumn1 = moveColumn1;
            //if column is full or letter is wrong, while loop will continue until p2 enter correct column, letter
            while(checkColumnFull(board,size,correntColumn1) == 1 || letterCorrectCheck(correntColumn1,size) == 2){
                if(checkColumnFull(board,size,correntColumn1) == 1) 
                    cout<<"Column is full!! Player2 (O) , please select correct column : ";
                if(letterCorrectCheck(correntColumn1,size) == 2)  
                    cout<<"Invalid column! Player2 (O) , please select correct column : ";
                    cin>>correntColumn1;
            }
            moveColumn1 = correntColumn1;
        } // if end
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
    }//while end
} 
/*-----------end of fillUserSelect--------------*/
int selectColumnNumber(char board[][MAX_SIZE], int size,char columnSelect, int numberColumn, int & columnSum){
    //listColumn is produce column number
    int columnNumber = letterColumnNumber(columnSelect);
    int count1 = 0;
    //column is counting how many X or O there are
    for(int i = size; i>=0; i--){
        if(board[i][columnNumber] == 'X' || board[i][columnNumber] == 'O') count1++;          
    }
    // if column < size, column will be count1 and will return
    if(columnSum < size) columnSum = count1;
    return  columnNumber;
}
/*-----------end of selectColumnNumber----------*/
char moveComputerSelect(char board[][MAX_SIZE], int size){
    //arr array will keep letter according to entered size. move is keeping computer select letter
    char arr[20],move;
    int letterNum = 97,count =0;
    
    for(int i = 0; i < size ; i++){  
        arr[i] = letterNum; //assignment letters according to entered size
        letterNum++;
        count++;
    }
    //counts will count how many X there are if they entered consecutive 3 times vertical or horizontal
    int count1 =0,count2=0,count3=0,count4=0,column=0;
    
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
                        if(board[i][j+k+1] == '.' && j+k+1 < size )
                            column = j+k;
                        //column will keep column number if there are 3 times 'X' horizontal
                    }   
                }
            count1=0;
            }
        }
    }
    // if there are 3 times 'X' horizontal, computer letter will be according to column number +97
    if(count2 == 3) move = (char)(column+97);
    
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
    // if there are 3 times 'X' vertical, computer letter will be according to column number +97
    if(count4 == 3) move = (char)(column+97);
    // if selected column is full, move will change until find a '.';
    if(checkColumnFull(board,size,move) == 1){
        for(int i =0; i<size; i++){ 
            for(int j =0 ; j<size; j++){
                if(board[i][j] == '.'){    
                    column = j;
                    move = (char)(column+97);
                }
            }
        }
    }
    return move;
}
/*-----------end of moveComputerSelect----------*/
int letterCorrectCheck(char letterSelect, int size){
    int firstnum1= 65,firstnum2=97,flag = 0;
    
    for(int i = 0; i < size ; i++){  //assignment letter
        if(letterSelect == firstnum1 || letterSelect == firstnum2 )
            flag = 1;
            firstnum1++;
            firstnum2++;
    }
    if(flag == 1) 
        return 1;
    else 
        return 2;
    return 0;
}
/*-----------end of letterCorrectCheck----------*/
int checkColumnFull(char board[][MAX_SIZE], int size,char letterColumn){
    int column =letterColumnNumber(letterColumn), count = 0;
    
    for(int i =0; i < size; i++){
        if(board[i][column] == 'X' || board[i][column] == 'O') 
            count++;          
    }
    if(count == size) 
        return 1;
    else 
        return 0;
}
/*-----------end of checkColumnFull-------------*/
int checkWinner(char board[][MAX_SIZE], int size, int row, int column, char letterUser){
    // counts will count X or O according to selected row and column
    int count1 = 0, count2 = 0,count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0,
        count9 = 0, count10 = 0, count11=0,count12 =0, count13=0;
    
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
    for(int m = 0; m<4; m++){ 
        if(row + m -1 < size && row + m -1 >=0 && column+m-1 >=0 && column+m-1 < size && board[row + m - 1][column+m-1] == letterUser) 
            count10++; // diagonal2  count x-xxx   
        if(row + m < size && row + m -1 >=0 && column+m+1 >=0 && column+m-1 < size && board[row + m - 1][column-m+1] == letterUser) 
            count11++; // diagonal1 count x-xxx          
        if(row + m -2 < size &&  row + m -2 >=0 && column+m-2 >=0 && column+m-2 < size && board[row + m - 2][column+m-2] == letterUser) 
            count12++; // diagonal2 count xx-x                     
        if(row + m -2 < size && row + m -2 >=0 && column-m +2 >= 0 && column-m+2 < size && board[row + m - 2][column - m + 2] == letterUser) 
            count13++; // diagonal1 count xx-x      
    }
    // after if there is a won, letters will be small according to letterUser(letterUser 'X' or 'O')
    if(count1 == 4 || count2 == 4 || count3 == 4 || count4 == 4 || count5 == 4 || count6 == 4 || count7 == 4 || count8 == 4 || count9 == 4 || 
    count10 == 4 || count11 == 4 || count12 == 4 || count13 == 4 ){
        for(int k = 0; k < 4; k++){
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
            if(count13 == 4)
                board[row + k - 2][column - k + 2] = letterUser+' ';       
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
    int column;
    // according to entered letter, listColumn will return column number
     switch(letter){
        case 'A' :
        case 'a' :  column = 0; break;
        case 'B' :
        case 'b' :  column = 1; break;                 
        case 'C' :
        case 'c' :  column = 2; break;                 
        case 'D' :
        case 'd' :  column = 3; break;               
        case 'E' :
        case 'e' :  column = 4; break;                 
        case 'F' :
        case 'f' :  column = 5; break;                  
        case 'G' :
        case 'g' :  column = 6; break;                
        case 'H' :
        case 'h' :  column = 7; break;             
        case 'I' :
        case 'i' :  column = 8; break;                 
        case 'J' :
        case 'j' :  column = 9; break;                 
        case 'K' :
        case 'k' :  column = 10; break;                  
        case 'L' :
        case 'l' :  column = 11; break;                    
        case 'M' :
        case 'm' :  column = 12; break;          
        case 'N' :
        case 'n' :  column = 13; break;                 
        case 'O' :
        case 'o' :  column = 14; break;         
        case 'P' :
        case 'p' :  column = 15; break;               
        case 'Q' :
        case 'q' :  column = 16; break;                 
        case 'R' :
        case 'r' :  column = 17; break;                   
        case 'S' :
        case 's' :  column = 18; break;              
        case 'T' :
        case 't' :  column = 19; break;
    }
    return column;
}
/*-----------end of letterColumnNumber----------*/
void printBoard(char board[][MAX_SIZE], int size){
    char arr[20]; int letter = 97;
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
