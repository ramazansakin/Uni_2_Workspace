/* 
 * File:   ApplicationSoftware.cpp
 * Author: Ramazan Sakin--111044069
 */

#include "ApplicationSoftware.h"
#include<iostream>
using namespace std;

namespace sakinSpace{
    //Default Constructor with default values
    ApplicationSoftware::ApplicationSoftware() : Software(), orderNum(0)
    { ++numOfAppSWare; }
    
ApplicationSoftware::ApplicationSoftware( string aName, int number ) : Software( aName ){
    cout << "Application Software Constructor" << " -- "<<ApplicationSoftware::getNumOfAppSW()<<endl;
    explanation = " Application software is the general designation of"
                  " computer programs for performing user tasks.";
    ++numOfAppSWare;    //to increase
    setNumber(number);
}

ApplicationSoftware::~ApplicationSoftware(){
    cout<<"Application Software Destructor" << endl;
    --numOfAppSWare;    //to decrease
}

}
