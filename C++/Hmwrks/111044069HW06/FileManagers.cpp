/* 
 * File:   FileManagers.cpp
 * Author: Ramazan Sakin -- 111044069
 */

#include "FileManagers.h"

namespace sakinSpace{

FileManagers::FileManagers():SystemSoftware()
{ ++numOfFM; }    
    
FileManagers::FileManagers( string aName, int number ) : SystemSoftware( aName,  number ){
    
    setIsThere(true);
    explanationFM = "These are file managers";
    ++numOfFM; //for increasing the alive object number
}

FileManagers::~FileManagers() {
    cout << "Destructor for File Managers" << endl;
    --numOfFM; //for decreasing the alive object number
}

}
