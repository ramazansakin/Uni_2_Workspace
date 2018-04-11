package lists;

import java.util.Iterator;
import  java.util.ListIterator;

/**
 *
 * @author ramazan
 */
public interface GITList<E> extends Iterable<E>{
    
    // Add an item at the specified index
    void add(int index, E obj);
    
    // Insert an object at the beginning of the list.
    void addFirst(E item);

    // Get the element at position index.    
    E get(int index);

    // Get the first element in the list. 
    E getFirst();

    // Get the last element in the list.
    E getLast();

    // Return an Iterator to the list    
    Iterator<E> iterator();

    // Return a ListIterator to the list
    ListIterator<E> listIterator();

    // Return a ListIterator that begins at index
    ListIterator<E> listIterator(int index);

    // Adds all of the elements in the specified collection
    //to this collection (optional operation).
    boolean addAll(GITList<E> l);

    // Returns true if this collection contains all of the
    // elements in the specified collection.
    boolean containsAll(GITList<E> l);
    
    //Removes all of this collection's elements that are also contained
    // in the specified collection (optional operation).
    boolean removeAll(GITList<E>  l);
    
    // Retains only the elements in this collection that are contained
    // in the specified collection (optional operation).
    boolean retainAll(GITList<E>  l);

}
