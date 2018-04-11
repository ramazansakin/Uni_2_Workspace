/* 
 * File:   StarSystem.cpp
 * Author: ramazan
 * 
 */

#include<iostream>
#include<cstdlib>
#include "StarSystem.h"

using namespace std;

StarSystem::StarSystem():numberOfPlanet(0)
{ 
    PlanetOFSS = new Planet[20];
}

//Copy- Constructor -- ( a member of Big Three )
StarSystem::StarSystem(const StarSystem& aSystem):SSName(aSystem.getSSName()),
        numberOfPlanet(aSystem.getNumberOfPlanet() )
{
    PlanetOFSS = new Planet[getNumberOfPlanet()];
    
    for( int i=0; i < getNumberOfPlanet() ; ++i )
        PlanetOFSS[i] = aSystem.getAPlanet(i);

}


// Destructor -- ( a member of Big Three )
StarSystem::~StarSystem() {
    
    delete [] PlanetOFSS;
}

StarSystem StarSystem::operator+=( const Planet& aPlanet)
{
    PlanetOFSS[getNumberOfPlanet()] = aPlanet;
    // increase the number of Planet !!!
    return *this;
}

StarSystem StarSystem::operator-=(const Planet& aPlanet)
{
    int found=0, i;
    for( i=0; i<getNumberOfPlanet(); ++i )
        if( aPlanet.getName() == PlanetOFSS[i].getName() ){
            found = 1;
            break;
        }
    if( found != 1 ){
        cout<< "The Planet was not found!!" << endl;
        exit(1);
    }else{
        for( int j=i; j<getNumberOfPlanet()-1; ++j )
            PlanetOFSS[j] = PlanetOFSS[j+1];
        // decrease the number of Planet !!!    
    }
    return *this;
}

// assignment operator -- ( a member of Big Three )
StarSystem& StarSystem::operator=( const StarSystem& aSystem )
{
    if( numberOfPlanet != aSystem.getNumberOfPlanet() ){
        delete [] PlanetOFSS;
        PlanetOFSS = new Planet[getNumberOfPlanet()];
    }

    numberOfPlanet = aSystem.getNumberOfPlanet();
    SSName = aSystem.getSSName();

    for( int i=0; i<numberOfPlanet; ++i )
       PlanetOFSS[i] = aSystem.getAPlanet(i);
 
    return *this;
}

//overloading index operator
Planet& StarSystem::operator[](int index)
{
    return PlanetOFSS[index];
}


ostream& operator<<( ostream& out, const StarSystem& aSystem )
{
    out << "Star System Name:   " <<aSystem.getSSName() <<endl
         <<"number of Planets:  " <<aSystem.getNumberOfPlanet()<<endl
         <<"The Planets are     " <<endl;
         
    for (int i = 0; i < aSystem.getNumberOfPlanet(); ++i) {
        out << aSystem.getAPlanet(i) << endl;
        // out << aSystem[i] << endl;
    }
    
    return out;
}

