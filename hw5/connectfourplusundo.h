//This file is the file connectfourplusundo.h 
//This is the interface for the class ConnectFourPlusUndo
#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H
#include "connectfourplus.h"
#include "connectfourabstract.h"
#include<vector>

namespace ConnectFour{
    
    class ConnectFourPlusUndo : public ConnectFourPlus // inherit from ConnectFourPlus
    {
    public:
        ConnectFourPlusUndo(); // default constructor
        ConnectFourPlusUndo(int width, int height); //two parameter constructor
        ConnectFourPlusUndo& operator=(const ConnectFourPlusUndo & righSide); // assignment operator
        ConnectFourPlusUndo(const ConnectFourPlusUndo& otherOb); // copy constructor

        void setVec();  // this function set board size, after user load a file 
        int setBoard(); // if user enter UNDO, this function undo board according to vector saved
                        
        virtual int play(); // this function only play computer and change board 
        virtual int play(const char columnChoice); // this function is  changing board according to parameter only player mode
        virtual int playGame(); // game is playing in here. game mode, width, height etc. getting in this function.
        const int loadFile( const string fileName);  // load file
        const int saveFile( const string fileName);  // save file
        
        ~ConnectFourPlusUndo();
    protected:
        vector<char>saved; // vector is keeping all column choice user's.(a,b,c,d etc.)
                           // after user entered UNDO, vector calling, according to vector the last element,
                           // game board change according to the last move
                           //You can undo game board until beginning of the game.
    };
}


#endif /* CONNECTFOURPLUSUNDO_H */

