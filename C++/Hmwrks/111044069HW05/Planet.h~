/* 
 * File:   Planet.h
 * Author: ramazan
 *
 * Created on November 10, 2013, 11:44 PM
 */

#ifndef PLANET_H
#define	PLANET_H

using namespace std;	// using std::string;

class Planet {
public:
    Planet(){ /* empty */ }
    Planet( string aName, double diamtr, double aDistance, double aWeight );
    //Planet(const Planet& rightPlanet );	//copy-constructor ( a member of big three )
    ~Planet();
    
    //getters
    string getName()const{ return name; }
    double getDiameter()const{ return diameter; }
    double getDistance()const{ return distanceToMainStar; }
    double getWeight()const{ return weight; }
    
    //setters -- inline functions
    void setName( string aName ){ name = aName; }
    void setDiameter( double diamtr ){ diameter=diamtr; }
    void setDistance( double distance ){ distanceToMainStar=distance; }
    void setWeight( double aWeight ){ weight=aWeight; }
    
    //overloading Functions
    Planet operator++( );       //for prefix
    Planet operator++( int );   //for postFix
    Planet operator--( );
    Planet operator--( int );
    
    bool operator==( const Planet& rightPlanet )const;
    bool operator<( const Planet& rightPlanet )const;
    bool operator>( const Planet& rightPlanet )const;
    bool operator<=( const Planet& rightPlanet )const;
    bool operator>=( const Planet& rightPlanet )const;
    Planet& operator=( const Planet& rightPlanet );	//assignment operator -- (big three)
    friend istream& operator>>( istream& input, Planet& aPlanet );
    friend ostream& operator<<( ostream& output, const Planet& aPlanet );
    
private:

    string name;
    double diameter;
    double distanceToMainStar;
    double weight;
    
};

#endif	/* PLANET_H */

