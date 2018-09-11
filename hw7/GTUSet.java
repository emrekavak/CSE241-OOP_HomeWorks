import java.io.PrintStream;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Iterator;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidParameterException;
/**
 * GTUSet impelements GTUSetInt
*/
public class GTUSet<T> implements GTUSetInt<T> {
    
    protected T [] arr ;  // for hold elements
    public int used = 0;  // when a element add, used will incread
    public int cap = 5;   // first cap and will incread according to added element
    public int maxSize = 100; // max add element number
    /**
     * GTUIterator classı
     * index  = for hold index number
     */
    public class GTUIterator implements Iterator<T>{  

        protected int index = 0;  // 
        /**
         * default constructor
         * index=0
         */
        public GTUIterator() {  
            index=0;
        }
        /**
         * one paramter constructor
         * index=indx
         */
        public GTUIterator(int indx) { 
            index=indx;
        }
        public void setİndex(int V){ 
            index=V;
        }
        /**
         * for return next element
         * @return arr[index++];
         */
        public T next(){  
            return arr[index++];
        }
        /**
         * check there is next element
         * @return true or false according to check
         */
        public boolean hasNext(){ 
            if(index < used) return true;
            else return false;
        }
        /**
         * for return previous element
         * @return arr[index];
         */
        public T previous(){  
            if(index > 0) index--;
            return arr[index];
        }
        /**
         * check there is previous element 
         * @return true or false according to check
         */
        public boolean hasPrevious(){ 
            if(index > 0) return true;
            else return false;
        }
       /**
        * for get index
        * @return index
        */
        public int getIndex(){
            return index;
        }  
    } // ıterator end
    /**
     * default consturcotr
     * new arr creat
     */
    public GTUSet(){ 
        used = 0;
        arr = (T[]) new Object[cap];  
    }
    /**
     * 
     * one parameter constuructor
     */
    public GTUSet(Class<T[]> cls){ 
        used = 0;
        arr = cls.cast(Array.newInstance(cls.getComponentType(), cap)); // new arr creat
    }    
    public T getArr(int index){  // for get arr according to index
        return arr[index];   
    }
    public int getCap(){ // return capacite
        return cap;
    }
    public void setArr(int indx,T val){ // for set arr according to index and value
        arr[indx]=val;    
    }
    /**
     * new element index==0 and return first element iterator
     * @return begg (GTUIterator object) 
     */
    public GTUIterator begin(){  
        GTUIterator begg = new GTUIterator(0); 
        return begg;  
    }
    /**
     * new GTUIterator object creating
     * // return object last element +1
     * @return endd (GTUIterator object) 
     */
    public GTUIterator end(){  
        GTUIterator endd=begin(); 
        endd.setİndex(used+1); 
        return endd;
    }
    /**
     * 
     * @return used++ 
     */
    public int setUsed(){ 
        return used++;
    }
    /**
     *   check arr empty or not
     * @return true or false
     */
    public boolean empty(){ 
        if(used == 0) return true;
        else return false;
    }
    public int size() {  // return arr size
        return used;
    }
    public int maxSize() {
        return maxSize;
    }
    /**
     * 
     * for insert element.If there is in the set, no insert will
     */
    /**
     * 
     * @param element 
     */
    public void insert(T element) {
        if(element instanceof GTUSet){
            throw new InvalidParameterException();
        }
        int count = 0, flag = 0;  
        T []backup =(T[]) new Object[cap+1];  // if used>=cap, backup will back arr
 
        if(used+1>cap){  // checking capacity
            for(int j=0; j<used;j++){
                backup[j]=arr[j]; // backup filling with arr elements
                count++;
            }
        arr=(T[]) new Object[cap+1]; // cap+1 yer alıyor
           for(int j=0; j<used;j++){ // yer aldıktan sonra arr icini eskisi ile dolduruyor
                arr[j]=backup[j];
            }
        this.used=count; // used element sayısına esitleniyor
        cap++; // yeni capacite +1
        }
        
        for(int i = 0 ; i< this.used;i++){ // parametre dizide var mı control ediyor
            if(arr[i] == element) flag = 1; // varsa flag =1 
        }
        if(flag == 0){ // element dizide yoksa ekleyecek
        arr[used]=element;    
        used++;
        }
    }
    /**
     * 
     *  diziden gönderilen parametreye göre eleman silicek
     * @return true or false
     */
    public boolean erase(T value) {  
        int backindex=0; // value ile aynı olan indexi tutmak icin
        T []backup =(T[]) new Object[cap]; // arr backup almak icin
        for(int i = 0; i< cap; i++){
            if(arr[i]== value){
                backindex=i;
                for(int j=0,k = 0; k < cap ; k++,j++){
                    if(j<cap){
                        if(j == backindex && j+1 < cap) { 
                            j++;  // aynı olan elemanı backup almamak icin +1 arrırıyor
                            backup[k] = arr[j];    
                        }
                        if(j != backindex) backup[k] = arr[j];
                    }
                }
            }
        }
        arr=backup;  // parametre olarak gönderiken elemanın olmadıgı backup, arrye atanıyor
        used--;
        return true;
    }
    /**
     * clear all content
     * used==0
     */
    public void clear() {
        Arrays.fill(arr, null); // tüm arryi null ile dolduruyor
        used=0;  // usedu 0 a esitliyor
    }
    public int count(T element) {  // gonderilen elemanın kac tane oldugunu sayıyor
        int count = 0;
        for(int i = 0; i<used;i++)
            if(arr[i]== element) count++;   
        return count;    
    }
    /**
     * 
     * 
     * @return GTUSet iterator
     */
    public GTUIterator find(T element){
        GTUIterator findd =begin();  // iterator objesi olusturuluyor
        
         while(findd.hasNext()){  // diziyi hast next ile kontrol edip tarama yapıyor
            if(findd.next()==element) // eger element dizide var ise iteratoru return ediyor
                return findd;
            }
        findd=null;  // eleman yok ise iteratore null atıyor (cok denedım ama baska cözum bulamadım, hep farklı adres return edildigi icin endi yakalayamıyor)
        return findd; // ıterator return  
    }
    public GTUSetInt<T> intersection(GTUSetInt<T> obj){ // aynı olan elementleri yakalıyor
        GTUSet ob1;  // GTUSet objesi GTUSetIntı cast etmek ıcın
        ob1 =(GTUSet)obj; // GTUSetInt objesi GTUSet e cast ediliyor
        GTUSetInt ınt1 = new GTUSet(); // yeni obje yaratılıyor return etmek icin
        for(int i = 0; i<used;i++){
            for(int j= 0; j< ob1.used;j++)
                if(this.arr[i] == ob1.arr[j]){ 
                      ınt1.insert(this.arr[i]);   // eger aynı element var ise, ınt1 objesine insert ediyor
             }
        }
        return ınt1;
    }
}