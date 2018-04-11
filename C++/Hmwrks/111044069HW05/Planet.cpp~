
#include <iostream>
#include "Planet.h"

Planet::Planet( string aName, double diamtr, double aDistance, double aWeight ):
name(aName),diameter(diamtr), distanceToMainStar(aDistance),weight(aWeight)
{ /* intentionally empty body */ }

Planet::~Planet() {
}


//copy-constructor -- ( big three )
/*Planet::Planet( const Planet& otherPlanet ){
	
	this.name = otherPlanet.getName();	
	this.diameter = otherPlanet.getDiameter();
	this.distanceToMainStar = otherPlanet.getDistance();
	this.weight = otherPlanet.getWeight();

}*/


Planet Planet::operator++()
{
    double newDiameter = getDiameter()+1.0;
    return Planet(name, newDiameter, distanceToMainStar, weight );
}


Planet Planet::operator++(int){
    double tempDiameter = getDiameter();
    setDiameter(getDiameter()+1);
    return Planet(name, tempDiameter, distanceToMainStar, weight );
}

Planet Planet::operator--()
{
    double newDiameter = getDiameter()-1.0;
    return Planet(name, newDiameter, distanceToMainStar, weight );
}

Planet Planet::operator--(int){
    double tempDiameter = getDiameter();
    setDiameter(getDiameter()-1);
    return Planet(name, tempDiameter, distanceToMainStar, weight );
}

bool Planet::operator==( const Planet& rightPlanet )const
{
    if( getDiameter() == rightPlanet.getDiameter()   &&
        getDistance() == rightPlanet.getDistance()   &&
        getName()     == rightPlanet.getName()       &&
        getWeight()   == rightPlanet.getWeight()         ){
        return true;
    }else
        return false;         
}


bool Planet::operator<(const Planet& rightPlanet) const
{
    return getWeight() < rightPlanet.getWeight();
}

bool Planet::operator>(const Planet& rightPlanet) const
{
    return getWeight()>rightPlanet.getWeight();
}

bool Planet::operator<=(const Planet& rightPlanet) const
{
    return getWeight()<=rightPlanet.getWeight();
}

bool Planet::operator>=(const Planet& rightPlanet) const
{
    return getWeight() >= rightPlanet.getWeight();
}

ostream& operator<<( ostream& output, const Planet& aPlanet )
{
    output << "The planet's Name     : "<< aPlanet.getName() << endl   
           << "             Diameter : "<< aPlanet.getDiameter() <<endl
           << "             Distance : "<< aPlanet.getDistance() <<endl
           << "             Weight   : "<< aPlanet.getWeight() << endl; 
           
            return output;
}


Planet& Planet::operator=(const Planet& rightPlanet)
{
    name = rightPlanet.getName();
    distanceToMainStar = rightPlanet.getDistance();
    diameter = rightPlanet.getDiameter();
    weight = rightPlanet.getWeight();
}


istream& operator>>( istream& input, Planet& aPlanet )
{
	// it is better you take the inputs orderly
    input >> aPlanet.name;
    input >> aPlanet.diameter;
    input >> aPlanet.distanceToMainStar;
    input >> aPlanet.weight;
    
    return input;
}

