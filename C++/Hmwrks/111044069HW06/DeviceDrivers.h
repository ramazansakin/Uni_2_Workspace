/* Copy constructor, assignment operator were not implemented, because of default ones are enough
 * File:   DeviceDrivers.h
 * Author: Ramazan sakin -- 11044069
 */

#ifndef DEVICEDRIVERS_H
#define	DEVICEDRIVERS_H

#include "SystemSoftware.h"

namespace sakinSpace{

class DeviceDrivers: public SystemSoftware{
public:
    DeviceDrivers();
    DeviceDrivers( string aName, int number );
    ~DeviceDrivers();
    
    //getters
    string getExplanationDD()const{ return explanationDD; }
    static int getNumberOfDD() { return numOfDD; }
    
private:

    string explanationDD;
    static int numOfDD;

};

}

#endif	/* DEVICEDRIVERS_H */

