/* 
 * File:   DeviceDrivers.cpp
 * Author: Ramazan sakin -- 11044069
 */

#include "DeviceDrivers.h"
#include<iostream>

using namespace std;
namespace sakinSpace{
    DeviceDrivers::DeviceDrivers() : SystemSoftware()
    { ++numOfDD; }
    
DeviceDrivers::DeviceDrivers( string aName ,int number ) : SystemSoftware( aName, number ) {
    cout << "Devices Drivers Constructor" << " -- "<<DeviceDrivers::getNumberOfDD()<<endl;
    explanationDD = "These are required tools to operate the computer system";
    ++numOfDD; //for increasing the alive object number
}

DeviceDrivers::~DeviceDrivers() {
    cout << "Devices Drivers Destructor" << endl;
    --numOfDD; //for decreasing the alive object number
}

}
