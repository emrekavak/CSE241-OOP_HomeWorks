/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include<iostream>
#include"gtumap.h"
#include<string>
#include<memory>
#include<utility>
using namespace std;
namespace GTUEdu{
     
    template<class K, class V>
    V& GTUMap<K,V>::operator[](const K& k){
       
     	for(int j = 0; j< this->used+1;j++){ // checking k there is or no in the map container					
                if(this->p.get()[j].first==k){
                            
                    return GTUSet<pair<K,V>>::p.get()[j].second;  // if there is return will be second element	
                                
                }	
        }
        
    GTUSet<pair<K,V>>::p.get()[this->used].first=k;  // if there isnt k in the container, yeni yer alınıcak
    this->used++ ;   // used ++ because new element add
    this->bubSort(this->used);  // sort function call
    
    return this->p.get()[this->used-1].second;  // second element return after k add
   
    }
}
