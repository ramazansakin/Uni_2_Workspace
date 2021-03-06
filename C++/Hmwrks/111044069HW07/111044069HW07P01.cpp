/* 
 * File:   List.cpp
 * Author: Ramazan SAKIN -- 111044069
 */
#include<iostream>
#include "List.h"
#include "SortedList.h"

using namespace std;

namespace sakinSpace{    

template<class T>
List<T>::List() :numberOfElements(0){
    elements = new T[25];
}

template<class T>
List<T>::List( const T array[], const int numOfElement ):numberOfElements(numOfElement){
	
	//elements = new T[numOfElement];
    for( int i=0; i<numOfElement; ++i )
        elements[i] = array[i];
}

template<class T>
List<T>::~List(){
    delete [] elements; 
}

/*
template<class T>   //assignment operator for big three
List<T>& List<T>::operator=( const List<T>& otherList ){
    if( getNumberOfElements() != otherList.getNumberOfElements() ){
        delete [] elements;
        elements = new T[otherList.getNumberOfElements()];
        
    }
    setNumberOfElement( otherList.getNumberOfElements() );
    
    for( int i=0; i<otherList.getNumberOfElements(); ++i )
        elements[i] = otherList.at(i);
        
    return *this;    
}*/

//copy-constructor
template<class T>
List<T>::List(const List<T>& orig) :numberOfElements(orig.numberOfElements){
    // elemets = new T[orig.numberOfElements];
    for( int i=0 ; i< getNumberOfElements(); ++i ){
        elements[i] = orig.at(i);
    }
}

template<class T>
//The function can throw an exception ... ( exception specification ) )
T List<T>::at(int index)const throw(int){
    if( index < 0 || index > getNumberOfElements() ){
        cout << "Illegal index!!!" << endl;
        throw index;
    }else
        return elements[index];       // first element of the array is elements[0]
}

template<class T>
void List<T>::setAnElementB(const T& anElement, int index){
    if( index < 0 || index > getNumberOfElements() )
        throw index;
    else{
        this->elements[getNumberOfElements()] = anElement;
        ++this->numberOfElements;
    }     
}

template<class T>
//stream extraction operator
ostream& operator<<( ostream& out, const List<T>& aList ){
    int i;
    out << "Number of elements of the array of the list: "<< aList.getNumberOfElements()
                                                                               <<endl;    
    out << "The elements are :" << endl;
    for( i=0; i<aList.getNumberOfElements(); ++i )
        out << aList.at(i) << " ";
    
    out << endl << endl;
    return out;
}

}


