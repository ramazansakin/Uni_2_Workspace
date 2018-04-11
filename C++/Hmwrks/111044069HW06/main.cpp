/* 
 * File:   main.cpp
 * Author: Ramazan Sakin--111044069
 *
 * ***************************************************************************
 *      This Program includes software and its categories and tells about
 *      them what its meaning and which categories they have ...
 * ***************************************************************************     
 *      Copy constructor, assignment operator were not implemented,
 *      because of default ones are enough      
 */

//includes header file but not to deed base header files
#include "Compilers.h"  //includes Software header, 
                        //and also Computer Programming Tools header and others,too..
#include "Debuggers.h"
#include "DeviceDrivers.h"
#include "FileManagers.h"
#include "GraphicsSoftware.h"
#include "BussinessSoftware.h"

using namespace sakinSpace;

//initializing for the static members
int Software::numOfSoftware = 0;
int ApplicationSoftware::numOfAppSWare = 0;
int SystemSoftware::numOfSSw = 0;
int CompProgTools::numOfCPT = 0;
int Compilers::numOfComp = 0;
int Debuggers::numOfDeb = 0;
int DeviceDrivers::numOfDD = 0;
int BussinessSoftware::numOfBS = 0;
int FileManagers::numOfFM = 0;
int GraphicsSoftware::numOfGS = 0;


int main(int argc, char** argv) {
    
    cout << "***********************************************************************"<<endl<<endl;
    Software aSoftware( "Software" );
    cout << aSoftware.getSName() << endl;
    cout << "Number of the alive objects is : " <<aSoftware.getNumOfSoftware() << endl;
    
    cout << "***********************************************************************"<<endl<<endl;
    BussinessSoftware aBusSW("Business Software", 5); // 5 --> random numbers and others, too...
    cout << "A business Software : " << endl;
    cout << "Name : " << aBusSW.getSName() << endl;
    cout << "Number : " << aBusSW.getOrderNum() << endl; 
    cout << "Number of alive Business Software: "<<aBusSW.getNumberOfBS() << endl;
    cout << "Number of Softwares is : " << aBusSW.getNumOfSoftware() << endl;
    
    cout << "***********************************************************************"<<endl<<endl;
    CompProgTools aCompTool( "Computer Programming Tools", 23 );
    cout << "Name of the Computer Programming Tool is : " << aCompTool.getSName() << endl;
    cout << "Number of it : " << aCompTool.getNumberCPT() << endl;
    cout << "Number of alive Computer Programming Tools" << aCompTool.getNumberOfCPT() << endl;
    cout << "Number of Softwares is : " << aCompTool.getNumOfSoftware() << endl;
    
    cout << "***********************************************************************"<<endl<<endl;
    Compilers aCompiler( "Compiler", 7 );
    cout << "Name of the compiler object is : " << aCompiler.getSName() <<endl;
    cout << "Explanation of this : " << aCompiler.getExplanationComp();
    cout << "Number of the compiler : "<< aCompiler.getNumberCPT() << endl;
    cout << "Number of alive Compiler is : " << aCompiler.getNumberOfComp() << endl;
    cout << "Number of Softwares is : " << aCompTool.getNumOfSoftware() << endl;
    
    cout << "***********************************************************************"<<endl<<endl;
    FileManagers aFmanager; //Default constructors are called
    cout << "File Manager object's example with Default Constructors " << endl;
    cout << "Name of the File Manager" << aFmanager.getSName() << endl;
    cout << "Number of the File Manager object is : " << aFmanager.getNumberOfFM() << endl;
    cout << "Explanation of it : " << aFmanager.getExplanationFM() << endl;
    cout << "Number of alive File Manager object is : " << aFmanager.getNumberOfFM() << endl;
    cout << "Number of alive Software objecet is : " << aFmanager.getNumOfSoftware() << endl;
    cout << "***********************************************************************"<<endl<<endl;
    
    cout << "***********************************************************************"<<endl<<endl;
    cout << "Because of the testing of the number alive objects of Compilers " << endl;
    Compilers *arrayOfCompilers;
    arrayOfCompilers = new Compilers[5];
    cout << "After creating 5 Compilers with an array "<< endl;
    cout << "Number of alive Compiler objects is " << Compilers::getNumberOfComp() << endl<<endl;
    delete [] arrayOfCompilers;
    cout << "After deleting the array of Compilers, number of alive object is " <<
                                                        Compilers::getNumberOfComp() << endl;
    cout << endl << endl;                    
    
    cout << "***********************************************************************"<<endl<<endl;
    cout << "End of Testing" << endl;
    cout << "Destructors are called at the end of the program!!!" << endl;
    
    return 0;
}
