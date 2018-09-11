// this is file gtusetbase.h for base class

#ifndef GTUSETBASE_H
#define GTUSETBASE_H
#include<iostream>
#include<memory>
#include<string>
using namespace std;

namespace GTUEdu{
    
    template<class T>
    
    class GTUSetBase{
    
        public:
 
       class GTUIterator{  // iterator
           
            public:
		bool operator !=(const GTUIterator& rpoint); // overloads operators
		bool operator ==(const GTUIterator& rpoint);
		GTUIterator& operator++();
                GTUIterator operator++(int val);
		GTUIterator& operator--();
                GTUIterator operator--(int val);
                GTUIterator& operator =(const GTUSetBase& rightSide); 
		T& operator*();
                T* operator->();
              
		private:
        };
         
        typename GTUSetBase<T>::GTUIterator end();      
        typename GTUSetBase<T>::GTUIterator begin();
        typename GTUSetBase<T>::GTUIterator find(const T& el);
        virtual bool empty()const = 0;  // return if true used == 0
        virtual int size()const = 0;  // return used elements size
        virtual int max_size()const =0;  // return maxsize
        virtual void insert(const T& el) =0; // inserts elements in container
        virtual bool erase(const T& value) = 0;  // erase one element
        virtual void clear() = 0;   // make used = 0;
        virtual int count(T value)const = 0; // count called element in the set
        
        
          
        protected:
         
    };
    
    
    
}

#endif