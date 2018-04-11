/* 
 * File:   SystemSoftware.cpp
 * Author: Ramazan SAKİN -- 111044069
 */
#include "SystemSoftware.h"
#include<iostream>

namespace sakinSpace{

SystemSoftware::SystemSoftware(): Software()
{ ++numOfSSw; }

SystemSoftware::SystemSoftware( string aName, int number ) : Software(  aName) {
    cout << "System Software Constructor"<<" -- "<<SystemSoftware::getNumberOfSSw()<<endl;
    orderNumSSw = number;
    explanationSSw = " System software is a generic phrase referring to the computer"
                     " programs used to start and run computer systems and networks.";
    ++numOfSSw; //for increasing the alive object number
}

SystemSoftware::~SystemSoftware() {
    cout << "System Software Destructor" << endl;
    --numOfSSw;
}

}