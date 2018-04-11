/* 
 * File:   StarSystem.h
 * Author: ramazan
 *
 * Created on November 13, 2013, 10:39 PM
 */


#ifndef STARSYSTEM_H
#define	STARSYSTEM_H
#include<iostream>
#include "Planet.h"


using namespace std;

class StarSystem {
public:
    StarSystem();
    ~StarSystem();
    StarSystem( const StarSystem& aSystem );    //copy-constructor
    
    //getters
    string getSSName()const { return SSName; }
    int getNumberOfPlanet()const { return numberOfPlanet; }
    Planet getAPlanet(int index)const { return PlanetOFSS[index]; }
    static int getNumOfSS() { return numOfSS; }
    
    //setters
    void setNameSS( string aSSname ){ SSName = aSSname; }
    void setPlanetNumber( int number ){ numberOfPlanet = number; }
    static int setSSnumber(){ ++numOfSS; }
    
    //overloaded Functions
    StarSystem operator+=( const Planet& aPlanet );
    StarSystem operator-=( const Planet& aPlanet );
    Planet& operator[]( int index );
    StarSystem& operator=( const StarSystem& aSystem );
    friend ostream& operator<<( ostream& out, const StarSystem& aSystem );
    
private:
    string SSName;
    int numberOfPlanet;
    Planet *PlanetOFSS;		//composition not inheritance
    static int numOfSS;
    
};


#endif	/* STARSYSTEM_H */

