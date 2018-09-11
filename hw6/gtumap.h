/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gtumap.h
 * Author: emre
 *
 * Created on December 14, 2017, 8:13 PM
 */

#ifndef GTUMAP_H
#define GTUMAP_H
#include<iostream>
#include<string>
#include"gtuset.h"
#include<utility>

using namespace std;

namespace GTUEdu{
    
    template<class K, class V>
    class GTUMap :public GTUSet<std::pair<K,V> >
    {
        public:
     
         //typename GTUMap<K,V>::GTUIterator end();      
	 //typename GTUMap<K,V>::GTUIterator begin();
	 //typename GTUMap<K,V>::GTUIterator find(const K& index);
         
        V& operator[](const K& k);
        private:
            
    };
    
}

#endif /* GTUMAP_H */

