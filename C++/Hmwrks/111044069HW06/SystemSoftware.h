/* Copy constructor, assignment operator were not implemented, because of default ones are enough
 * File:   SystemSoftware.h
 * Author: Ramazan  Sakin--111044069
 * Gebze Institue of Technology
 */

#ifndef SYSTEMSOFTWARE_H
#define	SYSTEMSOFTWARE_H

#include "Software.h"

namespace sakinSpace{

class SystemSoftware: public Software{
public:
    SystemSoftware();
    SystemSoftware( string aNAme, int number );
    ~SystemSoftware();
    
    //getters
    string getExplanationSSw()const{ return explanationSSw; }
    int getNumberSSw()const { return orderNumSSw; }
    static int getNumberOfSSw() { return numOfSSw; }
    
private:
    string explanationSSw;
    int orderNumSSw;
    static int numOfSSw;
    
};


}

#endif	/* SYSTEMSOFTWARE_H */

