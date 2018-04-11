/* 
 * File:   SortedList.h -- H02
 * Author: Ramazan SAKIN
 */

#ifndef SORTEDLIST_H
#define	SORTEDLIST_H
#include "List.h"

namespace sakinSpace{

template<class T>
class SortedList: public List<T> {
public:
    SortedList();
    SortedList( const SortedList<T>& other);
    SortedList( const T eleArray[], const int numOfEle );
    virtual ~SortedList();
    
    //getters
    T getFirstElement()const { return firstElement; }
    T getLastElement()const { return lastElement; }
    
    //setters
    void setFirstEle(const T& first ){ firstElement = first; }
    void setLastEle( const T& last ){ lastElement = last; }
    
    //the virtual keyword can be written again but not need to write,Howvr writng vrtual is safer
    //Overriding the virtual functions
    virtual void addElement( const T& anElement );       //adds an element to array of elements
    virtual void removeElement( int index ) throw(int);  //removes an element that is wanted to deleted
    virtual bool searchAnElement( const T& theElement )const;  //searches an element whether there is or not
    void sortElements();
    
    List<T>& operator=( const List<T>& aSList );
    void operator+=( const List<T>& aList );
    List<T>& operator +(const List<T>& rightList );
    List<T>& operator %(const List<T>& rightList );
    
private:
    T firstElement; //first came or largest element in the array
    T lastElement;  //last came or smallest element in the array

};

} //End_of_SakinSpace

#endif	/* SORTEDLIST_H */

