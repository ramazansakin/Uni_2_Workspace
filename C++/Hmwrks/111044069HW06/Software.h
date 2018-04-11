/* Copy constructor, assignment operator were not implemented, because of default ones are enough
 * File:   Software.h
 * 111044069---Ramazan Sakin
 */

#ifndef SOFTWARE_H
#define	SOFTWARE_H
#include <iostream>

namespace sakinSpace{
    
    using namespace std;
    
class Software {
    
public:
    Software();
    Software( string aName );
    //Software( const Software &other );
    ~Software();
    
    //getters
    string getSName()const{ return name; }
    static int getNumOfSoftware(){ return numOfSoftware; }
    string getASubCathagoryName(int index)const;
    
    //setters
    void setSName( string aName ){ name = aName; }
    
private:
    string name;
    string *subCathegoryName;
    static int numOfSoftware;
    
};

}

#endif	/* SOFTWARE_H */