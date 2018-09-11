/* 
 * Name = EMRE KAVAK && Number = 151044085 && HW5 >> CONNECT FOUR WİTH INHERITANCE << 
 */
#include"connectfourabstract.h" // all header file including
#include"connectfourplus.h"
#include"connectfourdiag.h"
#include"connectfourplusundo.h"
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;
using namespace ConnectFour;

int main(){
    ConnectFourPlus ob1;  // 3 type objects creating 
    ConnectFourPlusUndo ob2;
    ConnectFourDiag ob3;
    int modeFlag=0;
    string mode;
    
    cout<<"\n"<<"----- Welcome to Connect Four Game ----- "<<endl;
    cout<<"\n"<<"* For save game, you should enter SAVE FILENAME."<<endl;
    cout<<"* For load game, you should enter LOAD FILENAME."<<endl;
    cout<<"* For UNDO game, you should enter just UNDO."<<endl;
    cout<<"* Note : You can only LOAD, SAVE or UNDO when choosing a column"<<endl;
    cout<<endl;
    do{ 
        cout<<"Please enter game type between ( Plus (P)- Diagonal (D)- Undo (U) ) :"; //game mode select
        getline(cin,mode);
        if(mode.length()==1)
        if(mode[0] == 'P'|| mode[0] == 'D'|| mode[0] == 'U' ) modeFlag =1;
        if(modeFlag == 0) //game mode control  
            cerr<<"Invalid mode!!"<<endl;
        cout<<endl;
    }while(modeFlag ==0);
    
    char m =mode[0];
    switch(m){
        case 'P':   ob1.setGameMode(m); // game mode save
                    ob1.playGame();     // game starting according to selected mode
                    break;
        case 'D':   ob3.setGameMode(m);
                    ob3.playGame();
                    break;
        case 'U':   ob2.setGameMode(m);
                    ob2.playGame();
                    break;        
    }
    return 0;
}