/*##############################################################################
		               Ramazan SAKIN--111044069
  ##########################################################################
		                     CHESS GAME
################################################################################*/
#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

using namespace std;

const int ROW        =  8;
const int COL        =  8;
const int numOfPiece = 16;

class BoardPosition{
  public:			
	BoardPosition();	//no parameter constructor
	BoardPosition( char postnX, char postnY );	//two-parameter constr.
	
	//setters
	bool isPosWhite( char aPiece ){ bool sts=(aPiece=='b') ? true : false; return sts; }
	void setPosX( int sposX );
        void setPosY( int sposY );
        
	//getters -- inline functions
	static int getNumOfPos(){ return numOfPos; }
	int getPosX()const{ return posX; }
	int getPosY()const{ return posY; }
	
  private:
	int posX;
	int posY;
	static int numOfPos;
	
};

class ChessBoard;       //forward declaration

class ChessPiece{
  public:
        ChessPiece( bool first );	// Constructor without parameter
        //setters
        bool canMove( int index, BoardPosition& aPosition );
	friend class ChessBoard;
	//getters                                                 
  	string getName()const{ return name; }
  	bool getIsEaten()const{ return isEaten; }
  	bool getIsFirst()const{ return isFirst; }
  	char getTeam()const{ return team; }
        char getCName()const{ return cName; }
        bool atTeam( int newPosX, int newPosY )const;
        bool atTeamBlack( int newPosX, int newPosY )const;
        
  	//Checking functions
        int checkMoving( int indexOfPiece, int newPosX,int newPosY )const;
	int checkRook( bool eaten, int indexOfPiece, int oldPosX, int oldPosY, int newPosX,int newPosY )const;
        int checkKnight( bool eaten, int indexOfPiece, int oldPosX, int oldPosY, int newPosX,int newPosY )const;
	int checkBishop( bool eaten, int indexOfPiece, int oldPosX, int oldPosY, int newPosX,int newPosY )const;
	int checkQueen( bool eaten, int indexOfPiece, int oldPosX, int oldPosY, int newPosX,int newPosY )const;
	int checkKing( bool eaten, int indexOfPiece, int oldPosX, int oldPosY,
                        int newPosX,int newPosY, bool checkBishop, bool checkRook )const;
	int checkWhitePawn( bool eaten, char thePiece, int oldPosX, int oldPosY,  int newPosX,int newPosY )const;
	int checkBlackPawn( bool eaten, char thePiece, int indexOfPiece, int oldPosX, int oldPosY, int newPosX,int newPosY )const;
        
        int canPass( bool isEaten, int index, int oldPosX, int oldPosY, int newPosX, int newPosY )const;
        int canPassWPawn( int oldPosX, int oldPosY, int newPosX, int newPosY )const;
	int canPassBPawn( int oldPosX, int oldPosY,int newPosX, int newPosY )const;
	int canPassRook( int oldPosX, int oldPosY,int newPosX, int newPosY )const;
	int canPassBishop( int oldPosX, int oldPosY,int newPosX, int newPosY )const;
	int canPassKing( int oldPosX, int oldPosY, int newPosX, int newPosY )const;
	int canPassQueen( int oldPosX, int oldPosY, int newPosX, int newPosY )const;
        
        //random moving functions
        
        //setters
        void setTeam(char sTeam);
        void setName(string sName);
        void setIsFirst( bool stat );
        void setIsEaten( bool stat );
        void setCName( char charName );
        
        BoardPosition thePiece;
        
  private:
	char team;
	string name;
	bool isEaten;
	bool isFirst;
        char cName;

};


int BoardPosition::numOfPos = 0;

class ChessBoard{
  public:
        
  	ChessBoard();	//no-parameter cnstr. for base case
        bool moveBlack(const BoardPosition& source , const BoardPosition& dest);
        bool moveWhite(const BoardPosition& source , const BoardPosition& dest);
        int convCharTOInt( char move );
	void placedPiecesTochessBoard( );
	void showchessBoard( );
	int playManually( );
	int searchPiece( int postnX, int postnY )const;
        int searchBlackPiece( int postnX, int postnY )const;
	void isEatenPiece( int indexOfPiece );
	int playRandomly( );
	int randMoving( int randNum );
        void setApiece( int X, int Y, char ch );
        
        //checks can pass or not pass   
	void lostMessage()const{ cout << "\n\n######  You lost the game  #######\n\n"; }
	void winMessage()const{ cout <<  "\n\n######  You won the game  #######\n\n"; }
         
	//getters
	char chessBoard[ROW][COL];
        
        static int  getNumberMoving(){ return movingNumber; }
	ChessPiece  getAwhitePiece( int index ){ return  whitePieces[index]; }
	ChessPiece  getAblackPiece( int index ){ return  blackPieces[index]; }
        char getApieceFrCB( int newPosX, int newPosY );
	
        //move randomlly
        int moveRook( bool eaten, int randNum );
	int movePawn( bool eaten, int randNum );
	int moveKnight( bool eaten, int randNum );
	int moveKing( bool eaten, int randNum );
	int moveBishop( bool eaten, int randNum );
	int moveQueen( bool eaten, int randNum );
	int canQueenEat( int randNum );

  private:
    static int movingNumber;
    vector<ChessPiece>  blackPieces;
    vector<ChessPiece>  whitePieces;
    
};

int ChessBoard::movingNumber = 0;	//init. to zero

int main(){
	ChessBoard aChessBoard;
	srand(time(NULL));
	
	int movingNum=0, validity;
        
	while( aChessBoard.getAwhitePiece(4).getIsEaten() != true ){	// 4 for the white queen's index
		//system("clear");
		aChessBoard.showchessBoard();
		++movingNum;
		
                do{
                  cout << "move  "<< movingNum <<endl;  
		  validity = aChessBoard.playManually();
		}while( validity == -1 );
                  
		if( aChessBoard.getAblackPiece(4).getIsEaten() == true ){
			aChessBoard.winMessage();
			return 0;
		}
		//system("clear");
		aChessBoard.showchessBoard();
		++movingNum;
		
		do{
                  cout << "move " << movingNum << " Computer"<< endl;  
		  validity = aChessBoard.playRandomly();
		}while( validity == -1 );		
		
		if( aChessBoard.getAwhitePiece(4).getIsEaten() == true ){
			aChessBoard.lostMessage();
			return 0;
		}
	}

	return 0;
}

// Initializes the first status of chess Table and values of the Pieces 
ChessBoard::ChessBoard(  )
{
    /*for(int i=0;i<16;++i)
        blackPieces.push_back(i);
	int i, j, k;*/
    ChessPiece aPiece(true);
    
    //black pieces
    for( int i=0; i<16; ++i )
	blackPieces.push_back(aPiece);
        
        blackPieces[0].setName("rook");
        blackPieces[1].setName("knight");
        blackPieces[2].setName("bishop");    
	blackPieces[3].setName("king");	    
	blackPieces[4].setName("Queen");	    
	blackPieces[5].setName("bishop");    
	blackPieces[6].setName("knight");    
	blackPieces[7].setName("rook");	    
        for( int j=0 ;j<16; ++j )
            whitePieces.push_back(aPiece);
        //white pieces
        whitePieces[0].setName("rook");        
        whitePieces[1].setName("knight");
        whitePieces[2].setName("bishop");    
	whitePieces[3].setName("king");	    
	whitePieces[4].setName("Queen");	    
	whitePieces[5].setName("bishop");    
	whitePieces[6].setName("knight");    
        whitePieces[7].setName("rook");	    
        ;
        whitePieces[0].setCName('K');   blackPieces[0].setCName('k');
        whitePieces[1].setCName('A');   blackPieces[1].setCName('a');     
        whitePieces[2].setCName('F');   blackPieces[2].setCName('f');
        whitePieces[3].setCName('V');   blackPieces[3].setCName('v');
        whitePieces[4].setCName('S');   blackPieces[4].setCName('s');
        whitePieces[5].setCName('F');   blackPieces[5].setCName('f');
        whitePieces[6].setCName('A');   blackPieces[6].setCName('a'); 
        whitePieces[7].setCName('K');   blackPieces[7].setCName('k');
        
	for( int i=8; i<numOfPiece ; ++i ){	
            whitePieces[i].setName("pawn");
        }
	
	for(int  k=8; k<numOfPiece ; ++k ){		
            blackPieces[k].setName("pawn");
        }
        
        for(int  j=8; j<numOfPiece; ++j ){
            blackPieces[j].setCName('p');
            whitePieces[j].setCName('P');
        }
        
	for( int l=0;l<numOfPiece; ++l ){
		whitePieces[l].setTeam('w');
		blackPieces[l].setTeam('b');
	}
        
	placedPiecesTochessBoard(  );
}

//places the Pieces to chess table
void ChessBoard::placedPiecesTochessBoard(  )
{
	int i,j,k,t;
        
	t=0;	//coordinates for black team
	for( i=0 ; i<2 ; ++i ){ 				
		for( j=0; j<COL ; ++j ){
			chessBoard[i][j] = blackPieces[t].getCName();
			blackPieces[t].thePiece.setPosX(j);
			blackPieces[t].thePiece.setPosY(i);
			++t;
		}
	}
	
	for( i=2 ; i<6 ; ++i ){ 				
		for( j=0; j<COL ; ++j ){
                    chessBoard[i][j] = '.';
		}
	}
	
	t=0;	//coordinates for white team
	for( i=7 ; i>5 ; --i ){ 				
		for( j=0; j<COL ; ++j ){
			chessBoard[i][j] = whitePieces[t].getCName();
			whitePieces[t].thePiece.setPosX(j);
			whitePieces[t].thePiece.setPosY(i);		
			++t;
		}
	}//for initials statuses..
	for(i=0; i<16; ++i){
		blackPieces[i].setIsFirst(true);
		whitePieces[i].setIsEaten(false);
		blackPieces[i].setIsFirst(true);
		whitePieces[i].setIsEaten(false);
	}
		
}


//Show the current ches table
void ChessBoard::showchessBoard( )
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


//user plays and this function checks user's moving
int ChessBoard::playManually(  ){
    
	char move,  ignoreMe;
	BoardPosition aPosition;
        int oldPosX, oldPosY, newPosX, newPosY;
	int PieceIndex;
	cin >> move;
	oldPosX = convCharTOInt(move);
	cin >> move;
	oldPosY = convCharTOInt( move );
        
	cin >> ignoreMe;	//for - character or any else
	cin >> move;	
	newPosX = convCharTOInt( move );
	cin >> move;
	newPosY = convCharTOInt( move );
	
	if( newPosX == -1 || newPosY == -1 )
		return -1;	//play again with valid moving
	if( chessBoard[oldPosY][oldPosX] == '.' )
            return -1;
            
        PieceIndex = searchPiece( oldPosX, oldPosY );
        bool stat = whitePieces[PieceIndex].atTeam( newPosX, newPosY );
        
        if( PieceIndex == -1 ){
		cout << "You can not eat your Pieces!Move again\n";
		return -1;
	}
        aPosition.setPosX(newPosX);
        aPosition.setPosY(newPosY);
        bool validity = whitePieces[PieceIndex].canMove(PieceIndex, aPosition );
        if( validity == false )
            return -1;
        
        whitePieces[PieceIndex].thePiece.setPosX(newPosX);
	whitePieces[PieceIndex].thePiece.setPosY(newPosY);
	
	int enemyIndex = searchBlackPiece( newPosX, newPosY );
        if( enemyIndex != -1 )
            isEatenPiece( enemyIndex );
	whitePieces[PieceIndex].setIsFirst(false);	//for Pawns
	
	chessBoard[newPosY][newPosX] = chessBoard[oldPosY][oldPosX];	
	chessBoard[oldPosY][oldPosX] = '.';
	cout << endl;
	
	return 1;	//There is no problem*/
}

//converts the character to integer

int ChessBoard::convCharTOInt( char move )
{
	switch( move ){
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

int ChessBoard::searchPiece( int posX, int posY )const
{ 	
	int i, j;
	for(  i=0; i<16 ; ++i ){
		if( whitePieces[i].thePiece.getPosX() == posX && 
                    whitePieces[i].thePiece.getPosY() == posY &&
                    whitePieces[i].getTeam() == 'w'          )
               		return i;
	}
	return -1;	//There is not or **error**
}

int ChessBoard::searchBlackPiece( int posX, int posY )const
{
    int i, j;
	for(  i=0; i<16 ; ++i ){
		if( blackPieces[i].thePiece.getPosX() == posX && 
                    blackPieces[i].thePiece.getPosY() == posY &&
                    blackPieces[i].getTeam() == 'b'          )
               		return i;
	}
	
	return -1;	//There is not or **error**
        
}

//checks user's moving  with the helper functions
//And also checks the moving of black Pieces
//If user or black Pieces played wrongly, it is neccessary to play again to continue
int ChessPiece::checkMoving( int indexOfPiece, int newPosX,int newPosY )const
{
 int control;
 cout << indexOfPiece << getName()<<endl;
 switch(indexOfPiece+1){
	case 1:  case 8:
          control= checkRook( getIsEaten(),
                   indexOfPiece, thePiece.getPosX(),
                   thePiece.getPosY(), newPosX, newPosY );
	  break;
        case 2:  case 7:
	  control= checkKnight( getIsEaten(), 
                   indexOfPiece, thePiece.getPosX(),
                   thePiece.getPosY(), newPosX, newPosY );
	  break;
	case 3:  case 6:
	  control=checkBishop( getIsEaten(),
                  indexOfPiece, thePiece.getPosX(),
                  thePiece.getPosY(), newPosX, newPosY);
	  break;
	case 4:
	  control=checkKing( getIsEaten(), 
                  indexOfPiece, thePiece.getPosX(),
                  thePiece.getPosY(), newPosX, newPosY,
                  checkBishop( getIsEaten(),
                  indexOfPiece, thePiece.getPosX(),
                  thePiece.getPosY(), newPosX, newPosY),
                  checkRook( getIsEaten(),
                  indexOfPiece, thePiece.getPosX(),
                  thePiece.getPosY(), newPosX, newPosY ) );
	  break;
	case 5:
	  control=checkQueen( getIsEaten(), 
                  indexOfPiece, thePiece.getPosX(),
                  thePiece.getPosY(), newPosX, newPosY);
	  break;
	case 9:  case 10: case 11:  case 12:
	case 13: case 14: case 15:  case 16:
            if( atTeam(thePiece.getPosX(), thePiece.getPosY()) )
	  control=checkWhitePawn( getIsEaten(), indexOfPiece, thePiece.getPosX(),
                                         thePiece.getPosY(), newPosX, newPosY );
            else
          control=checkBlackPawn(getIsEaten(),'.' ,indexOfPiece, thePiece.getPosX(),
                                         thePiece.getPosY(), newPosX, newPosY );      
	  break;
	default:
	  return -1;	//if there is an error
 }
	return control;
}

//if a black team's component was eaten, that Piece should not be used 
void ChessBoard::isEatenPiece( int indexOfPiece )
{
    blackPieces[indexOfPiece].setIsEaten(false);
}

//Checking  Functions..
//checks the Pieces' movings
int ChessPiece::checkRook(bool eaten, int indexOfPiece, int oldPosX, int oldPosY, int newPosX, int newPosY) const
{
    if( eaten != true     ){    
    if( newPosX >= 0 && newPosY < 8  && 
       (abs(newPosX-newPosX) == 0) || (abs(oldPosY-newPosY)==0) )
        return 1;
    else 
        return -1;    
    }else
        return -1;
}


int ChessPiece::checkKnight( bool eaten,int indexOfPiece, int oldPosX, int oldPosY,int newPosX,int newPosY )const
{	
	if( eaten != true   ){
		if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8
		    && oldPosX != newPosX && oldPosY != newPosY 
		    && abs(newPosX-oldPosX)+abs(newPosY-oldPosY) == 3 ) // +2 X or Y and
			return 1;											// +1 for other one(3)
		else
			return -1;
	}else
		return -1;
}

int ChessPiece::checkBishop(bool eaten, int indexOfPiece, int oldPosX, int oldPosY,
                             int newPosX, int newPosY) const
{	
	if( eaten != true   ){
		if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8 &&
                    oldPosX != newPosX && oldPosY != newPosY &&
		    abs( oldPosX-newPosX ) == abs( oldPosY-newPosY ) )
			return 1;
		else
			return -1;
	}else
		return -1;
}


int ChessPiece::checkQueen(bool eaten, int indexOfPiece, int oldPosX, int oldPosY,
                            int newPosX, int newPosY) const
{
	if( eaten != true  ){
		if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8
		    && ( abs(oldPosX-newPosX)==1 || abs( oldPosY-newPosY ) )== 1 )
			return 1;
		else
			return -1;	
	}else
		return -1;
}

int ChessPiece::checkKing(bool eaten, int indexOfPiece, int oldPosX, int oldPosY,
                           int newPosX, int newPosY, bool checkBishop, bool checkRook ) const
{
	if( eaten != true ){
	  if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8 &&
	    (checkBishop == true || checkRook == true ) )
		return 1;
	  else
	  	return -1;	
	}else
		return -1;
}

int ChessPiece::checkWhitePawn(bool eaten, char thePiece, int oldPosX,
                                               int oldPosY, int newPosX, int newPosY) const
{	
	if( eaten != true && thePiece == '.'
	    && isFirst == true  ){
			if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8 &&
				oldPosX == newPosX && (oldPosY-2 == newPosY || oldPosY-1 == newPosY) )
				return 1;
			else if( !isFirst && oldPosX >= 0 && oldPosX < 8 
			         && newPosY >= 0 && newPosY < 8 && oldPosX == newPosX && 
			                                              oldPosY-1 == newPosY )
			    return 1;	//you can go only one step
			else		    
			    return -1;
		}else if( thePiece != '.' ){
			if(( oldPosX-1==newPosX && oldPosY-1==newPosY ) || 
		  	(oldPosX+1==newPosX && oldPosY-1==newPosY ) ){
		  		return 1;	//if the Pawn eats a Piece, ..	
		  	}else
				return -1;
	}
	
}


int ChessPiece::checkBlackPawn(bool eaten, char thePiece, int indexOfPiece,
        int oldPosX, int oldPosY, int newPosX, int newPosY) const
{	
	if( isEaten != true && thePiece == '.'     ){
			if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8 &&
				oldPosX == newPosX && ( oldPosY+2 == newPosY || oldPosY+1 == newPosY ) )
				return 1;
			else
				return -1;
		}else if( thePiece != '.' ){
			if(( oldPosX-1==newPosX && oldPosY+1==newPosY ) || 
		  	(oldPosX+1==newPosX && oldPosY+1==newPosY ) ){
		  		return 1;	//if the Pawn eats a Piece, ..	
		  	}else
				return -1;
	}
	
}


//is the searched Piece in my team or other team
bool ChessPiece::atTeam( int newPosX, int newPosY )const
{
	for( int i=0; i<numOfPiece ; ++i ){
		if( newPosX == thePiece.getPosX() &&
                    newPosY == thePiece.getPosY()   )	
			return true;
	}

	return false;
}


bool ChessPiece::atTeamBlack( int newPosX, int newPosY )const
{
	for( int i=0; i<numOfPiece ; ++i ){
		if( newPosX == thePiece.getPosX() &&
                    newPosY == thePiece.getPosY()   )	
			return true;
	}

	return false;
}


//If there is a Piece that is in your team of your front, you can not pass above of it...
//This function controls the Piece which want to pass above its own team's Piece
//Also, this fuction checks enemyPieces that can pass or can not pass
int ChessPiece::canPass(bool isEaten,int index, int oldPosX, int oldPosY,  int newPosX, int newPosY) const
{
    
	int status=0;
	if( getCName() == 'P' ){
            status=canPassWPawn( oldPosX,oldPosY,newPosX,newPosY);
        }else if( getCName() == 'p' ){
            status=canPassBPawn( oldPosX,oldPosY,newPosX,newPosY);    
	}else if( getCName() == 'K' || getCName() == 'k' ){
	    status=canPassRook( oldPosX,oldPosY,newPosX,newPosY);
	}else if( getCName() == 'F' || getCName() == 'f' ){
	    status=canPassBishop( oldPosX,oldPosY,newPosX,newPosY);
	}else if( getCName() == 'V' || getCName() == 'v' ){
	    status=canPassKing( oldPosX,oldPosY,newPosX,newPosY);
	}else if( 'S'==getCName() ||  's' == getCName() ){
	    status=canPassQueen( oldPosX,oldPosY,newPosX,newPosY);
	}

	return status;
}


//checks the Pawn
int ChessPiece::canPassWPawn(int oldPosX, int oldPosY, int newPosX, int newPosY) const
{
	if( newPosY==oldPosY-2 )
        if( atTeam(newPosX, newPosY) == true )
	    return -1;
	return 1;
}


int ChessPiece::canPassBPawn(int oldPosX, int oldPosY, int newPosX, int newPosY) const
{
	if( newPosY==oldPosY+2 )
            if( atTeamBlack(newPosX, newPosY) == true )
		return -1;
	return 1;
}

int ChessPiece::canPassRook( int oldPosX, int oldPosY, int newPosX, int newPosY) const
{ 
	int i;
	if( oldPosY-newPosY > 1 ){
	  for( i=newPosY; i<oldPosY; ++i ){
              if( !islower(getCName()) ){
		if( atTeam(newPosX, i) )
			return -1;
              }else{
                 if( atTeamBlack(newPosX, i) )
			return -1; 
              }
            }
                  
	}else if( newPosY-oldPosY > 1 ){
	  for( i=newPosY; i>oldPosY; --i ){
              if( !islower(getCName()) ){
		if( atTeam(newPosX, i) )
			return -1;
              }else{
                 if( atTeamBlack(newPosX, i) )
			return -1; 
              }
            }	
	}else if( newPosX-oldPosX > 1 ){
	  for( i=newPosX; i>oldPosX; --i ){
              if( !islower(getCName()) ){
		if( atTeam(i, newPosY) )
			return -1;
              }else{
                 if( atTeamBlack(i, newPosY) )
			return -1; 
              }
            }
	}else if( oldPosX-newPosX > 1 ){
	  for( i=newPosX ; i<oldPosX; ++i ){
              if( !islower(getCName()) ){
		if( atTeam(i, newPosY) )
			return -1;
              }else{
                 if( atTeamBlack(i, newPosY) )
			return -1; 
              }
            }	
	}	
	
	return 1;
}

int ChessPiece::canPassBishop( int oldPosX, int oldPosY, int newPosX, int newPosY) const
{	
	int i,j;
	//checks is a Piece front on my way? , controls coordinates...
	if( oldPosY>newPosY && oldPosX>newPosX ){
	  for( i=newPosX,j=newPosY; i<oldPosX, j<oldPosY; ++i, ++j ){
              if( !islower(getCName()) ){
		if( atTeam(j, i) )
			return -1;
              }else{
                 if( atTeamBlack(j, i) )
			return -1; 
              }
            }
	}else if( oldPosY>newPosY && oldPosX<newPosX ){
	  for( i=newPosX,j=newPosY; i>oldPosX, j<oldPosY; --i, ++j ){
              if( !islower(getCName()) ){
		if( atTeam(j, i) )
			return -1;
              }else{
                 if( atTeamBlack(j, i) )
			return -1; 
              }
            }
	}else if( oldPosY<newPosY && oldPosX>newPosX  ){
	  for( i=newPosX,j=newPosY; i<oldPosX, j>oldPosY; ++i, --j ){
              if( !islower(getCName()) ){
		if( atTeam(j, i) )
			return -1;
              }else{
                 if( atTeamBlack(j, i) )
			return -1; 
              }
            }
	}else if( oldPosY<newPosY && oldPosX<newPosX  ){
	  for( i=newPosX,j=newPosY; i>oldPosX, j>oldPosY; --i, --j ){
              if( !islower(getCName()) ){
		if( atTeam(j, i) )
			return -1;
              }else{
                 if( atTeamBlack(j, i) )
			return -1; 
              }
            }
	}
	return 1;
}

//if the Piece can go either like a Knight or like a Rook, the Piece is King...
int ChessPiece::canPassKing( int oldPosX, int oldPosY, int newPosX, int newPosY) const{	
	if( abs( oldPosX-newPosX ) == 0 || abs( oldPosY-newPosY ) == 0 ){
	    if( canPassRook( oldPosX, oldPosY, newPosX, newPosY) == 1)
			return 1;
	}else if( abs(oldPosX - newPosX) == abs( oldPosY-newPosY ) ){
		if( canPassBishop( oldPosX, oldPosY, newPosX, newPosY) == 1 )
			return 1;			
	}else 
		return -1;

}

int ChessPiece::canPassQueen( int oldPosX, int oldPosY, int newPosX, int newPosY) const
{
              if( !islower(getCName()) ){
		if( atTeam(newPosX, newPosY) )
			return -1;
              }else{
                 if( atTeamBlack(newPosX, newPosY) )
			return -1; 
              }
	return 1;	
}

//the black team plays randomly, chooses a Piece with random index and 
//chooses random X and Y coordinates and checks the Piece can pass x and y coor.
//checks is there a Piece that is same team and check moving --valid or unvalid
int ChessBoard::playRandomly( )
{	//choosing a Piece randomly
	int randNum = rand()%16 ,  status;
	
	status = randMoving( randNum );	
	return status;
}                                               

// move the Piece that specify with rand number, which Piece?
int ChessBoard::randMoving(int randNum)
{
	int status;
        bool isEaten = blackPieces[randNum].getIsEaten();
	switch(randNum){
		case 0:  case 7:
			status = moveRook( isEaten,randNum);
	    	break;
		case 1:  case 6:
			status = moveKnight( isEaten, randNum);
			break;
		case 2:  case 5:
			status = moveBishop( isEaten, randNum);
			break;	
		case 3:
			status = moveKing( isEaten, randNum );
			break;
		case 4:
			status = moveQueen( isEaten, randNum);
			break;
		default:	//At the other cases 	
		status = movePawn(isEaten, randNum);
	}
	
	return status;	//play again if status is -1, o.w go on..
}

int ChessBoard::moveRook( bool eaten, int randNum)
{
	int whichPos = rand()%2;        //which aspect should the Rook go randomly?
	BoardPosition aPosition;
	
        if( whichPos == 0 ){			//and go along towards X or Y randomly
                aPosition.setPosX(rand()%3 + blackPieces[randNum].thePiece.getPosX());
                // moving randm step to X
		aPosition.setPosY(blackPieces[randNum].thePiece.getPosY());
        }else {
	  aPosition.setPosX(rand()%3+blackPieces[randNum].thePiece.getPosX());	//moving random step to Y
	  aPosition.setPosY(blackPieces[randNum].thePiece.getPosY());
	}
	
	bool validity = blackPieces[randNum].canMove(randNum, aPosition );
        
	if( validity == -1 )
		return -1;
	else { 
            
                setApiece(blackPieces[randNum].thePiece.getPosX(),blackPieces[randNum].thePiece.getPosY(),'.');
		blackPieces[randNum].thePiece.setPosX(aPosition.getPosX());
                blackPieces[randNum].thePiece.setPosY(aPosition.getPosY());
		setApiece(aPosition.getPosX(),aPosition.getPosY(),blackPieces[randNum].getCName());
                
	}
  	return 1;
}

int ChessBoard::moveBishop( bool eaten,int randNum )
{
	int randomNum = rand()%4;
	BoardPosition aPosition;
        
        aPosition.setPosY(randomNum + blackPieces[randNum].thePiece.getPosY());
        // not to cross the frontier
	if( aPosition.getPosY()%2 == 0 )
		aPosition.setPosX(blackPieces[randNum].thePiece.getPosX() + randomNum);
	else
		aPosition.setPosX(blackPieces[randNum].thePiece.getPosX() - randomNum);
		
	bool validity = blackPieces[randNum].canMove(randNum, aPosition );
        
	if( validity == -1 )
		return -1;
	else {
                setApiece(blackPieces[randNum].thePiece.getPosX(),blackPieces[randNum].thePiece.getPosY(),'.');
		blackPieces[randNum].thePiece.setPosX(aPosition.getPosX());
                blackPieces[randNum].thePiece.setPosY(aPosition.getPosY());
		setApiece(aPosition.getPosX(),aPosition.getPosY(),blackPieces[randNum].getCName());
	}
  	return 1;
}

int ChessBoard::movePawn( bool eaten,int randNum )
{
  BoardPosition aPosition;
  
	if( blackPieces[randNum].getIsFirst() == true )
		aPosition.setPosY(rand()%2 + 1 + blackPieces[randNum].thePiece.getPosY());
	else  //If the Pawn was played second time or more, the Pawn can go one step
		aPosition.setPosY(1 + blackPieces[randNum].thePiece.getPosY());		
	
	aPosition.setPosX(blackPieces[randNum].thePiece.getPosX());
		
	bool validity = blackPieces[randNum].canMove(randNum, aPosition );
        
	if( validity == -1 )
		return -1;
	else {
                setApiece(blackPieces[randNum].thePiece.getPosX(),blackPieces[randNum].thePiece.getPosY(),'.');
		blackPieces[randNum].thePiece.setPosX(aPosition.getPosX());
                blackPieces[randNum].thePiece.setPosY(aPosition.getPosY());
		setApiece(aPosition.getPosX(),aPosition.getPosY(),blackPieces[randNum].getCName());
	}
  	return 1;
}

int ChessBoard::moveKnight(bool eaten, int randNum )
{
	int randNumber = rand()%2, newX, newY;
	int randNumber2 = rand()%2, randNumber3 = rand()%2;
	BoardPosition aPosition;
        
	//play randomly
	if( randNumber == 0 ){
		aPosition.setPosX(2 + blackPieces[randNum].thePiece.getPosX());
		if( randNumber2 == 0 )
			aPosition.setPosY(1 + blackPieces[randNum].thePiece.getPosY());		
                else	
			aPosition.setPosY(-1 + blackPieces[randNum].thePiece.getPosY());
	}else{
		aPosition.setPosY(2 + blackPieces[randNum].thePiece.getPosY());
		if( randNumber3 == 0 ) 
			aPosition.setPosX(1+ blackPieces[randNum].thePiece.getPosX());
		else
			aPosition.setPosX(-1+ blackPieces[randNum].thePiece.getPosX());
	}

	bool validity = blackPieces[randNum].canMove(randNum, aPosition );
        
	if( validity == -1 )
		return -1;
	else {
            
                setApiece(blackPieces[randNum].thePiece.getPosX(),blackPieces[randNum].thePiece.getPosY(),'.');
		blackPieces[randNum].thePiece.setPosX(aPosition.getPosX());
                blackPieces[randNum].thePiece.setPosY(aPosition.getPosY());
		setApiece(aPosition.getPosX(),aPosition.getPosY(),blackPieces[randNum].getCName());
	}
  	return 1;
}

int ChessBoard::moveKing( bool eaten,int randNum )
{
        int randNumber;
	BoardPosition aPosition;
        
	randNumber = rand()%4;
	aPosition.setPosX(randNumber + blackPieces[randNum].thePiece.getPosX());
	
	if( aPosition.getPosX()%2 == 0 )
		aPosition.setPosY(blackPieces[randNum].thePiece.getPosY());
	else if( randNumber = rand()%2 == 1  )
		aPosition.setPosY(blackPieces[randNum].thePiece.getPosY() + randNumber);
	else
		aPosition.setPosY(blackPieces[randNum].thePiece.getPosY() - randNumber);
			
	bool validity = blackPieces[randNum].canMove(randNum, aPosition );
        
	if( validity == -1 )
		return -1;
	else {
                setApiece(blackPieces[randNum].thePiece.getPosX(),blackPieces[randNum].thePiece.getPosY(),'.');
		blackPieces[randNum].thePiece.setPosX(aPosition.getPosX());
                blackPieces[randNum].thePiece.setPosY(aPosition.getPosY());
		setApiece(aPosition.getPosX(),aPosition.getPosY(),blackPieces[randNum].getCName());
	}
  	return 1;
}

int ChessBoard::moveQueen( bool eaten, int randNum  )
{
	bool  validity;
	BoardPosition aPosition;
        
	aPosition.setPosX(rand()%2 + blackPieces[randNum].thePiece.getPosX());	
	aPosition.setPosY(rand()%2 + blackPieces[randNum].thePiece.getPosY());	
	
	validity =blackPieces[randNum].canMove(randNum, aPosition );
        
	if( validity == -1 )
		return -1;
	else {
                setApiece(blackPieces[randNum].thePiece.getPosX(),blackPieces[randNum].thePiece.getPosY(),'.');
		blackPieces[randNum].thePiece.setPosX(aPosition.getPosX());
                blackPieces[randNum].thePiece.setPosY(aPosition.getPosY());
		setApiece(aPosition.getPosX(),aPosition.getPosY(),blackPieces[randNum].getCName());
	}
  	return 1;
  	
}


//if there is a Piece next to the black Queen, Queen can eat the Piece but 
//when the randNum is 4(indexOfBlckQueen) 
int ChessBoard::canQueenEat( int randNum)
{
    int oldPosX= blackPieces[randNum].thePiece.getPosX();
    int oldPosY= blackPieces[randNum].thePiece.getPosY();    
    
        for( int i=0; i<3; ++i )
          for( int j=0; j<3; ++j ){
      	    if( !blackPieces[randNum].atTeamBlack((oldPosX-1+i),(oldPosY-1+j)) ){
      		if( i != 1 && j != 1 ){
      			setApiece((oldPosX-1+i),(oldPosY-1+j),blackPieces[randNum].getCName());
      			setApiece(oldPosX, oldPosY, '.');
      			blackPieces[randNum].thePiece.setPosX(oldPosX-1+j);
                        blackPieces[randNum].thePiece.setPosY(oldPosY-1+i);
      			return 1;
      	   }
        }         
      }
	return -1;
}


BoardPosition::BoardPosition(char postnX, char postnY):posX(postnX), posY(postnY)
{ ++numOfPos; }

BoardPosition::BoardPosition()
{ ++numOfPos; }


bool ChessPiece::canMove( int index, BoardPosition& aPosition )
{
    bool validity1, validity2;
 
    validity1 = checkMoving(index, aPosition.getPosX(), aPosition.getPosY() );
    validity2 = canPass(getIsEaten(), index, thePiece.getPosX(),thePiece.getPosY(),
                         aPosition.getPosX(), aPosition.getPosY());
    
    if( !islower(getCName()) ){
        if(atTeam(aPosition.getPosX(), aPosition.getPosY()))
            return false;
    }else{
        if(atTeamBlack(aPosition.getPosX(), aPosition.getPosY()))
            return false;
    }    
        
    if( validity1 == -1 || validity2 == -1 )
        return false;
    else 
        return true;
}

void BoardPosition::setPosX(int sposX){
    posX = sposX;
}

void BoardPosition::setPosY(int sposY){
    posY = sposY;
}

void ChessPiece::setIsFirst(bool stat){
    isFirst = stat;
}

void ChessPiece::setCName(char charName){
     cName= charName;
}

void ChessPiece::setTeam(char sTeam){
    team = sTeam;
}

void ChessPiece::setIsEaten(bool stat){
    isEaten=stat;
}

void ChessPiece::setName(string sName){
    name=sName;
}

void ChessBoard::setApiece(int X, int Y,  char ch){
    
    chessBoard[Y][X] = ch;
}

char ChessBoard::getApieceFrCB(int newPosX, int newPosY){
    return chessBoard[newPosY][newPosX];
}

ChessPiece::ChessPiece(bool first){
            isFirst=first;
            isEaten=false;
}
