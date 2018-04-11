/* 
 * File:   main.cpp
 * Author: ramazan
 *
 * Created on November 10, 2013, 11:42 PM
 */

#include <cstdlib>      //  exit())
#include<iostream>
#include "StarSystem.h"

using namespace std;

 
#define SENTINAL -1
const int MAX_SYSTEMS = 20;

int StarSystem::numOfSS = 0;

int getAchoice(void);
int doChoice( int choice, StarSystem SSystems[] );
int findTheSS( StarSystem systems[], string SSname );
int findThePlanet( StarSystem &theSystem, string pName );
void showTheSystems( StarSystem Systems[] );

int main(  ) {
    int status;
    StarSystem systems[MAX_SYSTEMS];
    cout << "Welcome to Star System Program" <<endl;
    
    while( status != SENTINAL ){
        int selection = getAchoice();
        doChoice( selection, systems );
        
        cout << "-Please enter -1 to exit and show the Star Systems, or 1 to go on: "<<endl;
        cin >> status;
        if( status != 1 && status != -1 ){
            cout << "Please enter valid choices" <<endl;
            exit(1);        
        }
    }
    
    //  Test the overloading functions

    showTheSystems(systems);
    
    return 0;
}

int getAchoice(void)
	{
		cout << "1) Create a new Star System" <<endl;
		cout << "2) Add a Planet to a Star System"<<endl;
		cout << "3) Extract a Planet from a Star System"<<endl;
		cout <<"(If you didn't create any Star System,you can't add or extract a Planet!)\n";
		int choice;
		cin >> choice;
		return choice;
	}

	int doChoice( int choice, StarSystem SSystems[] )
	{
		int index=0, stats;
		Planet aPlanet;
		string aName, sName, pName;
		switch( choice ){
		    case 1:
		          cout << "Please enter a name for Star System :"<<endl;
		          cin >> aName;
		          SSystems[StarSystem::getNumOfSS()].setNameSS(aName);
		          StarSystem::setSSnumber();
		          
		          break;
		    case 2:
		        cout << "Please enter the name of the Star System you'll add a planet\n-> ";
		        cin >> sName;
		        index = findTheSS( SSystems, sName );
		        if( index == -1 ){
		            cout << "The Star System was not found!!"<<endl;
		            exit(1);
		        }
		          cout << "Please enter a name, diameter, distance(from main star) and weight\n"
		               << "orderly and add a blank between two attributes" <<endl<<"-> ";
		          cin >> aPlanet;
		          SSystems[index]+=aPlanet;
		          SSystems[index].setPlanetNumber(SSystems[index].getNumberOfPlanet()+1);
		          break;
		    case 3:
		        cout << "Please enter the name of the Star System you'll extract a planet\n-> ";
		        cin >> sName;
		        index = findTheSS( SSystems, sName );
		        if( index == -1 ){
		            cout << "The Star System was not found!!"<<endl;
		            exit(1);
		        }
		        cout << "Please enter the name of the planet you want to extract\n-> ";
		        cin >> pName;
		        stats = findThePlanet( SSystems[index], pName );
		        if( stats == -1 ){
		            cout << "The Planet was not found!!!" << endl;
		            exit(1);
		        }
		        SSystems[index] -= SSystems[index].getAPlanet(stats);
		        SSystems[index].setPlanetNumber(SSystems[index].getNumberOfPlanet()-1);
		        break;
		    default:
		        cout << "You have entered an invalid choice!!!"<<endl;
		        return -1;
		}
	}

	int findTheSS( StarSystem systems[], string SSname )
	{
		for( int i=0; i< StarSystem::getNumOfSS(); ++i ){
		    if( systems[i].getSSName() == SSname )
		        return i;
		}
		return -1;
	}

	int findThePlanet( StarSystem &theSystem, string pName )
	{
		for( int i=0; i<theSystem.getNumberOfPlanet(); ++i )
		    if( theSystem.getAPlanet(i).getName() == pName )
		        return i;
		return -1;  //if there is not a planet that has pName
	}

	void showTheSystems( StarSystem Systems[] )
	{
		for( int i=0; i<StarSystem::getNumOfSS(); ++i )
		    cout << Systems[i] << endl << endl;
		
	}

