import java.util.Iterator;
import java.security.InvalidAlgorithmParameterException;

/**
 *
 * @author Emre KAVAK
 * Java İnterface class
 */
public interface GTUSetInt<T>{
    
    public boolean empty();
    public int size();
    public int maxSize();
    public void insert(T element);
    public boolean erase(T value);
    public void clear();
    public int count(T element);
    public Object begin();
    public Object end();
    public Object find(T element);      
}