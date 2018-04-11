/* 
 * File:   CompProgTools.h
 * Author: Ramazan SAKİN -- 111044069
 */

#ifndef COMPPROGTOOLS_H
#define	COMPPROGTOOLS_H
#include"Software.h"
using namespace std;

namespace sakinSpace{

class CompProgTools : public Software{
public:
    CompProgTools();
    CompProgTools( string aName, int number );
    ~CompProgTools();
    //getters
    string getExplanationCPT()const{ return explanationCPT; }
    int getNumberCPT()const { return orderNumCPT; }
    static int getNumberOfCPT() { return numOfCPT; }
    //setter
    void setOrderNum( int aNumber ){ orderNumCPT = aNumber; }
    
private:
    bool status;
    string explanationCPT;
    int orderNumCPT;
    static int numOfCPT;
};

}

#endif	/* COMPPROGTOOLS_H */

