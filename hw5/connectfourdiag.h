//This is the interface for the class ConnectFourDiag
//This is the file connecfourdiag.h
#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H
#include "connectfourabstract.h"
#include<string>

namespace ConnectFour{
    
    class ConnectFourDiag : public ConnectFourAbstract
    {
        public:
        ConnectFourDiag(); //default constructor
        ConnectFourDiag(int width, int height); //two parameter constructor
        virtual int getcheckWinner(const int rowNum,const int columnNum,const int user); // just diagonal check
        ConnectFourDiag& operator=(const ConnectFourDiag & righSide); // assignment operator
        ConnectFourDiag(const ConnectFourDiag& otherOb); // copy constructor
        ~ConnectFourDiag(); // destructor 
    protected:
     // all data member inherit from base class
    };    
}
#endif /* CONNECTFOURDIAG_H */

