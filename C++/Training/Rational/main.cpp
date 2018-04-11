/*
 * Driver.cpp for showing the Rational Class
 *
 *  Created on: 10 Eki 2013  12:05
 *      Author: meltem ?etiner
 *
 */

 #include <iostream>
 #include "Rational.h"

 using namespace std;

 int main(int argc , char** argv){

    Rational a,b(2,5), c(3,4);
    cout<<"a =";
    a.output();//  0/1
    cout<<"b =";
    b.output();//  2/1
    cout<<"c =";
    c.output();//  3/4

    cout<<"a = a + 1/2 = ";
    a.add(1,2);
    a.output();//  1/2

    cout<<"c = c + a = ";
    c.add(a);
    c.output(); // 5/4

    cout<<"b = b + 3/9 = ";
    b.add(3,9);//   7/3
    b.output();

    cout<<"a = b =";
    a= b;
    a.output(); ///  7/3

    return 0;
 }