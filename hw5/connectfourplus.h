//This file is the file connectfourplus.h 
//This is the interface for the class ConnectFourPlus
#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H
#include "connectfourabstract.h"

namespace ConnectFour{
    
    class ConnectFourPlus : public ConnectFourAbstract // doing inheritance class from  ConnectFourAbstract class
    {
    public:
        
        ConnectFourPlus(); // default constructor
        ConnectFourPlus(int width, int height); //two parameter constructor
        virtual int getcheckWinner(const int rowNum,const int columnNum,const int user); // only vertical and horizontal check
        ConnectFourPlus& operator=(const ConnectFourPlus & righSide); // assignment operator
        ConnectFourPlus(const ConnectFourPlus& otherOb); // copy constructor
        ~ConnectFourPlus(); //destructor
        
    protected:
        //all data member using from base class
    };
}
#endif /* CONNECTFOURPLUS_H */

