/* 
 * File:   UniqueList.cpp -- P03
 * Author: Ramazan SAKIN
 */

#include "UniqueList.h"
#include<iostream>
using std::endl;
using std::cout;

namespace sakinSpace{

template<class T>
UniqueList<T>::UniqueList() : List<T>(){
    //intentionally empty body
}

//copy- constructor
template<class T>
UniqueList<T>::UniqueList(const UniqueList& orig) {
    
    this->numberOfElements = orig.getNumberOfElements();
    for( int i=0; i < this->getNumberOfElements(); ++i )
        this->elements[i] = orig.at(i);
}

// two-parameter constructor 
template<class T>
UniqueList<T>::UniqueList(const T eleArray[], const int numberOfEle){
    this->numberOfElements = numberOfEle;
    int k=0;
    for( int i=0; i<numberOfEle ; ++i ){
      if( !searchAnElement(eleArray[i]) )  
        this->elements[k] = eleArray[i];
        ++k;
    }    
}

template<class T>
UniqueList<T>::~UniqueList() {
  //knowingly empty left
}

template<class T>
//The function can throw an exception ... ( exception specification )
void UniqueList<T>::removeElement(int index) throw (int) {
    
    if( index < 0 )
        throw index;
    else if( this->getNumberOfElements() == 0 ){
        throw index;
    }else {
        for( int i=index; i< this->getNumberOfElements(); ++i )
            this->elements[i] = this->elements[i+1];        // removing the i nd element,
                                      // I slided the array to back by one step
        --this->numberOfElements;    //decreasing the number of elements of the array
    }
}

template<class T>
bool UniqueList<T>::searchAnElement(const T& theElement) const{
    for( int i=0; i<this->getNumberOfElements() ; ++i ){
        if( List<T>::at(i) == theElement )
            return true;
    }
    return false;
}

template<class T> 
void UniqueList<T>::addElement(const T& anElement){
    if( !searchAnElement(anElement) ){
        this->elements[this->getNumberOfElements()] = anElement;
        ++this->numberOfElements;
    }else {
        cout << "The set has already had " << anElement << endl;
        cout << "So it can not be added again!!!" << endl;
    }
    
}

template<class T>
List<T>& UniqueList<T>::operator=(const List<T>& aUList){
    int k=0;
    if( this->getNumberOfElements() != aUList.getNumberOfElements() ){
        delete [] this->elements;
        this->elements = new T[aUList.getNumberOfElements()];
    }
    this->numberOfElements = aUList.getNumberOfElements();
    
    for( int i=0; i < aUList.getNumberOfElements(); ++i ){
            this->elements[i] = aUList.at(i);
    }
    return *this;
}

template<class T>
void UniqueList<T>::checkUnique(){
    for( int i=0; i<this->getNumberOfElements(); ++i )
        for( int j=i+1; j<this->getNumberOfElements(); ++j )
            if( this->elements[i] == this->elements[j] )
                for( int k=j; k<this->getNumberOfElements(); ++k )
                    this->elements[k] = this->elements[k+1];
}                              

template<class T>
void UniqueList<T>::operator +=(const List<T>& aList){
    int k=0, index = this->getNumberOfElements(), decreaser=0;  //decreaser for not being
    for( int i = this->getNumberOfElements() ;                  //same element in the Un.List
             i< this->getNumberOfElements()+aList.getNumberOfElements(); ++i ){
                if( !searchAnElement( aList.at(k) ) ){
                   this->elements[index] = aList.at(k);
                   ++index;
                }else
                     --decreaser;   
        ++k;
    }
    
    this->setNumberOfElement(aList.getNumberOfElements()+
                             this->getNumberOfElements()+decreaser);  
    this->checkUnique();
}

//overloading binary + operator for combining two List
template<class T>
List<T>& UniqueList<T>::operator+(const List<T>& rightList){
    
    UniqueList<T> *aUList;
    aUList = new UniqueList<T>;
    int i;
    
    for( i=0 ; i<this->getNumberOfElements(); ++i )
        aUList->elements[i] = this->at(i);
    int k=0;
    for( int j=i; j<i+rightList.getNumberOfElements();++j ){
        aUList->elements[j] = rightList.at(k);
        ++k;
    }
    aUList->setNumberOfElement(k);
    return *aUList;
}

//overloading % operator for taking intersection elements of two List
template<class T>
List<T>& UniqueList<T>::operator%(const List<T>& rightList){
    
    UniqueList<T> *aUList;
    aUList = new UniqueList<T>;
    int lBorder, times=0, hBorder;   //times is the number of integers elements of them
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
        bool status = rightList.searchAnElement(this->at(k));
        if( status == true ){
            aUList->setAnElementB(this->at(k), times);
            ++times;
        }
    }
    aUList->setNumberOfElement(times);
    return *aUList;
}

}
