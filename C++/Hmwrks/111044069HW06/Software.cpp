/* Copy constructor, assignment operator were not implemented, because of default ones are enough
 * File:   Software.cpp
 */

#include "Software.h"
#include<cstdlib>
#include<iostream>

using namespace std;

namespace sakinSpace{

Software::Software(): name("unnamed Software")
{ /* intentionally empty body -- default constructor in explicit */ }    
    
Software::Software( string aName ) {
  
    cout << "Software constructor -- " << getNumOfSoftware() << endl;
    setSName(aName);
    subCathegoryName = new string[3]; //for subcategories
    subCathegoryName[0] = "Application Software";
    subCathegoryName[1] = "System Software";
    subCathegoryName[2] = "Computer Programming Tools";
    ++numOfSoftware;
}

string Software::getASubCathagoryName(int index) const
{
    if( index > 3 || index < 0){
        cout << "Illegal index!!!The program was closed" << endl;
        exit(1);
    }else
        return subCathegoryName[index];
}

Software::~Software() {
    cout << "Software destructor" << endl;
    --numOfSoftware;
}

}
