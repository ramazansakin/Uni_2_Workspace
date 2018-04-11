/* 
 * File:   Compilers.h
 * Author: Ramazan sakin -- 111044069
 */

#ifndef COMPILERS_H
#define	COMPILERS_H

#include "CompProgTools.h"

using namespace std;

namespace sakinSpace{

class Compilers : public CompProgTools{
public:
    Compilers();
    Compilers( string aName, int number );
    ~Compilers();
    
    //getters
    string getExplanationComp()const{ return explanationComp; }
    static int getNumberOfComp() { return numOfComp; }
    //
    void setStatus( bool aSts ){ status = aSts; }
    
private:
    bool status;
    string explanationComp;
    static int numOfComp;

};

}

#endif	/* COMPILERS_H */

