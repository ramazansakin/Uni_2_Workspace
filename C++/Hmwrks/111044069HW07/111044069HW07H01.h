/* 
 * File:   List.h
 * Author: Ramazan Sakin -- 111044069
 */

#ifndef LIST_H
#define	LIST_H
#include<fstream>
using std::ostream;

namespace sakinSpace{

//template with type T( any type )    
template<class T>
class List{
public:
    List();
    List( const T array[], const int numOfElement );
    List(const List<T>& orig);  //copy-constructor
    virtual ~List();

    //pure virtual class not to instantiate this class
    // this is only used as base class and for code reuse!!! So it should be declared
    // as pure virtual function
    virtual void addElement( const T& anElement ) = 0;
    virtual void removeElement( int index )  = 0;
    virtual bool searchAnElement( const T& theElement )const = 0;
    
    //getters
    int getNumberOfElements()const { return numberOfElements; }
    T at( int index )const throw(int);
    
    //setters
    void setNumberOfElement( const int& number ){ numberOfElements = number; }
    void setAnElementB( const T& anElement, int index );
    
    //operator overloading for the class
    virtual void operator+=( const List<T>& aList ) = 0;    //return *this
    virtual List<T>& operator=( const List<T>& otherList ) = 0;  //overload assignment op. for
    virtual List<T>& operator%( const List<T>& rightList ) = 0;
    virtual List<T>& operator+( const List<T>& rightList ) = 0;     
    
    protected:
        T* elements;
        int numberOfElements;
        
};

template<class T>
ostream& operator<<( ostream& out, const List<T>& theList );

}

#endif	/* LIST_H */

