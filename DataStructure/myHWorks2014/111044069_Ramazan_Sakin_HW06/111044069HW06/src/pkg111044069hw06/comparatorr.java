
package pkg111044069hw06;

import java.util.Comparator;
/**
 * @author ramazan
 */

/* Comparator for Car Class according to cost */

public class comparatorr<E> implements Comparator<Car>{

    @Override
    public int compare(Car left, Car right) {
        
        if( left.getCost() < right.getCost() ){
            return -1;
        }else if( left.getCost() > right.getCost() )
            return 1;
        else 
            return 0;
    }
    
}
