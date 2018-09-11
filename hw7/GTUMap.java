import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Iterator;
import java.security.InvalidAlgorithmParameterException;
import javafx.util.Pair;
import java.lang.Object;
import java.util.Objects;

public class GTUMap<K,V> extends GTUSet<javafx.util.Pair>{
/**
 * 
 * GTUMap one parameter constructor 
 */
    public GTUMap(Class<Pair[]> cls) {
        super(cls);
    }
    /**
     * default constructor
     */
    public GTUMap(){
        super();
    }
    /**
     * @return Value
     */
    public V at(K k){
        
        for(int i = 0; i < this.used; i++){
            if( k == getArr(i).getKey()){ // key arr icinde kontrol ediliyor
                return (V)(getArr(i).getValue()); // eger var ise V tipinde return ediliyor
            }
        }
        return null; 
    }
    /** 
     * parametre elemanı arıyor
     * @return GTUIterator Obje
     */
    public GTUIterator find(Pair k){
        GTUIterator findd =begin();  // ıterator obje yaratılıyor
         while(findd.hasNext()){
            if(findd.next()==k) // eger key var ise , ıterator objesi return edilcek
                return findd;
            } 
        findd=null;  // eger key yok ise, iteratore null atılacak (baska yolunu bulamadım)
        return findd;
    }
    /**
     * 
     * eleman siliyor
     * @return true or false
     */
    public boolean erase(K key,V value) {

        for(int i = 0; i<this.used; i++){
            if(getArr(i).getKey()==key){  // parametre kontol ediliyor  
            this.erase(arr[i]); // eger parametre var ise, gtuset objesi cagırlıyor siliyor
                return true;
            }
        }
    return false;
    }
    /**
     * 
     * 
     * @return GTUSetIn object 
     */
    public GTUSetInt intersection(GTUSetInt obj){ // ortak elemanlardan yeni obje olusturup return ediyor
        GTUMap<K,V> ob1; // map objesi yaratılıyor cast icin
        ob1 =(GTUMap<K,V>)obj; // obje map olarak cast ediliyor
        GTUSetInt ınt1 = new <javafx.util.Pair<K, V>[]> GTUMap(); // yenı gtusetınt objesi yaratılıyor
     
        for(int i = 0; i<used;i++){
            for(int j= 0; j< ob1.used;j++)
                if(this.getArr(i).getKey() == ob1.getArr(j).getKey()){ // ortak eleman kontrolu
                      ınt1.insert(this.getArr(i));  // yeni objeye insert  
             }
        }
        return ınt1;  // GTUSetInt objesi return
    }
}