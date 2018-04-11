/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lists;

import java.util.Iterator;
import java.util.ListIterator;
import java.lang.Iterable;

/**
 *
 * @author ramazan
 */
public class GITLinkedList<E> implements GITList<E>, Iterable<E>{
    
    /* compose KWLinkedList object to delegate its methods */
    private KWLinkedList<E> gitLinkedList;

    public GITLinkedList() {
        gitLinkedList = new KWLinkedList();
    }

    @Override
    public void add(int index, E obj) {
        gitLinkedList.add(index, obj);
    }

    @Override
    public void addFirst(E item) {
        gitLinkedList.addFirst(item);
    }
   
    @Override
    public E get(int index) {
        return (E)gitLinkedList.get(index);
    }

    @Override
    public E getFirst() {
        return (E)gitLinkedList.getFirst();
    }

    @Override
    public E getLast() {
        return (E)gitLinkedList.getLast();
    }

    @Override
    public Iterator<E> iterator() {
        return gitLinkedList.iterator();
    }

    @Override
    public ListIterator<E> listIterator() {
        return gitLinkedList.listIterator();
    }

    @Override
    public ListIterator<E> listIterator(int index) {
        return gitLinkedList.listIterator(index);
    }

    @Override
    public boolean addAll(GITList<E> l) {
        
        int i=0;
        if( !l.iterator().hasNext() )
            return false;
        for (Iterator<E> it = l.iterator(); it.hasNext();  ) {
            Object data = it.next();
            gitLinkedList.addLast((E) data);
        }
        return true;
    }
    
    @Override
    public boolean containsAll(GITList<E> l) {
        int isThere=0;
        if( !l.iterator().hasNext() )
            return true;
        for( Object item: l ){
            for( int i=0; gitLinkedList.listIterator(i).hasNext() ;++i ){
                if(item.equals(gitLinkedList.get(i)))
                    isThere=1;
            }
            if( isThere==0 )
                return false;
            isThere = 0;
        }
        return true;
    }

    @Override
    public boolean removeAll(GITList<E> l) {
        E data;
        Iterator<E> itr = gitLinkedList.listIterator(0);
        if( !itr.hasNext() )
            return true;
        for( Object item: l ){
            for( int i=0; itr.hasNext(); ++i ){
                data = itr.next();
                if(item.equals(data))
                    itr.remove();
            }
            itr = gitLinkedList.listIterator(0);
        } 

        return true;
    }

    @Override
    public boolean retainAll(GITList<E> l) {
        E data;
        boolean isThere = false;
        Iterator<E> itr = gitLinkedList.listIterator(0);
        if( !itr.hasNext() )
            return true;
        for( int i=0; itr.hasNext(); ++i ){
            data = itr.next();
            for( Object item: l ){
                if(item.equals(data))
                    isThere=true;
            }
            if( !isThere )
                itr.remove();
            isThere = false;
        } 

        return true;
    }
    

    
    
}
