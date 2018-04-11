/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lists;

import java.util.Iterator;
import java.util.ListIterator;

/**
 *
 * @author ramazan
 */
public class GITArrayList<E> implements GITList<E>{
    
    private KWArrayList gitArrayList;

    public GITArrayList() {
        gitArrayList = new KWArrayList();
    }
    
    @Override
    public void add(int index, E obj) throws ArrayIndexOutOfBoundsException{
        
        if( index<0 || index > gitArrayList.size() ){
            throw new ArrayIndexOutOfBoundsException();
        }else{
            gitArrayList.add(obj);
            for( int i=gitArrayList.size()-1; i>index;--i )
                gitArrayList.set(i, gitArrayList.get(i-1));
            gitArrayList.set(index, obj);
        }
    }

    @Override
    public void addFirst(E item) {
        gitArrayList.add(item);
        for( int i=gitArrayList.size()-1; i>0;--i )
            gitArrayList.set(i, gitArrayList.get(i-1));
        gitArrayList.set(0, item);
    }
    
    public int getSize(){
        return gitArrayList.size();
    }
    
    @Override
    public E get(int index) {
        return (E)gitArrayList.get(index);
    }

    @Override
    public E getFirst() {
        return (E)gitArrayList.get(0);
    }

    @Override
    public E getLast() {
        return (E)gitArrayList.get(gitArrayList.size()-1);
    }

    @Override
    public Iterator<E> iterator() {
        return new gitListIterator(0);
    }

    @Override
    public ListIterator<E> listIterator() {
        return new gitListIterator(0);
    }

    @Override
    public ListIterator<E> listIterator(int index) {
        return new gitListIterator(index);
    }

    @Override
    public boolean addAll(GITList<E> l) {
        
        if( !l.iterator().hasNext() )
            return false;
        for (Iterator<E> it = l.iterator(); it.hasNext();  ) {
            Object data = it.next();
            gitArrayList.add(data);
        }
        return true;
    }

    @Override
    public boolean containsAll(GITList<E> l) {
        int isThere=0;
        if( !l.iterator().hasNext() )
            return true;
        for( Object item: l ){
            for( int i=0; i<gitArrayList.size() ;++i ){
                if(item.equals(gitArrayList.get(i)))
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
       if( l.get(0) == null )
            return true;
        for( Object item: l ){
            for( int i=0; i<gitArrayList.size(); ++i ){
                data = (E) gitArrayList.get(i);
                if(item.equals(data))
                    gitArrayList.remove(i);
            }
        } 
        return true;
    }

    @Override
    public boolean retainAll(GITList<E> l) {
       E data;
       int isThere = 0;
       if( l.get(0) == null )
            return true;
        for( int i=0; i<gitArrayList.size(); ++i ){
            data = (E)gitArrayList.get(i);
           for (Iterator<E> it = l.iterator(); it.hasNext();) {
               Object item = it.next();
               if(item.equals(data)){
                  isThere=1;
               }
           }
            if( isThere == 1 )
                gitArrayList.remove(i);
            isThere = 0;
        } 
        return true;
    }
    
    private class gitListIterator<E> implements ListIterator<E>{
        
        private int index=0;
        private int returnedItemIndex;
        
        public gitListIterator(int index){
            // check index's Bounds
            if(index < 0 || index > gitArrayList.size())
                throw new ArrayIndexOutOfBoundsException();
            this.index = index;
            returnedItemIndex = -1;
        }

        @Override
        public boolean hasNext(){
            if(index < gitArrayList.size() )
                return true;
            return false;
        }

        @Override
        public E next() {
            if( hasNext() ){
                E data = (E) gitArrayList.get(index);
                returnedItemIndex = index;
                ++index;
                return data;
            }
            
            return null;
        }

        @Override
        public boolean hasPrevious() {
            return index > -1;
        }

        @Override
        public E previous() {
            if( hasPrevious()){
                E data = (E) gitArrayList.get(index);
                returnedItemIndex = index;
                --index;
                return data;
            }
            return null;
        }

        @Override
        public int nextIndex() {
                return index;
        }

        @Override
        public int previousIndex() {
                return index-1;
        }

        @Override
        public void remove(){
            if(returnedItemIndex <= -1)
                throw new IllegalStateException();
            gitArrayList.remove(returnedItemIndex);
            returnedItemIndex= -1;
        }

        @Override
        public void set(E e) {
            if( !(returnedItemIndex <= -1) )
                gitArrayList.set(index, e);
            else
                throw new IllegalStateException();
            returnedItemIndex = -1;
        }

        @Override
        public void add(E e) {
            gitArrayList.add(e);    // to encrease the array size
            for( int i = index+1; i < gitArrayList.size(); ++i )
                gitArrayList.set(i, gitArrayList.get(i+1));
            gitArrayList.set(index, e);
            ++index; 
        }
    
    
    }
    
}

