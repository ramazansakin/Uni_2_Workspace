/* Copy constructor, assignment operator were not implemented, because of default ones are enough
 * File:   GraphicsSoftware.h
 * Author: Ramazan  Sakin -- 111044069
 */

#ifndef GRAPHICSSOFTWARE_H
#define	GRAPHICSSOFTWARE_H

#include "ApplicationSoftware.h"


namespace sakinSpace{

class GraphicsSoftware: public ApplicationSoftware {
public:
    GraphicsSoftware();
    GraphicsSoftware( string aName, int number );
    ~GraphicsSoftware();
    
    //getters
    string getExplanationGS()const{ return explanationGS; }
    static int getNumberOfGS() { return numOfGS; }
    
private:
    string explanationGS;
    static int numOfGS;

};

}

#endif	/* GRAPHICSSOFTWARE_H */

