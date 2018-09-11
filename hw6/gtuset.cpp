#include <iostream>
#include <memory>
#include"gtuset.h"
#include<utility>
#include<string>
using namespace std;

namespace GTUEdu{
    
    template<class T>
    GTUSet<T>::GTUSet():used(0),cap(10){ // default constructor
        shared_ptr<T>p{new T[cap],default_delete<T[]>()};  // yeni yer alıyor
    }
    
    template<class T>
    GTUSet<T>::GTUSet(T numCap){ // one parameter constructor

        if(numCap<= 101){  // checking maxSize
            cap = numCap;
            shared_ptr<T>p{new T[cap],default_delete<T[]>()};  // numcapa göre yeni yer alıyor
            used=0;
        } else {
            cout<<"cap exceed"<<endl; 
            throw 1;  // if mazSize exceeded throw 
        }
    }

    template<class T>
    GTUSet<T>::GTUSet(const GTUSet<T>& gtuSetOb): cap(gtuSetOb.getNumCap(), // assignment information
                                                  used(gtuSetOb.getNumUsed())){ // copy constructor
        if(cap<= 90){
            shared_ptr<T>p{new T[cap],default_delete<T[]>()}; // yeni yer alıyor
            for(int i = 0; i< used; i++){
                p.get()[i]=gtuSetOb.get()[i]; // copy information
            }
        }
    }
    
    template<class T>
    GTUSet<T>::GTUIterator::GTUIterator(){  // GTUIterator default constructor
        it=nullptr;
    }
    
    template<class T>
    GTUSet<T>::GTUIterator::GTUIterator(T* rvalue){  // Iterator one parameter constructor
            it=rvalue;
    }
    
    template<class T>
    int GTUSet<T>::getNumUsed()const{
        return used;
    }
    
    template<class T>
    int GTUSet<T>::getNumCap()const{
        return cap;
    }
    
    template<class T>
    bool GTUSet<T>::empty()const{
        if(used == 0) return true;
        if(used > 0) return false;
    }
    
    template<class T>
    int GTUSet<T>::size()const{
         return used;
    }
    
    template<class T>
    int GTUSet<T>::max_size()const{
        return maxSize;
    }
    
    template<class T>
    void GTUSet<T>::insert(const T& el){  // insert one element in container

        int flag = 0;
        for(int i = 0; i< used; i++)   // checking element there is or not in container
                if(p.get()[i] == el) flag = 1;  // if there is, element will not add
        
        if(cap+1<=maxSize){  // checking maxsize
            if(used>=cap){ // if there is no cap

                shared_ptr<T>temp1(new T[cap+1],default_delete<T[]>());// for temp
                 for(int i=0; i<cap;i++){  // assignment new information
                    temp1.get()[i]=p.get()[i];
                }
                cap++; // cap increment
                shared_ptr<T>a1(new T[cap+1],default_delete<T[]>()); // for copy p
                p=a1;
                for(int m=0; m<cap;m++)
                    p.get()[m]=temp1.get()[m];       
            }
        }
        else {
                cout<<"maxsize exceed"<<endl;
                throw 1;
            }
        if( flag == 0 && cap<=maxSize ) {
            p.get()[used]=el; // new element add array
            used++; // used ++
        }
        flag = 0;
        bubSort(used);  // sorting function call
    }
    
    template<class T>
    bool GTUSet<T>::erase(const T& value){  // erasae one element from container
        
    shared_ptr<T>backup(new T[cap],default_delete<T[]>());  // for copy

    int bacindex = 0, k=0, u=0;
        for(int i = 0; i<cap; i++){
            if(p.get()[i] == value){
                bacindex = i;
                for(k = 0; k<cap;k++,u++){
                        if(k == bacindex ) u++;
                                backup.get()[k] = p.get()[u]; // erase element doesn't copy


                }

                if(bacindex!=0){ // after erase element
                    used--;    // used --
                    p=backup; // copy new container
                    bubSort(used);  // sort function call
                    return true;
                }
            }
        }
    }
      
    template<class T>
    void GTUSet<T>::clear(){
        used=0;         
    }

    template<class T>
    int GTUSet<T>::count(T value)const{

	for(int i = 0; i<cap; i++){
            if(p.get()[i] == value) return 1;	
	}
	return 0;
    }
    
    template<class T>
    void GTUSet<T>::bubSort(int value){
	
        T temp;
        for(int i=0;i< value;i++){
            for(int j=i+1;j<value;j++){
                if(p.get()[i]>p.get()[j]){  // checking another element
                        temp=p.get()[i];    // temp
                        p.get()[i]=p.get()[j];
                        p.get()[j]=temp;

                }
            }
        }
    }
    
    template<class T>
    T& GTUSet<T>::GTUIterator:: operator*(){ 
        return *it;
    }
    
    template<class T>
    T* GTUSet<T>::GTUIterator:: operator->(){ 
        return it;
    }
    
    template<class T>
    typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator ++(){ //prefix
        it++; 
        return *this;
    }
    
    template<class T>
    typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator ++(int val){ //postfix
        GTUIterator postin(*this);
        it++;
        return postin;
    }
    
    template<class T>
    typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator--(){ //prefix
        it--; 
        return *this;
    }
    
    template<class T>
     typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator--(int val){ //postfix
        int i =*this; 
        it--;
        return i;
    }
    
    template<class T>
    bool GTUSet<T>::GTUIterator::operator !=(const GTUIterator& rpoint){ 
        return it!=rpoint.it;
    }
    
    template<class T>
    bool GTUSet<T>::GTUIterator::operator ==(const GTUIterator& rpoint){ 
        return it==rpoint.it;
    }
    
    template<class T>
    typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator =(const GTUSet& righOb){
        
        used=righOb.used;
        cap=righOb.cap;
        for(int i = 0; i<used;i++){
            p.get()[i]=righOb.get()[i];
        }
        return *this;
    }

    template<class T>
    typename GTUSet<T>::GTUIterator GTUSet<T>::begin(){
        return (p.get());
    }

    template<class T>
    typename GTUSet<T>::GTUIterator GTUSet<T>::end(){
        return p.get()+used;

    }

    template<class T>
    typename GTUSet<T>::GTUIterator GTUSet<T>::find(const T& el){

    int flag = 0;

    for(int i=0; i<cap; i++){
        if(p.get()[i]==el){
                flag=1;
                return GTUSet<T>::GTUIterator(&p.get()[i]);

        }
    }

    if(flag == 0 && cap+1<=90)  return GTUSet<T>::GTUIterator(&p.get()[used]);
    }
    
    template<class T>
    GTUSet<T>::~GTUSet(){
            //empty
    }
}
