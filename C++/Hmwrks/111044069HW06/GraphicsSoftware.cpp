/* 
 * File:   GraphicsSoftware.cpp
 * Author: Ramazan Sakin-- 111044069
 */

#include "GraphicsSoftware.h"
#include<iostream>

using std::endl;
using std::cout;

namespace sakinSpace{

GraphicsSoftware::GraphicsSoftware() : ApplicationSoftware()
{ ++numOfGS; }
    
GraphicsSoftware::GraphicsSoftware( string aName, int number ):ApplicationSoftware( aName, number) {
    cout << "Graphics Software Constructor"<<" -- "<<GraphicsSoftware::getNumberOfGS()<<endl;
    explanationGS = "Software for Graphics";
    ++numOfGS; //for increasing the alive object number
}

GraphicsSoftware::~GraphicsSoftware() {
    cout << "Graphics Software Destructor" <<endl;
    --numOfGS; //for decreasing the alive object number
}

}
