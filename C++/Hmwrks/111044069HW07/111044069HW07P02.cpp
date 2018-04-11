/* 
 * File:   SortedList.cpp -- P02
 * Author: Ramazan SAKİN
 */

#include "SortedList.h"
#include<iostream>
using std::cout;
using std::endl;

namespace sakinSpace{

template<class T>
SortedList<T>::SortedList(): List<T>(){
}

//copy-constructor
template<class T>
SortedList<T>::SortedList( const SortedList<T>& other){
    setNumberOfElement(other.getNumberOfElements());
    setFirstEle(other.getFirstElement());
    setLastEle(other.getLastElement());
    
    for( int i=0; i<this->getNumberOfElements(); ++i )
        this->elements[i] = other.at(i);

}

//two parameter constructor
template<class T>
SortedList<T>::SortedList(const T eleArray[], const int numberOfEle){
    this->numberOfElements = numberOfEle;
    for( int i=0; i<numberOfEle ; ++i ){
        this->elements[i] = eleArray[i];
    }
}

//destr.
template<class T>
SortedList<T>::~SortedList() {
}

//The function can throw an exception ... ( exception specification )
template<class T>
void SortedList<T>::removeElement(int index) throw (int) {
    
    int i;
    if( index < 0 )
        throw index; 
    else if( this->getNumberOfElements() == 0 ){
        throw index;
    }else if( this->getNumberOfElements()-1 == index ){
        this->elements[index] = 0;
        --this->numberOfElements;    //decreasing the number of elements of the array..
    }else {for( i=index; i<this->getNumberOfElements(); ++i )
        this->elements[i] = this->elements[i+1];  // removing the i nd element,
                                              // I slided the array to back by one step
        --this->numberOfElements;    //decreasing the number of elements of the array..
        sortElements();
    }
}


template<class T>
bool SortedList<T>::searchAnElement(const T& theElement) const{
    for( int i=0; i<this->getNumberOfElements() ; ++i ){
        if( this->at(i) == theElement )
            return true;
    }
    return false;
}

template<class T>
void SortedList<T>::addElement(const T& anElement){
    this->setAnElementB(anElement, this->getNumberOfElements() );
    sortElements();
}

template<class T>
void SortedList<T>::sortElements(){
    if(this->getNumberOfElements() >= 1 ){
        for( int i=0; i<this->getNumberOfElements() ; ++i )
            for( int j=i+1; j<this->getNumberOfElements(); ++j )        
                if( this->elements[j] < this->elements[i] ){
                    //swapping the values
                    T temp = this->elements[i];
                    this->elements[i] = this->elements[j];
                    this->elements[j] = temp;
                } 
    }
}


template<class T>
List<T>& SortedList<T>::operator =(const List<T>& aSList){
    if( this->getNumberOfElements() != aSList.getNumberOfElements() ){
        delete [] this->elements;
        this->elements = new T[aSList.getNumberOfElements()];
    }
    this->numberOfElements = aSList.getNumberOfElements();
    
    for( int i=0; i < aSList.getNumberOfElements(); ++i )
        this->elements[i] = aSList.at(i);
    return *this;
}

//overloading += operator
template<class T>
void SortedList<T>::operator +=(const List<T>& aList){
    int k=0, index = this->getNumberOfElements();
    for( int i=this->getNumberOfElements() ; 
             i<this->getNumberOfElements()+aList.getNumberOfElements(); ++i ){
        
        this->elements[index] = aList.at(k);
        ++index;
        ++k;
    }
    this->setNumberOfElement(aList.getNumberOfElements()+this->getNumberOfElements());
    sortElements();
}

//overloading binary + operator for combining two List
template<class T>
List<T>& SortedList<T>::operator +(const List<T>& rightList){
    
    SortedList<T> *aSlist;
    aSlist = new SortedList<T>;
    int i;
    for( i=0 ; i<this->getNumberOfElements(); ++i )
        aSlist->setAnElementB(this->at(i), i);
    int k=0;
    for( int j=i; j<i+rightList.getNumberOfElements();++j ){
        aSlist->setAnElementB(rightList.at(j-i), j);
        k=j;
    }
    
    aSlist->setNumberOfElement(k+1);
    aSlist->sortElements();
    return *aSlist;
}

//overloading % operator for taking intersection elements of two List
template<class T>
List<T>&  SortedList<T>::operator %(const List<T>& rightList){
    
    SortedList<T> *aSList;
    aSList = new SortedList<T>;
    int lBorder, times=0, hBorder ;   //times is the number of integers elements of them
    if( this->getNumberOfElements() > rightList.getNumberOfElements() ){
        lBorder = rightList.getNumberOfElements();       //border is the number of less elements
        hBorder = this->getNumberOfElements();        
    }else{
        lBorder = this->getNumberOfElements();
        hBorder = rightList.getNumberOfElements();
    }
    
    for( int k=0; k<hBorder; ++k ){
        if( this->getNumberOfElements() == lBorder && k == lBorder )
            break;
        bool status = rightList.searchAnElement( List<T>::at(k));
        if( status == true ){
            aSList->setAnElementB(this->at(k), times);
            ++times;
        }
    }
    aSList->setNumberOfElement(times);
    aSList->sortElements();
    return *aSList;
}

} // End_Of_SakinSpace
