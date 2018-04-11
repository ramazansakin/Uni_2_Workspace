/* 
 * File:   CompProgTools.cpp
 * Author: Ramazan Sakin -- 111044069
 */

#include <iostream>

#include "CompProgTools.h"
#include<iostream>
using std::cout;
using std::endl;

namespace sakinSpace{
    
    CompProgTools::CompProgTools()
    {  ++numOfCPT; }

CompProgTools::CompProgTools( string aName, int number ) : Software( aName ){
    cout << "CompProgTools constructor"<< " -- "<<CompProgTools::getNumberOfCPT()<< endl;
    setOrderNum(number);
    explanationCPT = "Any tools that help us to programming";
    ++numOfCPT; //for increasing the alive object number
    
}

CompProgTools::~CompProgTools() {
    cout << "CompProgTools destructor" << endl;
    --numOfCPT; //for decreasing the alive object number
}

}
