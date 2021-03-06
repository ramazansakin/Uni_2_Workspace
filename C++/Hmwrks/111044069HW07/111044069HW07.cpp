/* 
 * File:   111044069HW07.cpp  --  main.cpp
 * Author: Ramazan SAKIN -- 111044069
 */

#include<iostream>
#include "List.cpp"
#include "List.h"
#include "UniqueList.cpp"   //for template class
#include "SortedList.cpp"

using namespace std;
using namespace sakinSpace;


int main( ){

    // Exception-handling ... try-throw-catch blocks    
    try{
        
        //Testing
        cout << "###############################################################" <<endl;
        cout << "Creating an Sorted List object and Unique List object  and adding "
             << "\nelements: " << endl;
        cout << "a SortedList object has character array" << endl;
        SortedList<char> charSList;
        charSList.addElement('r');
        charSList.addElement('s');
        charSList.addElement('a');
        charSList.addElement('k');
        charSList.addElement('n');
        cout << charSList << endl;
        
        cout << "an UniqueList object has double array " <<endl;
        UniqueList<double> aUList;
        aUList.addElement(12.45);
        aUList.addElement(23.56);
        aUList.addElement(36.23);
        aUList.addElement(23.56);
        aUList.addElement(3.45);
        aUList.addElement(23.65);
        
        cout << aUList << endl;
        cout << "################################################################" << endl;
        cout << "Removing and searching an element from an object's array" << endl;
        
        cout << "Remove 12.45 form the Unique List has double array" << endl;
        aUList.removeElement(0);
        cout << "Remove 's' character from the Sorted List has char array" << endl;
        charSList.removeElement(4);
        cout << aUList << endl;
        cout << charSList << endl << endl;
        
        cout << endl;
        cout << "Searching test: search char 'r' in the Sorted array whether there is or not" << endl;
        if (charSList.searchAnElement('a') )
            cout << "'r' character is found in the SortedList array" << endl;
        else
            cout << "'r' character is not found the Sorted List array" <<endl;    
        
        cout << "Searching 34.56 from the UniqueList array" << endl;
        if( aUList.searchAnElement(34.56) )       
            cout << "34.56 is found the List" <<endl;
        else
            cout << "34.56 is not found the List" <<endl;
        cout << "################################################################" << endl;
        cout << "Testing the += operator" << endl;
        SortedList<int> intSList;
        intSList.addElement(11);
        intSList.addElement(63);
        intSList.addElement(571);
        intSList.addElement(82);
        intSList.addElement(234);
        
        UniqueList<int> intUList;
        intUList.addElement(23);
        intUList.addElement(83);
        intUList.addElement(33);
        intUList.addElement(632);
        intUList.addElement(5);
        
        cout << "A new int Unique list" <<endl << intUList << endl;
        cout << "A new int SortedList" << endl <<intSList << endl;
        cout << "intUList += intSList;" << endl;
        intUList += intSList;
        cout << "new aUList:" << endl; 
        cout << intUList<< endl;
        
        cout << "################################################################" << endl;
        cout << "Testing + and % operator : " << endl;
        intSList.addElement(45);
        intSList.addElement(21);        
        
        UniqueList<int> anUniqueListt; 
        anUniqueListt.addElement(12);
        anUniqueListt.addElement(25);
        anUniqueListt.addElement(63);
        anUniqueListt.addElement(23);
        anUniqueListt.addElement(21);
        anUniqueListt.addElement(151);
        
        SortedList<int> newList;
        cout << "The int SortedList " << endl ;
        cout << intSList << endl;        
        cout << "The int Unique List" << endl;
        cout << anUniqueListt <<endl;        
        cout << "The conjunction of the Lists:" << endl;
        
        newList = intSList+anUniqueListt;
        cout << newList << endl;
        cout << endl;
        cout << "The disjunction of the Lists:" << endl;
        newList = intSList%anUniqueListt;
        cout << newList << endl;
        
        cout << "################################################################" << endl;
        cout << "Testing = operator: " << endl;
        cout << "Before UniqueList = SortedList" << endl;
        cout << "The UniqueList" << endl;
        cout << anUniqueListt<< endl;
        cout << "the Sorted List" << endl;
        cout << intSList<<endl; 
        cout << "After UniqueList = SortedList" << endl;
        anUniqueListt = intSList;
        cout << "The UniqueList" << endl;
        cout << anUniqueListt<< endl;
        cout << "the Sorted List" << endl;
        cout << intSList<<endl;
        
        cout << "################################################################" << endl;
        cout << "Testing at() function to get an element with specific index" << endl;
        
        cout << "First 5 element in a Unique Array: " << endl;
        for( int i=0; i< 5; ++i )
            cout << anUniqueListt.at(i) << " ";
        cout << endl << endl;    
        cout << "################################################################" << endl;
        cout << "Testing exception handling errors:" << endl<<endl;
        
        UniqueList<int> uniqList;
        cout << "If you try to remove an element from an empty List:" <<endl;
        uniqList.removeElement(2);
        
        
    } 
    catch(int index){   /* exception-handler */
        cout << "Illegal index!!!Your command failed!!!" << endl;
    }catch(double){
        cout << "Illegal double element!!Your commed is failed!!!" << endl;
    }
    cout << endl;
    try{
    	UniqueList<char> uniqList;
    	cout << "If you try to access an element from an empty List:" <<endl;
    	uniqList.at(3);
    }catch(int){
    	cout << "Illegal index!!!Your command failed!!!" << endl;
    }
    cout << "The Program is closed..." << endl;
    return 0;   //END_OF_TESTING_MAIN
}

