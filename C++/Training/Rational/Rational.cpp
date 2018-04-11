/*
 * Rational.cpp
 *
 *  Created on: 10 Eki 2013
 *      Author: meltem ?etiner
 *
 */
#include <iostream>// for using cout
#include <cstdlib>// for exit()
#include "Rational.h"

using namespace std;

// default  constructor---> 0/1
/*Rational::Rational(){
	numarator=0;
	denominator=1;
	++numberCons;
}

*/
// constructor with one parameter --> numValue/1
/*Rational::Rational(int numValue){
	numarator=numValue;
	denominator=1;
	++numberCons;
}*/

//constructor with 2 parameters -> numValue/denomValue
Rational::Rational(int numValue, int denomValue){
	numarator=numValue;
	denominator=denomValue;
	if(denominator == 0){// error check
		cout<<"denominator can't equal to 0 ";
		exit(1);
	}
	//++numberCons;
}

// show the value of the rational
void const Rational::output(){
	cout<<numarator<<"/"<<denominator<<endl;
}

// set the numarator value and the denominator value of the Rational
void Rational::set(int numValue, int denomValue){
	numarator=numValue;
	denominator=denomValue;
	if(denominator == 0){// error check
			cout<<"denominator can't equal to 0 ";
			exit(1);
		}
}

// return Rational+(numValue/denmValue)
Rational Rational::add(int numValue, int denomValue){
	int tempDenom= denominator*denomValue;
	int tempNum= numValue*denominator + numarator*denomValue;
	Rational temp(tempNum,tempDenom);
	temp.simplify();
	set(temp.getN(),temp.getD());
    return temp;
}

// return the rational value + raValue
Rational Rational::add( Rational& raIns){
	int tempDenom= denominator*raIns.getD();
	int tempNum= raIns.getN()*denominator + numarator*raIns.getD();
	Rational temp(tempNum,tempDenom);
	temp.simplify();
	numarator=temp.getN();
	denominator=temp.getD();
    return temp;
}

bool Rational::simplify(){
	bool change =false;
  int smallValue = (numarator <= denominator ) ? numarator : denominator ;
  for(int i = smallValue ;i>1 ;i--){
	  if(numarator % i == 0 && denominator %i == 0) set(numarator/i,denominator/i);
	  change=true;
  }
  return change;
}

Rational::~Rational() {
	// TODO Auto-generated destructor stub
}


Rational operator +( const Rational &num1, const Rational &num2 ){
	
	if( num1.getD() == num2.getD() )
		return Rational( num1.getN() + num2.getN(), num2.getD() );
	else {
		int denominatorTot, numaratorTot;
		
		numaratarTot = num1.getD()*num2.getN() + num2.getD()*num1.getN();
		
		denominatorTot = num1.getN()*num2.getN();
		
		for( int i=(denominatorTot>numaratorTot) ? denominatorTot: numaratorTot; i>0; --i )
			numaratorTot %= i, denominatorTot %= i;
	}	
	return Rational( numaratorTot, denominatorTot );
}

/*void operator -( const Rational &num1 ){
	num1.denominator = -num1.denominator;
	num1.numarator = -num1.numarator;

}
*/
Rational operator /( const Rational &num1, const Rational &num2 ){
	

}

Rational operator *( const Rational &num1, const Rational &num2 );



