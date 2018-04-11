/*##############################################################################
		               Ramazan SAKIN--111044069
  ##########################################################################
		                     CHESS GAME
################################################################################*/
#include<iostream>

using namespace std;

#define ROW  8
#define COL  8
#define numOfPiece  16
#define SENTINAL  -1

class BoardPosition{
  public:			
	BoardPosition();	//no parameter constructor
	BoardPosition( char postnX, char postnY );	//two-parameter constr.
	
	//setters
	bool isPosWhite( int x, int y )const{ return (x+y)%2 == 0? true: false; }
	void initChessBoard();
	void showChessBoard()const;
	int convCharToInt( char aPosition );
	
	//getters -- inline functions
	static int getNumOfPos(){ return NumOfPos; }
	int getPosX(){ return posX; }
	int getPosY(){ return posY; }
	char getName(){ return thePiece; }
	char getAchessPiece( int posx, int posy ){ return chessBoard[posy][posx]; }
	
  private:
  	char chessBoard[ROW][COL];
	char thePiece;
	int posX;
	int posY;
	static int NumOfPos;
	
};

int BoardPosition::NumOfPos = 0; //initialization for static int for class member 

int main(){	
	
	BoardPosition aPiece;
	aPiece.initChessBoard();
	aPiece.showChessBoard();
	
	char postnX, postnY;
	int positionX, positionY, status;
	
	while( status != SENTINAL ){
		do{
			cout << "Please enter coordinates for a board position: ";
			cin >> postnX >> postnY;
			aPiece = BoardPosition( postnX, postnY );
			positionX = aPiece.convCharToInt( postnX );
			positionY = aPiece.convCharToInt( postnY );
			
			if( positionX == -1 || positionY == -1 )
				cout << "You entered invalid position!Enter again:\n-> ";
		}while( positionX == -1 || positionY == -1  );
	
		bool isWhite;
		isWhite = aPiece.isPosWhite( positionX, positionY );

		if( isWhite == true )
			cout << "The position is white"<< endl;
		else
			cout << "The position is black" << endl;	
		
		cout << "You want to ask a position, enter 1. if not enter -1\n-> ";
		cin >> status;
		if( status != 1 )
			break;
	}
	cout <<endl << "There are "<< aPiece.getNumOfPos() <<" position(s) that was created" <<endl;
	// -1 for the first decleration
	return 0;
}

BoardPosition::BoardPosition():posX(0), posY(0) //member initializer list
{ ++NumOfPos; }

BoardPosition::BoardPosition( char postnX, char postnY )
:posX(postnX), posY(postnY) 
{
	if( !(((posX > 'A' || posX > 'a') && ( posY > '0' || posY < '9' ))) ){	
		cout << "Please enter valid coordinates!" << endl;
	}else 	
		++NumOfPos;
		 
}

// Initializes the first status of chess Board and values of the stones 
void BoardPosition::initChessBoard(  )
{
	int i,j, k, t=0;
	
	chessBoard[0][0] = 'k';  chessBoard[7][0] = 'K';   
	chessBoard[0][1] = 'a';	 chessBoard[7][1] = 'A';	
	chessBoard[0][2] = 'f';	 chessBoard[7][2] = 'F';
	chessBoard[0][3] = 'v';	 chessBoard[7][3] = 'V';
	chessBoard[0][4] = 's';	 chessBoard[7][4] = 'S';
	chessBoard[0][5] = 'f';	 chessBoard[7][5] = 'F';
	chessBoard[0][6] = 'a';	 chessBoard[7][6] = 'A';
	chessBoard[0][7] = 'k';	 chessBoard[7][7] = 'K';
	
	for( i=0; i<numOfPiece/2 ; ++i )		
		chessBoard[1][i]  = 'p';
		
	for( i=2 ; i<6 ; ++i ){ 				
		for( j=0; j<COL ; ++j ){
			chessBoard[i][j] = '.';
		}
	}
		
	for( k=0; k<numOfPiece/2 ; ++k )		
		chessBoard[6][k]  = 'P';

}
//Show the current chess Board
void BoardPosition::showChessBoard(  )const
{
	
	for( int i=0; i<ROW; ++i ){
		for( int j=0; j<COL ; ++j ){
			cout << chessBoard[i][j] << " ";
		}
		cout << "|" <<ROW-i << endl;	
	}
	cout << "---------------" << endl;
	cout <<"A B C D E F G H"<< endl << endl;
}


//converts the character to integer
int BoardPosition::convCharToInt( char aPosition )
{
	switch( aPosition ){
		case 'H': case 'h': case '1':
			return 7;  break;
		case 'G': case 'g': case '2':
			return 6;  break;
		case 'F': case 'f': case '3':
			return 5;  break;
		case 'E': case 'e': case '4':
			return 4;  break;
		case 'D': case 'd': case '5':
			return 3;  break;
		case 'C': case 'c': case '6':
			return 2;  break;
		case 'B': case 'b': case '7':
			return 1;  break;		
		case 'A': case 'a': case '8':
			return 0;  break;
		default:
			cout << "Invalid moving!\nPlease enter valid coordinates to go on"<<endl;	
			return -1;	//when the user enter wrong coordinates	
	}	
}

