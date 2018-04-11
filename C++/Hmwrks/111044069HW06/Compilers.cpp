/* 
 * File:   Compilers.cpp
 * Author: Ramazan Sakin -- 111044069
 */

#include "Compilers.h"

namespace sakinSpace{
    
Compilers::Compilers(): CompProgTools(), status(false) 
{ ++numOfComp; /*for increasing the alive object number*/ }    
    
Compilers::Compilers(string aName, int number): CompProgTools( aName, number ) {
    cout << "Compilers constructor" << endl;
    setStatus(true);
    explanationComp = "Compilers are programs to help to programmers for programming";
    ++numOfComp; //for increasing the alive object number
}

Compilers::~Compilers() {
    cout << "Compilers destructor" << endl;
    --numOfComp; //for decreasing the alive object number
}

}