/* 
 * File:   BussinessSoftware.cpp
 * Author: Ramazan Sakin -- 1110440069
 */

#include "BussinessSoftware.h"
#include<iostream>

using namespace std;

namespace sakinSpace{

    BussinessSoftware::BussinessSoftware(): ApplicationSoftware() , status(false)
    { ++numOfBS; }
    
BussinessSoftware::BussinessSoftware( string aName, int number  ) 
                                     : ApplicationSoftware( aName,  number){
    cout << "Business Software Constructor" << " -- " << BussinessSoftware::getNumberOfBS()<<endl;
    explanationBS = "Softwares is used for business";
    ++numOfBS; //for increasing the alive object number
    setStatus(true);
}

BussinessSoftware::~BussinessSoftware() {
    cout << "Business Software Destructor"<<endl;
    --numOfBS; //for decreasing the alive object number
}

}