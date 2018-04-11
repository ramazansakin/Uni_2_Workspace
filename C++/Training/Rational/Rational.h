/*
 * Rational.h
 *
 *  Created on: 10 Eki 2013 - 12:05
 *      Author: meltem ?etiner
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

class Rational {
public:
	//Rational();// default  constructor---> 0/1
	//Rational(int numValue);// constructor with one parameter --> numValue/1
	Rational(int numValue=0, int denomValue=1);//constructor with 2 parameters -> numValue/denomValue
	int  getN() const{return numarator;};// get the numarator
	int  getD() const{return denominator;};// get the denominator
	void const output() ;// show the value of the rational
	void set(int numValue, int denomValue);// set the numarator value and the denominator value of the Rational
	Rational add(int numValue, int denomValue);// return Rational+(numValue/denmValue)
    Rational add(Rational& raIns);// return the rational value + raValue
    //static int getNumber(){ return numberCons; }
    ~Rational();
private:
	int numarator;
	int denominator;
	bool simplify();
	//static int numberCons;
};

Rational operator +( const Rational &num1, const Rational &num2 );

Rational operator -( const Rational &num1, const Rational &num2 );

Rational operator /( const Rational &num1, const Rational &num2 );

Rational operator *( const Rational &num1, const Rational &num2 );

//int Rational::numberCons = 0;

#endif /* RATIONAL_H_ */


