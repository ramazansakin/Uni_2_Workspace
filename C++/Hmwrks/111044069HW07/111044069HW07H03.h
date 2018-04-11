/* 
 * File:   UniqueList.h -- H03
 * Author: Ramazan SAKIN
 */

#ifndef UNIQUELIST_H
#define	UNIQUELIST_H
#include "List.h"

namespace sakinSpace{

template<class T>
class UniqueList : public List<T> {
public:
	//no parameter constructor
    UniqueList();
    //one-parameter constr.
    UniqueList(const UniqueList& orig);
    //two-parameter constr.
    UniqueList( const T eleArray[], const int numberOfEle );
    // destr as virtual
    virtual ~UniqueList();
    
//the virtual keyword can be wrttn again but not need to write,Hwvr writing vrtul is safr
    virtual void addElement( const T& anElement );  //adds an element to array of elements
    virtual void removeElement( int index ) throw(int);//remvs an elmnt tht is wntd to dltd
    virtual bool searchAnElement( const T& theElement )const;  //srchs an elmnt whther
    void checkUnique();                                        //there is or not
    
    //overloading functions
    void operator+=( const List<T>& aList );
    List<T>& operator=( const List<T>& aSList );
    List<T>& operator+(const List<T>& rightList );
    List<T>& operator%(const List<T>& rightList );
    
private:
    
    
};

}

#endif	/* UNIQUELIST_H */

