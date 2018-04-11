/*#############################################################################/
			Ramazan SAKIN ------ 111044069
     ###########################################
 	    
	The program gets argument from console and gets lines from user,
	searches the string user want to find from the lines, and prints the lines
	that includes the target string and checks 		 

##############################################################################*/

#include<iostream>
#include<string>

using namespace std;

const int maxLineNum = 30;	//number of line at most, but it is changeable
int sgrep( const string targetStr , string lines[maxLineNum], int numOfLine,
															   int numFunCOpt );

int controllArgv( char *argv[], int argc );

int getLines( string lines[maxLineNum] );

int findLenghtOfStr( string str );

int main( int argc, char **argv )
{
	int status, entrance;
	string lines[maxLineNum];
	status = controllArgv( argv, argc );	
	int numOfLine;
	
	switch(status){
		case 1:	
			numOfLine = getLines( lines );
			cout << endl;
			entrance = sgrep( argv[1], lines, numOfLine, 0 );	//only searchs
			break;		
		case 2:
			numOfLine = getLines( lines );
			cout << endl;
			entrance = sgrep( argv[2], lines, numOfLine, 1 );	//not case sensitivity searchs	
			break;
		case 3:
			numOfLine = getLines( lines );		// also prints line of found string
			cout << endl;
			entrance = sgrep( argv[2], lines, numOfLine, 2 );
			break;
		case 4:
			numOfLine = getLines( lines );		
			cout << endl;
			entrance = sgrep( argv[3], lines, numOfLine, 3 );
			cout << "OK";
	}
	
	if( entrance == 1 ){
		cout << "The string was not found!" << endl;
	}
	
	return 0;
}


int sgrep( const string targetStr, string lines[maxLineNum],int numOfLine,
															 int numFuncOpt )
{
	int numOfTrueChar=0, entrance=0;	// holds number of true character
	int i=0, j, k, n=0;
	int statK=0; cout << endl;
	
	int lenghtOfStr = findLenghtOfStr( targetStr );//finds lenght of the str you srchd
	
	for( j=0 ; j< numOfLine-1 ; ++j ){		//searchs the string and prints to console
		if( statK == 1 )
			--j;
		for( k=0; lines[j][k] != '\0' ; ++k ){
			if( statK == 1 ){ 	// Normally I decreased k to zero, whem I find target string
				k=0;			// but, k increases to 1 with for loop update mode and 
				statK=0;		// whem I find target string k becomes 1, not zero so that
			}					// I put the if stat here
			if( lines[j][k] == '\n' )	//if the first char in any line is nline char, pass other line
				++j;
			if( numFuncOpt != 1 && numFuncOpt != 3 ){
				while( lines[j][k] == targetStr[n] || targetStr[n] == '?'  ){
					++n;
					++k;
					++numOfTrueChar;
					
					if( numOfTrueChar == lenghtOfStr )
						break;
				}
			}else if( numFuncOpt == 1 || numFuncOpt == 3 ){
					
				/* If user entered -i, case sensitivity is ignored and prints
				   the lines that includes the string you want to search */
				while( lines[j][k] == targetStr[n] || targetStr[n] == '?' 
				   || static_cast<int>(lines[j][k]) == static_cast<int>(targetStr[n])-32 
				   || static_cast<int>(lines[j][k]) == static_cast<int>(targetStr[n])+32 ){
					++n;
					++k;
					++numOfTrueChar;
					if( numOfTrueChar == lenghtOfStr )
						break;
				}	
			}			
			if( numOfTrueChar == lenghtOfStr ){
				/* If the user entered -n, program prints to console the lines with
				   their line numbers */
				if( numFuncOpt == 2 || numFuncOpt == 3 )
					cout << (j+1) << "::";
				//prints the target lines
				cout << lines[j] << endl;
				numOfTrueChar=0;
				++j;		/*passes the other line, if the target str does not 
					          finds at the end of the line*/
				k=0;		//index of column
				n=0;
				statK = 1, entrance=1;
			}else {
				n=0;
				numOfTrueChar=0;	//if the target str finds, numOfTrueChar is getted zero				
			}
		}	
	}
	if( entrance == 0 )
		return 1;
}// END_OF_SGREP_FUNCTION

/* Finds lenght of the target string */
int findLenghtOfStr( string str ){
	int size;
	for( size=0 ; str[size] != '\0' ; ++size );

	return size;
}


int getLines( string lines[maxLineNum] )
{
	int i=0;
	cout << "Please enter strings( enter quit to exit )\n";

	getline( cin, lines[i]);	//gets first line and confirms the lines[i-1]
	
	//gets the string to array of string
	for( i=1 ; lines[i-1] != "quit"; ++i ){
	
		getline( cin, lines[i]);
						
	}
	
	return i;
}


int controllArgv( char *argv[], int argc )
{	
	// Is there the sting user search or not?  
	/* If the argc is equal to 2, runs sgrep without option */
	/* But, argc is equal to 3, runs with -i or -n */
	
	if( argc == 2 ) {
		return 1;
	}else if( argc == 3 ){
		if( argv[1][1] == 'i' ){
			return 2;	
			
		}else if( argv[1][1] == 'n' ){
			return 3;	
		}
	}else if( argc == 4 ){
		if( argv[1][1] == 'i' || argv[1][1] == 'n' ||
			argv[2][1] == 'i' || argv[2][1] == 'n' )
			return 4;	
	}else  {
		/* If you entered more or less arguman to console */
		cout << "Please enter valid arguments to command line!\n";
		cout << "You entered more or less arguments!" << endl;
		return 0;
	}
	
		
}

