/* 
 * File:   ApplicationSoftware.h
 * Author: Ramazan Sakin--111044069
 */

#ifndef APPLICATIONSOFTWARE_H
#define	APPLICATIONSOFTWARE_H
#include"Software.h"

namespace sakinSpace{

    using namespace std;
    
class ApplicationSoftware: public Software// inherits the Software class 
{
public:
    ApplicationSoftware();    //explicity default constructor
    ApplicationSoftware( string aName, int number );
    ~ApplicationSoftware();
    
    //getters
    string getExplanationAppSW()const { return explanation; }
    int getOrderNum(){ return orderNum; }    
    static int getNumOfAppSW(){ return numOfAppSWare; }
    
    //setters
    void setNumber( int aNumber ){ orderNum = aNumber; }
    
private:
    string explanation;
    int orderNum;
    static int numOfAppSWare;
        
};

}

#endif	/* APPLICATIONSOFTWARE_H */

