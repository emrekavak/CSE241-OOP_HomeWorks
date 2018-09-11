import javafx.util.Pair;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidParameterException;
import java.util.InputMismatchException;
import java.util.Scanner;
/**
 *
 * @author Emre KAVAK
 * Test Class For GTUSetInt, GTUSet and GTUMap
 */
public class Test {
    public static void main(String args[]){
        
    try {
        System.out.println("--------------- GTUSet TEST ---------------");
    GTUSet<Integer> setOb = new GTUSet<Integer>(Integer[].class);
    GTUSet<Integer> setOb2 = new GTUSet<Integer>(Integer[].class);
        System.out.printf("\n--> You can add just %d elements \n",setOb.maxSize()); //maxsize function    
        System.out.printf("--> First Capacitiy = %d\n",setOb.getCap());  // getcap functiob
        System.out.printf("--> First Size = %d\n",setOb.size()); // size function
        
    for(int i = 10; i<=50; i+=10) // insert elements
       setOb.insert(i);
    
    GTUSet<Integer>.GTUIterator it1 = setOb.new GTUIterator(); // iterator olusturuluyor
        System.out.printf("--> Elements added -> [ ");
        while(it1.hasNext())                            // using hasnext  next 
            System.out.printf("%d,",it1.next());       // print gtuset object
        System.out.printf("] . New size = %d \n",setOb.size());  
        
    for(int i = 60; i<=100; i+=10) // insert new elements
        setOb.insert(i);

    it1=setOb.begin(); // iteratore setOb objesinin baslangıcı tekrar atanıyor
        System.out.printf("--> New Elements added -> [ ");
        while(it1.hasNext())                                // hasnext ve next fonksıyonları kullanılıyor
            System.out.printf("%d,",it1.next());    
        System.out.printf("] . New size = %d , New Capacitiy = %d\n",setOb.size(), setOb.getCap()); 
        
    setOb.erase(20);   // erase metod called
    setOb.erase(60);
    it1=setOb.begin(); // iteratore setOb objesinin baslangıcı tekrar atanıyor
    
        System.out.printf("--> After erase ( 20,60 ) -> [ ");
        while(it1.hasNext())                                // hasnext ve next metodlar kullanılıyor
            System.out.printf("%d,",it1.next());    
        System.out.printf("] . New size = %d\n",setOb.size());  
        
        System.out.printf("--> Find(10) test =");   // find metod called
        if(setOb.find(10)!=null) 
            System.out.printf(" Yes, there is\n");
        else
            System.out.printf(" No, there isn't\n");
        
        System.out.printf("--> Find(101) test =");
        if(setOb.find(101)!=null) 
            System.out.printf(" Yes, there is\n");
        else
            System.out.printf(" No, there isn't\n");    
        System.out.printf("--> Count 50 = %d\n", setOb.count(50));  // count metod
        System.out.printf("--> Count 20 = %d\n", setOb.count(20));
        
        setOb.clear();  // clear function called
        it1=setOb.begin();   // iteratore setOb objesinin baslangıcı tekrar atanıyor
    
        System.out.printf("--> After clear set -> [ ");
        while(it1.hasNext())                            
            System.out.printf("%d,",it1.next());    
        System.out.printf("] . New size = %d ,",setOb.size()); 
        System.out.printf(" Empty test = %b \n",setOb.empty());
        
    GTUSetInt<Integer> setıntOb = new GTUSet<Integer>(Integer[].class); //GTUSetInt object creating
    it1=setOb.begin();  // assignment iterator

    System.out.printf("\n-----Intersection Test-----\n ");
    
    for(int i = 0; i<=10; i++) // insert setob new elements
        setOb.insert(i);
    
    for(int k = 6; k<=14; k+=2) // insert setInt new elements
        setıntOb.insert(k);
    
    System.out.printf("\n--> Set -> [ ");
        while(it1.hasNext())    // hasnext ve next fonksıyonları kullanılıyor
            System.out.printf("%d,",it1.next());    
        System.out.printf("] . New size = %d ,",setOb.size()); 
   
    GTUSet<Integer>.GTUIterator it2 = setOb.new GTUIterator(); 
        
    GTUSetInt<Integer> setıntOb2;
    setıntOb2=setOb.intersection(setıntOb);  // intersection funksiyonu yeni ollusturulan objeye atanıyor
    it2=(GTUSet.GTUIterator)setıntOb.begin();
        
        System.out.printf("\n--> GTUSetInt -> [ ");
        while(it2.hasNext())  // hasnext ve next fonksıyonları kullanılıyor
            System.out.printf("%d,",it2.next());    
        System.out.printf("] . New size = %d ,",setıntOb.size()); 
  
    it2=(GTUSet.GTUIterator)setıntOb2.begin();     // iterator casting islemi
        System.out.printf("\n--> Intersection -> [ ");
        while(it2.hasNext())     // hasnext ve next fonksıyonları kullanılıyor
            System.out.printf("%d,",it2.next());    
        System.out.printf("] . New size = %d ,\n",setıntOb2.size()); 
        
       System.out.println("\n--------------- END OF GTUSet TEST ---------------");
     
   

    
       System.out.println("\n--------------- GTUMap TEST ---------------");
       
    GTUMap<String, Integer>mapOb = new GTUMap<String, Integer>(Pair[].class);   // map objec creating
    GTUMap<String, Integer>.GTUIterator mapit =mapOb.new GTUIterator();        // map iterator creating
        System.out.printf("\n--> You can add just %d elements \n",mapOb.maxSize()); // maxsize
        System.out.printf("--> First Capacitiy = %d\n",mapOb.getCap());   // getcap funtion
        System.out.printf("--> First Size = %d\n",mapOb.size());   // size function
        
    javafx.util.Pair<String, Integer>ob1 = new javafx.util.Pair<>("Emre",34);  // pair object creating for map object insert
    javafx.util.Pair<String, Integer>ob2 = new javafx.util.Pair<>("Burcu",15);
    javafx.util.Pair<String, Integer>ob3 = new javafx.util.Pair<>("Deniz",40);
    javafx.util.Pair<String, Integer>ob4 = new javafx.util.Pair<>("Lale",90);
    javafx.util.Pair<String, Integer>ob5 = new javafx.util.Pair<>("Murat",11);
    javafx.util.Pair<String, Integer>ob6 = new javafx.util.Pair<>("Ugur",40);
    javafx.util.Pair<String, Integer>ob7 = new javafx.util.Pair<>("Mustafa",11);
    javafx.util.Pair<String, Integer>ob8 = new javafx.util.Pair<>("Hulya",71);
    javafx.util.Pair<String, Integer>ob9 = new javafx.util.Pair<>("Hakan",70);    

    mapit = mapOb.begin();  // iterator begin assigment
    mapOb.insert(ob1);  // map insert function using
    mapOb.insert(ob2);
    mapOb.insert(ob3);
    mapOb.insert(ob4);
    mapOb.insert(ob5);
        
        System.out.printf("--> Map Elements added -> [ ");    // print map object elements
        while(mapit.hasNext())                                
                System.out.printf("%s,",mapit.next());    
        System.out.printf("] . New size = %d \n",mapOb.size()); // size function
        System.out.printf("--> Accessing with at[Emre]  = %d\n",mapOb.at("Emre")); // at() method using 
        System.out.printf("--> Accessing with at[Lale]  = %d\n",mapOb.at("Lale"));
    mapit=mapOb.begin();    // assingment iteratır
    mapOb.erase("Lale",90); // erase method using
        System.out.printf("--> After erase ( Lale,40 ) -> [ ");
        while(mapit.hasNext())                                
            System.out.printf("%s,",mapit.next());    
        System.out.printf("] . New size = %d\n",mapOb.size()); 
        
    mapOb.insert(ob6);  // insert method using for map object
    mapOb.insert(ob7);
    mapOb.insert(ob8);
        mapit=mapOb.begin(); // iterator assignemnt
        System.out.printf("--> New Map Elements added -> [ ");
        while(mapit.hasNext())                                
                System.out.printf("%s,",mapit.next());    
        System.out.printf("] . New size = %d \n",mapOb.size());
        
        System.out.printf("--> Find(Ugur,40) test =");
        if(mapOb.find(ob6)!=null) // find method called
            System.out.printf(" Yes, there is\n");
        else
            System.out.printf(" No, there isn't\n");
       
        System.out.printf("--> Find(hakan,70) test =");
        if(mapOb.find(ob9)!=null)  // find method called
            System.out.printf(" Yes, there is\n");
        else
        System.out.printf(" No, there isn't\n");
        
        System.out.printf("--> Count (Emre,34) = %d\n", mapOb.count(ob1)); // count method called
        System.out.printf("--> Count (Deniz,90)= %d\n", mapOb.count(ob4));
        
    mapit=mapOb.begin();  /// iterator assingment begin
    mapOb.clear(); // clear function called
        System.out.printf("--> After clear map -> [ ");
        while(mapit.hasNext())                                // hasnext ve next fonksıyonları kullanılıyor
            System.out.printf("%d,",mapit.next());    
        System.out.printf("] . New size = %d ,",mapOb.size()); 
        System.out.printf(" Empty test = %b \n",mapOb.empty());
    
        System.out.println("\n-----Intersection Test----- \n");

    GTUSetInt mop2 = new GTUMap<String, Integer>(Pair[].class) ;  // new gtusetınt element creating
    mop2.insert(ob1);  // gtusetınt insert elements
    mop2.insert(ob2);
    mop2.insert(ob3);
    mop2.insert(ob5);
    mop2.insert(ob6);
    mop2.insert(ob7); 
     
    mapOb.insert(ob6);  // new elements adding for intersection test
    mapOb.insert(ob1);
    mapOb.insert(ob5);
    mapOb.insert(ob4);
    mapOb.insert(ob8);
    mapOb.insert(ob9);
    mapOb.insert(ob4);
         
    mapit=mapOb.begin();  /// iterator assingment begin
        System.out.printf("--> Map Elements added -> [ ");
        while(mapit.hasNext())                              
                System.out.printf("%s,",mapit.next()); 
        System.out.printf("] . New size = %d \n",mapOb.size());
        
    GTUMap<String, Integer>.GTUIterator mapit2 =mapOb.new GTUIterator();
    mapit2=(GTUMap.GTUIterator)mop2.begin();  // casting gtumap iterator for gtusetınt iterator
        
        System.out.printf("--> GTUSetInt -> [ ");
        while(mapit2.hasNext())                              
          System.out.printf("%s,",mapit2.next());    
        System.out.printf("] . New size = %d ,",mop2.size()); 
    
    GTUSetInt<javafx.util.Pair<String, Integer>> mop3;
    mop3=mapOb.intersection(mop2);   // gtumap intersection
    mapit2=(GTUMap.GTUIterator)mop3.begin(); // iterator casting
        
        System.out.printf("\n--> Intersection -> [ ");
        while(mapit2.hasNext())                               
            System.out.printf("%s,",mapit2.next());    
        System.out.printf("] . New size = %d ,\n",mop3.size()); 
        System.out.println("\n--------------- END OF GTUMap TEST ---------------");
    }
        catch(InvalidParameterException k){  // catch function call
            System.out.println("Invalid parameter");

        }
    }  
     
}