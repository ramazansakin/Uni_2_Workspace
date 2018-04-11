/* 
 * File:   Debuggers.cpp
 * Author: Ramazan Sakin -- 111044069
 */

#include "Debuggers.h"
#include "ApplicationSoftware.h"


namespace sakinSpace{
    
    Debuggers::Debuggers() : CompProgTools(), status(false)
    { ++numOfDeb; }
    
Debuggers::Debuggers( string aName, int number ) : CompProgTools( aName, number) {
    cout << "Constructor for Debuggers -- " << getNumberOfDeb() << endl;
    explanationDeb = "Debuggers are programs to show us our fault on the program codes";
    ++numOfDeb; //for increasing the alive object number
    setStatus(true);
}


Debuggers::~Debuggers() {
    cout << "Destructor for Debuggers -- " << endl;
    --numOfDeb; //for decreasing the alive object number
}


}
