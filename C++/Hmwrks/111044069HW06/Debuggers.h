/* 
 * File:   Debuggers.h
 * Author: Ramazan sakin -- 111044069
 */

#ifndef DEBUGGERS_H
#define	DEBUGGERS_H

#include "CompProgTools.h"

namespace sakinSpace{

class Debuggers: public CompProgTools{
public:
    Debuggers();
    Debuggers( string aName, int number );
    ~Debuggers();
    
    //getters
    string getExplanationDeb()const{ return explanationDeb; }
    static int getNumberOfDeb() { return numOfDeb; }
    //setter
    void setStatus( bool aStat ){ status = aStat; }
    
private:
    bool status;
    string explanationDeb;
    static int numOfDeb;

};

}

#endif	/* DEBUGGERS_H */

