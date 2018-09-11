// this is file gtuset.h for inheritance class,for header file gtuset.cpp

#ifndef GTUSET_H
#define GTUSET_H
#include<iostream>
#include"gtusetbase.h"
#include<memory>
#include<utility>
#include<string>

using namespace std;

namespace GTUEdu{
    
    template<class T>
    
    class GTUSet : public GTUSetBase<T>
    { 
        
        public: 
            
        GTUSet();  //  default constructor
        GTUSet(T numCap);  // with numCal, shared ptr call
        GTUSet(const GTUSet<T>& gtuSetOb);//copy constructor
        int getNumUsed()const; // return used
        int getNumCap()const; // return cap
        int setUsed(){used++;} // will +1 used
        
            class GTUIterator{ // inner class iterator

            public:

            GTUIterator();  // will be it=null ptr 
            GTUIterator(T* rvalue); // it will be it=rvalue
            bool operator !=(const GTUIterator& rpoint); // will return it!=rpoint.it;
            bool operator ==(const GTUIterator& rpoint);// will return it==rpoint.it;
            GTUIterator& operator++();  // prefix increment
            GTUIterator operator++(int val); // postfix increment
            GTUIterator& operator--(); // prefix decreasing
            GTUIterator operator--(int val); // postfix decreasing
            GTUIterator& operator =(const GTUSet& rightSide);  // copy objects
            T& operator*(); // return it
            T* operator->(); // return *it
            protected:
            T *it;

            };
         
	virtual  GTUSet<T>::GTUIterator end(); // iterator end
	virtual  GTUSet<T>::GTUIterator begin(); // iterator begin
	virtual  GTUSet<T>::GTUIterator find(const T& el); // find function
        
        void bubSort(int value);  // for ordered container
        virtual bool empty()const; // return true or false according to used
        virtual int size()const; // return used
        virtual int max_size()const; // return maxSize
        virtual void insert(const T& el); // insert elements in container
        virtual bool erase(const T& value); // erase 1 element from container
        virtual void clear();   // used will be = 0
        virtual int count(T value)const;  // count 1 element in container
        ~GTUSet();
        
        protected:  
  	
        shared_ptr<T>p{new T[100], default_delete<T[]>()};  // for dynamic array
  	int used=0; // for element counts
	int cap; // for cap
        int maxSize=101; // max elements insert number   
    };  
}
#endif