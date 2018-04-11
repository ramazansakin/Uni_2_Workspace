/* Copy constructor, assignment operator were not implemented, because of default ones are enough
 * File:   FileManagers.h
 * Author: Ramazan Sakin -- 111044069
 */

#ifndef FILEMANAGERS_H
#define	FILEMANAGERS_H

#include "SystemSoftware.h"


namespace sakinSpace{

class FileManagers: public SystemSoftware {
public:
    FileManagers();
    FileManagers( string aName, int number );
    ~FileManagers();
    
    //getters
    string getExplanationFM()const{ return explanationFM; }
    static int getNumberOfFM() { return numOfFM; }
    
    //setter
    void setIsThere( bool there ){ isThere = there; }
    
private:
    bool isThere;
    string explanationFM;
    static int numOfFM;

};

}

#endif	/* FILEMANAGERS_H */
