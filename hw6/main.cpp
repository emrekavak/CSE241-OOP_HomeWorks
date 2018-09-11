/* 
 * Name = EMRE KAVAK && Number = 151044085 && HW6 >> SET AND MAP CLASS << 
 */

#include<iostream>  // header files included
#include<utility>
#include<memory>
#include<string>
#include"gtusetbase.h"
#include"gtusetbase.cpp"
#include"gtuset.h"
#include"gtuset.cpp"
#include"gtumap.h"
#include"gtumap.cpp"
#include <stdexcept>
using namespace std;
using namespace GTUEdu;

template<class T>
std::shared_ptr<GTUSetBase<T> > setIntersection(const GTUSetBase<T>&, const GTUSetBase<T>&){
    
    shared_ptr<GTUSet<T> >pt(new GTUSet<T>);

    
}
int main(){
        
    GTUSet<int> a;  // creating set object

    try{  // for throw exception
        
    cout<<endl<<"->    Set capacity = "<<a.getNumCap()<<endl<<endl;  // information print
    cout<<"->    Set size = "<<a.size()<<endl<<endl;
    if(a.empty()==true) cout<<"->    Set now empty"<<endl<<endl;

        a.insert(3);  // not ordered elements add
        a.insert(2);
        a.insert(4);
        a.insert(5);
        a.insert(7);
    
    cout<<"->    Adding not ordered elements ( 3,2,4,5,7 )"<<endl<<endl;
    cout<<"->    Set Container =[";   
    
    for(GTUSet<int>::GTUIterator k=a.begin();k!=a.end(); k++) // set container print with GtuIterator k
            cout<<*k<<","; 
    cout<<"]"<<endl<<endl;
    
    cout<<"->    After adding elements Set size = "<<a.getNumUsed()<<endl<<endl;
    cout<<"-----------------------------------------------"<<endl<<endl;
    cout<<"Find function checking elements between (0-10)"<<endl<<endl;
     
    for(int i = 0; i<10; i++){
        if(a.find(i) != a.end())  // find function calling
            cout<<"->    "<<i<<" exist in the set"<<endl;
        else 
            cout<<"->    "<<i<<" isn't exist in the set"<<endl;
    }
    cout<<endl;
    cout<<"-----------------------------------------------"<<endl<<endl;
    
    a.erase(7);  // erase function call
    
    cout<<"After erasing 7"<<endl<<endl;
    cout<<"->    Set container =[";
    for(GTUSet<int>::GTUIterator k=a.begin();k!=a.end(); k++)
            cout<<*k<<","; 
    cout<<"]"<<endl<<endl;
    
    cout<<"Count function calling with 8"<<endl<<endl;
    
    if(a.count(8) == 1) cout<<"->   8 is element in the set just 1"<<endl;  // count function call
    else cout<<"->    8 isn't element in the set"<<endl;

    if(a.count(2) == 1) cout<<"->    2 is element in the set just 1"<<endl;
    else cout<<"->     2 isn't element in the set"<<endl;

    cout<<endl;
    a.clear();  // clear function clear all elements in set

    cout<<"Clear function called"<<endl<<endl;
    cout<<"->    Set =[";
    for(GTUSet<int>::GTUIterator k=a.begin();k!=a.end(); k++)
            cout<<*k<<endl; 
    cout<<"]"<<endl;
    cout<<endl;
    
    for(int i = 0; i<15; ++i)  // new elements adding with exceed capacity
        a.insert(i);
    cout<<"New elements added"<<endl<<endl;
    cout<<"->    New Set =[";
    for(GTUSet<int>::GTUIterator k=a.begin();k!=a.end(); k++)
            cout<<*k<<","; 
    cout<<"]"<<endl;
    
    cout<<"->    New capacity = "<<a.getNumCap()<<endl;
    cout<<"->    New size = "<<a.getNumUsed()<<endl<<endl;
    
    a.erase(3);
    cout<<"After (3) erased"<<endl<<endl;
    cout<<"->    New Set =[";
    for(GTUSet<int>::GTUIterator k=a.begin();k!=a.end(); k++)
            cout<<*k<<","; 
    cout<<"]"<<endl;

    cout<<"->    New size = "<<a.getNumUsed()<<endl<<endl;
    }
    
    catch(int k){  // catch function call
	
		cerr<<"Thrown k Exception...MaxSize exceeded"<<endl;
		
    }
    cout<<"-----------------end of set testing----------------"<<endl<<endl;
    
    try{  // for map container
        
    cout<<"Map Container"<<endl<<endl;
    GTUMap<string,int>::GTUIterator mapit;  // map iterator created
    GTUMap<string,int> mapob;  // map object create
    
    cout<<endl<<"->    Map container capacity = "<<mapob.getNumCap()<<endl<<endl;
    cout<<"->    Map container size = "<<mapob.size()<<endl<<endl;
    if(mapob.empty()==true) cout<<"->    Map container now empty"<<endl<<endl;
    
    cout<<"->    Adding not ordered elments (Aslı,100),(Veli,100),(Emre,80),(Ömer,75),(Ebru,75),(Ali,75)"<<endl<<endl;
    mapob.insert(pair<string,int>("Aslı",90));   // new elements adding with insert function
    mapob.insert(pair<string,int>("Veli",80));
    mapob.insert(pair<string,int>("Emre",100));
    mapob.insert(pair<string,int>("Ömer",75));
    mapob.insert(pair<string,int>("Ebru",65));
    mapob.insert(pair<string,int>("Ali",55));
    
    cout<<"Map Container ="<<endl<<endl;
    for(mapit=mapob.begin(); mapit!=mapob.end();mapit++)  // new elements print
    cout<<"->    [ "<<mapit->first<<" ] = "<<mapit->second<<endl;
    cout<<"->    New size = "<<mapob.getNumUsed()<<endl<<endl;
    
    cout<<endl<<"-----------------------------------------------"<<endl<<endl;
    
    mapob.erase(std::pair<string,int>("Emre",100));   // erase function call
    cout<<"After delete (Emre,100)"<<endl<<endl;
      
    cout<<"Map Container ="<<endl<<endl;   // after erase function call, new elements print
    for(mapit=mapob.begin(); mapit!=mapob.end();mapit++)
    cout<<"->    [ "<<mapit->first<<" ] = "<<mapit->second<<endl;
     
    cout<<"->    New size = "<<mapob.getNumUsed()<<endl<<endl;  // size print 
    cout<<endl<<"İs there (Emre,90) in the container ?"<<endl<<endl;
    if(mapob.find(pair<string,int>("emre",90))!=mapob.end())
        cout<<"->    There is";
    else cout<<"->   There isn't";
    cout<<endl;
     
    cout<<endl<<"İs there (Ömer,75) in the container ?"<<endl<<endl;
    if(mapob.find(pair<string,int>("Ömer",75))!=mapob.end())  // find function call for map object
        cout<<"->    There is";
    else cout<<"->   There isn't";
    cout<<endl;
     
    mapob.clear();  // clear function for map object
    cout<<endl<<"After clear function called ="<<endl<<endl;
    if(mapob.empty()==true) cout<<"->    Map container now empty"<<endl<<endl;
    cout<<"->    Map container size = "<<mapob.size()<<endl<<endl; 
      
    mapob["Kemal"]=50;    // new elements adding with operator []
    mapob["Kemal"]=50;
    mapob["Zeliha"]=60;
    mapob["Ahmet"]=70;
    mapob["Erdem"]=80;
    mapob["Yusuf"]=90;
    mapob["Mustafa"]=90;
    mapob["Harun"]=80;
    mapob["Eren"]=40;
      
    cout<<"New Ordered Map Container ="<<endl<<endl;
    for(mapit=mapob.begin(); mapit!=mapob.end();mapit++)
    cout<<"->    [ "<<mapit->first<<" ] = "<<mapit->second<<endl;
      
    cout<<"->    New Map container size = "<<mapob.size()<<endl<<endl;
    
    cout<<endl<<"Throw exception testing with try 150 capacity container"<<endl;
    GTUSet<int>throwtest(150);  // for test map
    
    }
    catch(int m){
        cerr<<"Thrown k Execption...MaxSize exceeded..."<<endl;  // if capacity exceed, m will be 1   
    }
    cout<<"-----------------end of map testing----------------"<<endl<<endl;
    return 0;   
}
