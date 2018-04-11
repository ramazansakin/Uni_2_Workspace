/* 
 * File:   BussinessSoftware.h
 * Author: Ramazan Sakin -- 11044069
 */

#ifndef BUSSINESSSOFTWARE_H
#define	BUSSINESSSOFTWARE_H

#include "ApplicationSoftware.h"
using std::string;

namespace sakinSpace{

class BussinessSoftware : public ApplicationSoftware 
{
public:
    BussinessSoftware();
    BussinessSoftware( string aName, int number );
    ~BussinessSoftware();
    
    //getters
    string getExplanationBs()const{ return explanationBS; }
    static int getNumberOfBS() { return numOfBS; }
    
    //setter
    void setStatus( bool aStatus ){ status = aStatus; }
    
private:
    bool status;
    string explanationBS;
    static int numOfBS;
    

};

}

#endif	/* BUSSINESSSOFTWARE_H */

