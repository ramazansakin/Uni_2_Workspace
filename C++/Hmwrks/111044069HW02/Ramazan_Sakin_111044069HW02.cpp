/*##############################################################################
		               Ramazan SAKIN--111044069
  ##########################################################################
		                     CHESS GAME
################################################################################*/
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

#define ROW  8
#define COL  8
#define numOfStone  16

struct stones{
	
	char team;
	char abbvOfName;
	bool isEaten;
	bool isFirst;
	int posX;
	int posY;
	
};


void initStones( stones bStones[], stones wStones[], char chessTable[ROW][COL] );

void placedStonesToChessTable( stones bStones[numOfStone], stones wStones[numOfStone],
														char chessTable[ROW][COL] );

void showChessTable( char chessTable[ROW][COL] );

int convCharTOInt( char move );

int playManually( int movingNum, stones userStns[],stones enemyStns[],
											char chessTable[ROW][COL] );

const int checkMoving( char chessTable[ROW][COL], char theStone, stones Stones[], 
           int indexOfStone, int oldPosX, int oldPosY, int newPosX,int newPosY );
											 
int searchStone( stones userStones[], int posX, int posY );

void isEatenStone( stones userStones[], int indexOfStone, char place );

const int checkRock( char chessTable[ROW][COL], stones Stones[],int indexOfStone, int oldPosX,
							   						int oldPosY,int newPosX,int newPosY );

const int checkHorse( char chessTable[ROW][COL],stones Stones[],int indexOfStone,
                           int oldPosX, int oldPosY,int newPosX,int newPosY );

const int checkElef( char chessTable[ROW][COL],stones Stones[],int indexOfStone, int oldPosX,
							   int oldPosY,int newPosX,int newPosY );

const int checkSah( char chessTable[ROW][COL],stones Stones[],int indexOfStone, int oldPosX,
							   int oldPosY,int newPosX,int newPosY );

const int checkVezir( char chessTable[ROW][COL],stones Stones[],int indexOfStone, int oldPosX,
							   int oldPosY,int newPosX,int newPosY );

const int checkWhitePiyon( char chessTable[ROW][COL],char theStone, stones Stones[],
             int indexOfStone, int oldPosX, int oldPosY,int newPosX,int newPosY );

const bool atTeam( char theStone, stones userStones[] );

const int canPass( stones userStns[],int index,char chessTable[ROW][COL], int oldPosX,
									    int oldPosY, int newPosX, int newPosY   );
									   
const int canPassWPiyon( char chessTable[ROW][COL],stones userStns[], int oldPosY, 
                                                      int newPosY, int oldPosX );

const int canPassBPiyon( char chessTable[ROW][COL],stones userStns[], int oldPosY, 
                                                      int newPosY, int oldPosX );

const int canPassRock( char chessTable[ROW][COL],stones userStns[], int oldPosX, 
									int oldPosY, int newPosX, int newPosY );

const int canPassElef( char chessTable[ROW][COL],stones userStns[], int oldPosX,
									int oldPosY, int newPosX, int newPosY );

const int canPassVezir( char chessTable[ROW][COL],stones userStns[], int oldPosX,
									int oldPosY, int newPosX, int newPosY );
									
const int canPassSah(char chessTable[ROW][COL],stones userStns[], int oldPosX,
										int oldPosY, int newPosX, int newPosY );

int playRandomly( char chessTable[ROW][COL], stones enemyStns[],
                                                           stones userStns[]  );

int searchEnemyStone( stones enemyStones[], int posX, int posY );

const int checkBlackPiyon( char chessTable[ROW][COL],char theStone,stones Stones[],
           int indexOfStone, int oldPosX,int oldPosY,int newPosX,int newPosY );
int randMoving( stones enemyStones[], stones enemyStns[],  int randNum,
                                          char chessTable[ROW][COL] );

int moveRock( stones enemyStones[],int randNum,char chessTable[ROW][COL] );

int movePiyon( stones enemyStones[],int randNum,char chessTable[ROW][COL] );

int moveHorse( stones enemyStones[],int randNum,char chessTable[ROW][COL] );

int moveVezir( stones enemyStones[],int randNum,char chessTable[ROW][COL] );

int moveElef( stones enemyStones[],int randNum,char chessTable[ROW][COL] );

int moveSah( stones enemyStones[],int randNum,char chessTable[ROW][COL] );

const int canSahEat( stones enemyStones[], int randNum, char chessTable[ROW][COL],
                                                  int oldPosX, int   oldPosY );                                                 
void lostMessage();

void winMessage();

int main(){	
	
	char chessTable[ROW][COL];
	stones bStones[numOfStone], wStones[numOfStone];
	initStones( bStones, wStones, chessTable );
	srand(time(NULL));
	
	cout << "#########    Chess Game is starting   ###########" << endl<< endl;
	int movingNum=0, validity;

	while( wStones[4].isEaten != true ){ 
		showChessTable( chessTable );
		++movingNum;
		do{
		  validity = playManually( movingNum, wStones,bStones, chessTable );
		}while( validity == -1 );
	
		if( bStones[4].isEaten == true ){
			winMessage();
			return 0;
		}
		showChessTable( chessTable );
		++movingNum;
		cout << "move " << movingNum << "  Computer"<< endl << endl;
		do{
		  validity = playRandomly( chessTable, bStones, wStones );
		}while( validity == -1 );		
		
		if( wStones[4].isEaten == true ){
			lostMessage();
			return 0;
		}
	}

	return 0;
}

// Initializes the first status of chess Table and values of the stones 
void initStones( stones bStones[], stones wStones[], char chessTable[ROW][COL] )
{
	int i,j, k, t=0;
	
	bStones[0].abbvOfName = 'k';   	wStones[0].abbvOfName = 'K';   
	bStones[1].abbvOfName = 'a';	wStones[1].abbvOfName = 'A';	
	bStones[2].abbvOfName = 'f';	wStones[2].abbvOfName = 'F';
	bStones[3].abbvOfName = 'v';	wStones[3].abbvOfName = 'V';
	bStones[4].abbvOfName = 's';	wStones[4].abbvOfName = 'S';
	bStones[5].abbvOfName = 'f';	wStones[5].abbvOfName = 'F';
	bStones[6].abbvOfName = 'a';	wStones[6].abbvOfName = 'A';
	bStones[7].abbvOfName = 'k';	wStones[7].abbvOfName = 'K';
	
	for( i=8; i<numOfStone ; ++i )		
		bStones[i].abbvOfName = 'p';
		
	for( k=8; k<numOfStone ; ++k )		
		wStones[k].abbvOfName = 'P';
	
	for( i=0;i<numOfStone; ++i ){
		wStones[i].team = 'w';
		bStones[i].team = 'b';
	}
	
	placedStonesToChessTable( bStones, wStones, chessTable );

}
//Show the current ches table
void showChessTable( char chessTable[ROW][COL] )
{
	
	for( int i=0; i<ROW; ++i ){
		for( int j=0; j<COL ; ++j ){
			cout << chessTable[i][j] << " ";
		}
		cout << "|" <<ROW-i << endl;	
	}
	cout << "---------------" << endl;
	cout <<"A B C D E F G H"<< endl << endl;
}

//places the stones to chess table
void placedStonesToChessTable( stones bStones[], stones wStones[], 
                                         char chessTable[ROW][COL] )
{
	int i,j,k,t;
	
	t=0;	//coordinates for black team
	for( i=0 ; i<2 ; ++i ){ 				
		for( j=0; j<COL ; ++j ){
			chessTable[i][j] = bStones[t].abbvOfName;
			bStones[t].posX = j;
			bStones[t].posY = i;
			++t;
		}
	}
	
	for( i=2 ; i<6 ; ++i ){ 				
		for( j=0; j<COL ; ++j ){
			chessTable[i][j] = '.';
		}
	}
	
	t=0;	//coordinates for white team
	for( i=7 ; i>5 ; --i ){ 				
		for( j=0; j<COL ; ++j ){
			chessTable[i][j] = wStones[t].abbvOfName;
			wStones[t].posX = j;
			wStones[t].posY = i;		
			++t;
		}
	}
	for(i=0; i<16; ++i){
		bStones[i].isEaten = false;
		wStones[i].isEaten = false;
		bStones[i].isFirst = true;
		wStones[i].isFirst = true;
	}
		
}

//user plays and this function checks user's moving
int playManually( int movingNum, stones userStns[], stones enemyStns[], char chessTable[ROW][COL] ){
	string move;
	int oldPosX, oldPosY, newPosX, newPosY;
	int stoneNumber, valid1, valid2, valid3;
	cout << "move " << movingNum << "  ";
	cin >> move;
	cout << endl;
	
	oldPosX = convCharTOInt( move[0] );
	oldPosY = convCharTOInt( move[1] );	
	newPosX = convCharTOInt( move[3] );
	newPosY = convCharTOInt( move[4] );
	
	if( newPosX == -1 || newPosY == -1 )
		return -1;	//play again with valid moving
	
	if( atTeam( chessTable[newPosY][newPosX], userStns ) ){
		cout << "You can not eat your stones!Move again\n";
		return -1;
	}
	stoneNumber = searchStone( userStns, oldPosX, oldPosY );
	valid2 = checkMoving( chessTable,chessTable[newPosY][newPosX] ,userStns,
	                         stoneNumber, oldPosX, oldPosY, newPosX, newPosY  );
	valid3=canPass( userStns, stoneNumber, chessTable, oldPosX, oldPosY, newPosX,newPosY);            
	if( valid2 == -1 ){
		cout << "Please enter valid coordinates!!\n";
		return -1;	
	}
	if( valid3 == -1 ){
		cout << "You can not pass above your stone!"<< endl;
		return -1;
	}
	userStns[stoneNumber].posX=newPosX;
	userStns[stoneNumber].posY=newPosY;
	
	int enemyIndex=searchEnemyStone( enemyStns, newPosX, newPosY );
	isEatenStone( enemyStns , enemyIndex, chessTable[newPosY][newPosX] );
	userStns[stoneNumber].isFirst = false;	//for piyons
	
	chessTable[newPosY][newPosX] = chessTable[oldPosY][oldPosX];	
	chessTable[oldPosY][oldPosX] = '.';
	cout << endl;
	
	return 1;	//There is no problem*/
}

//converts the character to integer
int convCharTOInt( char move )
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

//finds the stone
int searchStone( stones userStones[], int posX, int posY )
{ 	
	int i, j;
	for(  i=0; i<16 ; ++i ){
		if( userStones[i].posX == posX && userStones[i].posY == posY
		    && userStones[i].team == 'w'                              ){
			return i;
		}
	}
	
	return -1;	//There is not or **error**
}

//finds a stone that belongs to black team
int searchEnemyStone( stones enemyStones[], int posX, int posY )
{ 	
	int i, j;
	for(  i=0; i<16 ; ++i ){
		if( enemyStones[i].posX == posX && enemyStones[i].posY == posY
		    &&  enemyStones[i].team == 'b'                             ){
			return i;
		}
	}
	
	return -1;	//There is not or **error**
}

//checks user's moving  with the helper functions
//And also checks the moving of black stones
//If user or black stones played wrongly, it is neccessary to play again to continue
const int checkMoving( char chessTable[ROW][COL], char theStone, stones Stones[], 
           int indexOfStone, int oldPosX, int oldPosY, int newPosX,int newPosY )
{
 int control;
 switch(indexOfStone+1){
	case 1:  case 8:
      control=checkRock(chessTable,Stones,indexOfStone,oldPosX,oldPosY,newPosX,newPosY);
	  break;
    case 2:  case 7:
	  control=checkHorse( chessTable,Stones, indexOfStone,oldPosX, oldPosY, newPosX, newPosY );
	  break;
	case 3:  case 6:
	  control=checkElef(chessTable,Stones,indexOfStone,oldPosX,oldPosY,newPosX,newPosY);
	  break;
	case 4:
	  control=checkVezir(chessTable,Stones,indexOfStone,oldPosX,oldPosY,newPosX,newPosY);
	  break;
	case 5:
	  control=checkSah(chessTable,Stones,indexOfStone,oldPosX,oldPosY,newPosX,newPosY);
	  break;
	case 9:  case 10: case 11:  case 12:
	case 13: case 14: case 15:  case 16:
	  control=checkWhitePiyon( chessTable,theStone, Stones, indexOfStone, oldPosX, 
		                                                  oldPosY, newPosX, newPosY );
	  break;
	default:	
	  return -1;	//if there is an error
 }
	return control;
}

//if a black team's component was eaten, that stone should not be used 
void isEatenStone( stones enemyStones[], int indexOfStone, char place )
{
	if( place != '.' ){
		enemyStones[indexOfStone].isEaten=true;
	}
}

//Checking  Functions..
//this checking functions checks the stones' movings
const int checkRock( char chessTable[ROW][COL], stones Stones[],int indexOfStone, int oldPosX,
							   						int oldPosY,int newPosX,int newPosY )
{	
	if( Stones[indexOfStone].isEaten != true ){
		if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8
		    && atTeam( chessTable[oldPosX][oldPosY], Stones ) != -1 
		    && ( abs(oldPosX-newPosX) == 0 || abs(oldPosY-newPosY) == 0 ) )
			return 1;
		else
			return -1;	
	}else
		return -1;
}

const int checkHorse( char chessTable[ROW][COL],stones Stones[],int indexOfStone,
                           int oldPosX, int oldPosY,int newPosX,int newPosY )
{	
	if( Stones[indexOfStone].isEaten != true ){
		if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8
		    && oldPosX != newPosX && oldPosY != newPosY 
		    && abs(newPosX-oldPosX)+abs(newPosY-oldPosY) == 3 ) // +2 X or Y and
			return 1;											// +1 for other one(3)
		else
			return -1;
	}else
		return -1;
}

const int checkElef( char chessTable[ROW][COL],stones Stones[],int indexOfStone, int oldPosX,
							   int oldPosY,int newPosX,int newPosY )
{	
	if( Stones[indexOfStone].isEaten != true ){
		if( oldPosX != newPosX && oldPosY != newPosY &&
		    abs( oldPosX-newPosX ) == abs( oldPosY-newPosY )
		    && oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8 )
			return 1;
		else
			return -1;
	}else
		return -1;
}

const int checkSah( char chessTable[ROW][COL],stones Stones[],int indexOfStone,int oldPosX,
							  int oldPosY,int newPosX,int newPosY )
{
	if( Stones[indexOfStone].isEaten != true ){
		if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8
		    && ( abs(oldPosX-newPosX)==1 || abs( oldPosY-newPosY ) )== 1 )
			return 1;
		else
			return -1;	
	}else
		return -1;
}

const int checkVezir( char chessTable[ROW][COL],stones Stones[],int indexOfStone,int oldPosX,
							    int oldPosY,int newPosX,int newPosY )
{
	if( Stones[indexOfStone].isEaten != true ){
	  if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8 &&
	    (checkElef(chessTable,Stones,indexOfStone,oldPosX,oldPosY,newPosX,newPosY) ==1 &&
	    canPassElef( chessTable, Stones, oldPosX, oldPosY, newPosX, newPosY ) == 1) || 
	    (checkRock(chessTable,Stones, indexOfStone,oldPosX,oldPosY,newPosX,newPosY) ==1 &&
	    canPassRock( chessTable, Stones, oldPosX, oldPosY, newPosX, newPosY ) == 1 ) )
		return 1;
	  else
	  	return -1;	
	}else
		return -1;
}

const int checkWhitePiyon( char chessTable[ROW][COL],char theStone,stones Stones[],
           int indexOfStone, int oldPosX,int oldPosY,int newPosX,int newPosY )
{	
	if( Stones[indexOfStone].isEaten != true && theStone == '.'
	    && Stones[indexOfStone].isFirst == true  ){
			if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8 &&
				oldPosX == newPosX && (oldPosY-2 == newPosY || oldPosY-1 == newPosY) )
				return 1;
			else if( !Stones[indexOfStone].isFirst && oldPosX >= 0 && oldPosX < 8 
			         && newPosY >= 0 && newPosY < 8 && oldPosX == newPosX && 
			                                              oldPosY-1 == newPosY )
			    return 1;	//you can go one step
			else		    
				return -1;
		}else if( theStone != '.' ){
			if(( oldPosX-1==newPosX && oldPosY-1==newPosY ) || 
		  	(oldPosX+1==newPosX && oldPosY-1==newPosY ) ){
		  		return 1;	//if the piyon eats a stone, ..	
		  	}else
				return -1;
	}
	
}

const int checkBlackPiyon( char chessTable[ROW][COL],char theStone,stones Stones[],
           int indexOfStone, int oldPosX,int oldPosY,int newPosX,int newPosY )
{	
	if( Stones[indexOfStone].isEaten != true && theStone == '.' ){
			if( oldPosX >= 0 && oldPosX < 8 && newPosY >= 0 && newPosY < 8 &&
				oldPosX == newPosX && ( oldPosY+2 == newPosY || oldPosY+1 == newPosY ) )
				return 1;
			else
				return -1;
		}else if( theStone != '.' ){
			if(( oldPosX-1==newPosX && oldPosY+1==newPosY ) || 
		  	(oldPosX+1==newPosX && oldPosY+1==newPosY ) ){
		  		return 1;	//if the piyon eats a stone, ..	
		  	}else
				return -1;
	}
	
}

//is the searched stone in my team or other team
const bool atTeam( char theStone, stones userStones[] )
{
	for( int i=0; i<numOfStone ; ++i ){
		if(userStones[i].abbvOfName == theStone )	
			return true;
	}

	return false;
}

//If there is a stone that is in your team of your front, you can not pass above of it...
//This function controls the stone which want to pass above its own team's stone
//Also, this fuction checks enemyStones that can pass or can not pass
const int canPass( stones userStns[],int index,char chessTable[ROW][COL], int oldPosX,
									    int oldPosY, int newPosX, int newPosY   ){
	
	int status=0;
	if( userStns[index].abbvOfName == 'P' || userStns[index].abbvOfName == 'p' ){
	  if( userStns[index].abbvOfName == 'P' )
		status=canPassWPiyon( chessTable,userStns, oldPosY, newPosY, oldPosX );
	  else
	    status=canPassBPiyon( chessTable,userStns, oldPosY, newPosY, oldPosX );	
	}else if( userStns[index].abbvOfName == 'K' || userStns[index].abbvOfName == 'k' ){
		status=canPassRock( chessTable,userStns, oldPosX, oldPosY, newPosX, newPosY);
	}else if( userStns[index].abbvOfName == 'F' || userStns[index].abbvOfName == 'f' ){
		status=canPassElef( chessTable,userStns, oldPosX, oldPosY, newPosX, newPosY);
	}else if( userStns[index].abbvOfName == 'V' || userStns[index].abbvOfName == 'v' ){
		status=canPassVezir( chessTable,userStns, oldPosX, oldPosY, newPosX, newPosY);
	}else if( userStns[index].abbvOfName == 'S' || userStns[index].abbvOfName == 's' ){
		status=canPassSah( chessTable,userStns, oldPosX, oldPosY, newPosX, newPosY);
	}

	return status;
}

//checks the piyon
const int canPassWPiyon( char chessTable[ROW][COL], stones userStns[], int oldPosY,
                                                      int newPosY, int oldPosX ){
	if( newPosY==oldPosY-2 )
		 	if( atTeam( chessTable[oldPosY-1][oldPosX], userStns ))
				return -1;
	
	return 1;
}

const int canPassBPiyon( char chessTable[ROW][COL], stones userStns[], int oldPosY,
                                                    int newPosY, int oldPosX ){
	if( newPosY==oldPosY+2 )
		 	if( atTeam( chessTable[oldPosY+1][oldPosX], userStns ))
				return -1;

	return 1;
}

const int canPassRock( char chessTable[ROW][COL],stones userStns[], int oldPosX, 
									int oldPosY, int newPosX, int newPosY )
{ 
	int i;
	if( oldPosY-newPosY > 1 ){
	  for( i=newPosY; i<oldPosY; ++i )
		if( atTeam( chessTable[i][oldPosX], userStns) )
			return -1;
	}else if( newPosY-oldPosY > 1 ){
	  for( i=newPosY; i>oldPosY; --i )
		if( atTeam( chessTable[i][oldPosX], userStns) )
			return -1;		
	}else if( newPosX-oldPosX > 1 ){
	  for( i=newPosX; i>oldPosX; --i )
		if( atTeam( chessTable[oldPosY][i],userStns) )
			return -1;
	}else if( oldPosX-newPosX > 1 ){
	  for( i=newPosX ; i<oldPosX; ++i )
		if( atTeam( chessTable[oldPosY][i], userStns) )
			return -1;			
	}	
	
	return 1;
}

const int canPassElef( char chessTable[ROW][COL],stones userStns[], int oldPosX,
									int oldPosY, int newPosX, int newPosY )
{	
	int i,j;
	//checks is a stone front on my way? , controls coordinates...
	if( oldPosY>newPosY && oldPosX>newPosX ){
	  for( i=newPosX,j=newPosY; i<oldPosX, j<oldPosY; ++i, ++j )
		if( atTeam( chessTable[j][i] , userStns) )
			return -1;
	}else if( oldPosY>newPosY && oldPosX<newPosX ){
	  for( i=newPosX,j=newPosY; i>oldPosX, j<oldPosY; --i, ++j )
		if( atTeam( chessTable[j][i] , userStns) )
			return -1;
	}else if( oldPosY<newPosY && oldPosX>newPosX  ){
	  for( i=newPosX,j=newPosY; i<oldPosX, j>oldPosY; ++i, --j )
		if( atTeam( chessTable[j][i], userStns) )
			return -1;
	}else if( oldPosY<newPosY && oldPosX<newPosX  ){
	  for( i=newPosX,j=newPosY; i>oldPosX, j>oldPosY; --i, --j )
		if( atTeam( chessTable[j][i], userStns) )
			return -1;
	}
	return 1;
}

//if the stone can go either like a horse or like a rock, the stone is vezir...
const int canPassVezir( char chessTable[ROW][COL],stones userStns[], int oldPosX,
									int oldPosY, int newPosX, int newPosY )
{	
	if( abs( oldPosX-newPosX ) == 0 || abs( oldPosY-newPosY ) == 0 ){
	    if(canPassRock( chessTable,userStns, oldPosX, oldPosY, newPosX, newPosY) == 1)
			return 1;
	}else if( abs(oldPosX - newPosX) == abs( oldPosY-newPosY ) ){
		if( canPassElef( chessTable,userStns, oldPosX, oldPosY, newPosX, newPosY) == 1 )
			return 1;			
	}else 
		return -1;

}

const int canPassSah( char chessTable[ROW][COL],stones userStns[], int oldPosX,
										int oldPosY, int newPosX, int newPosY )
{	
	if( atTeam( chessTable[newPosY][newPosX], userStns) )
		return -1;
	return 1;	
}

//the black team plays randomly, chooses a stone with random index and 
//chooses random X and Y coordinates and checks the stone can pass x and y coor.
//checks is there a stone that is same team and check moving --valid or unvalid
int playRandomly( char chessTable[ROW][COL], stones enemyStns[], stones userStns[]  )
{	//choosing a stone randomly
	int randNum = rand()%16 ,  status;
	
	status = randMoving( enemyStns,userStns, randNum, chessTable );	
	return status;
}                                               

// move the stone that specify with rand number, which stone?
int randMoving( stones enemyStones[], stones userStns[],  int randNum,
                                             char chessTable[ROW][COL] )
{
	int status;
	switch(randNum){
		case 0:  case 7:
			status = moveRock( enemyStones, randNum, chessTable );
	    	break;
		case 1:  case 6:
			status = moveHorse( enemyStones, randNum, chessTable );
			break;
		case 2:  case 5:
			status = moveElef( enemyStones, randNum, chessTable );	
			break;	
		case 3:
			status = moveVezir( enemyStones, randNum, chessTable );
			break;
		case 4:
			status = moveSah( enemyStones, randNum, chessTable );
			break;
		default:	//At the other cases 	
		status = movePiyon( enemyStones, randNum, chessTable );
	}
	
	return status;	//play again if status is -1, o.w go on..
}

int moveRock( stones enemyStones[],int randNum,char chessTable[ROW][COL])
{
	int validity1, validity2, newX, newY;
	int whichPos = rand()%2;		//which aspect should the rock go randomly?
	
	if( whichPos == 0 ){			//and go along towards X or Y randomly
		
		newX = rand()%3+enemyStones[randNum].posX;	// moving randm step to X
		newY = enemyStones[randNum].posY;
		validity1=checkRock( chessTable, enemyStones, randNum, 
	    enemyStones[randNum].posX, enemyStones[randNum].posY, newX, newY);
	    validity2=canPass(enemyStones, randNum, chessTable,enemyStones[randNum].posX,
	                                          enemyStones[randNum].posY, newX, newY );
	}else {
	  newY = rand()%3+enemyStones[randNum].posY;	//moving random step to Y
	  newX = enemyStones[randNum].posX;
	  validity1=checkRock( chessTable, enemyStones, randNum, 
	  enemyStones[randNum].posX,enemyStones[randNum].posY,enemyStones[randNum].posX,newY);	
	  validity2=canPass( enemyStones, randNum, chessTable, enemyStones[randNum].posX,
	                                           enemyStones[randNum].posY, newX, newY );
	}
	
	
	if( validity1 == -1 || validity2 == -1 )
		return -1;
	else  {
		chessTable[enemyStones[randNum].posY][enemyStones[randNum].posX] = '.';
		enemyStones[randNum].posX=newX;
		enemyStones[randNum].posY=newY;
		chessTable[newY][newX] = enemyStones[randNum].abbvOfName;
		
		
		return 1;	
	}
		
}

int moveElef( stones enemyStones[],int randNum,char chessTable[ROW][COL] )
{
	int randomNum = rand()%4;
	int newY = randomNum + enemyStones[randNum].posY, newX;// not to cross the frontier
	if( newY%2 == 0 )
		newX = enemyStones[randNum].posX + randomNum;
	else
		newX = enemyStones[randNum].posX - randomNum;
		
	int validity1=checkElef(chessTable, enemyStones, randNum, 
	    enemyStones[randNum].posX, enemyStones[randNum].posY, newX, newY);
	int validity2=canPass(enemyStones, randNum, chessTable, enemyStones[randNum].posX,
	                                     enemyStones[randNum].posY, newX, newY);
	
	if( validity1 == -1 || validity2 == -1 )
		return -1;
	else  {
		chessTable[newY][newX] = enemyStones[randNum].abbvOfName;
		chessTable[enemyStones[randNum].posY][enemyStones[randNum].posX] = '.';
		enemyStones[randNum].posX=newX;
		enemyStones[randNum].posY=newY;
	}
	return 1;
}

int movePiyon( stones enemyStones[],int randNum,char chessTable[ROW][COL] )
{
  int newY;
			
	if( enemyStones[randNum].isFirst == true )
		newY = rand()%2 + 1 + enemyStones[randNum].posY;
	else  //If the piyon was played second time or more, the piyon can go one step
		newY = 1 + enemyStones[randNum].posY;		
	
	int newX = enemyStones[randNum].posX; 
		
	int validity1 = checkBlackPiyon(chessTable,chessTable[newY][newX], enemyStones,
	          randNum, enemyStones[randNum].posX, enemyStones[randNum].posY, newX, newY);
	int validity2=canPass( enemyStones, randNum, chessTable, enemyStones[randNum].posX,
	                                            enemyStones[randNum].posY, newX, newY );
	
	if( validity1 == -1 || validity2 == -1 )
		return -1;
	else  {
		chessTable[newY][newX] = enemyStones[randNum].abbvOfName;
		chessTable[enemyStones[randNum].posY][enemyStones[randNum].posX] = '.';
		enemyStones[randNum].posX=newX;
		enemyStones[randNum].posY=newY;
		enemyStones[randNum].isFirst = false;	//because of piyon can not be palyed
	}											//two step for other hand		
	return 1;
  	
}

int moveHorse( stones enemyStones[],int randNum,char chessTable[ROW][COL] )
{
	int randNumber = rand()%2, newX, newY;
	int randNumber2 = rand()%2, randNumber3 = rand()%2;
	
	//play randomly
	if( randNumber == 0 ){
		newX = 2 + enemyStones[randNum].posX;
		if( randNumber2 == 0 )
			newY = 1 + enemyStones[randNum].posY;
		else	
			newY = -1 + enemyStones[randNum].posY;
	}else{
		newY = 2 + enemyStones[randNum].posY;
		if( randNumber3 == 0 ) 
			newX = 1+ enemyStones[randNum].posX;
		else
			newX = -1+ enemyStones[randNum].posX;
	}

	int validity2;
	
	int validity1=checkHorse( chessTable, enemyStones, randNum, 
	    enemyStones[randNum].posX,enemyStones[randNum].posY, newX, newY);
	
	validity2 = searchStone(enemyStones, enemyStones[randNum].posX ,enemyStones[randNum].posY );
	
	if( validity1 == -1 || validity2 == -1 )
		return -1;
	else {
		chessTable[newY][newX] = enemyStones[randNum].abbvOfName;
		chessTable[enemyStones[randNum].posY][enemyStones[randNum].posX] = '.';
		enemyStones[randNum].posX=newX;
		enemyStones[randNum].posY=newY;
	}
	return 1;
}

int moveVezir( stones enemyStones[],int randNum,char chessTable[ROW][COL] )
{
	int randNumber = rand()%4, newY;
	int newX = randNumber + enemyStones[randNum].posX;
	
	if( newX%2 == 0 )
		newY = enemyStones[3].posY;
	else if( randNumber = rand()%2 == 1  )
		newY = enemyStones[3].posY + randNumber;
	else
		newY = enemyStones[3].posY - randNumber;
			
	int validity1=checkVezir(chessTable, enemyStones, 3, 
	    enemyStones[3].posX,enemyStones[3].posY, newX, newY);
	int validity2=canPass( enemyStones, 3, chessTable,enemyStones[3].posX,
	                                        enemyStones[3].posY, newX, newY );
	
	if( validity1 == -1 || validity2 == -1 )
		return -1;
	else {
		chessTable[newY][newX] = enemyStones[randNum].abbvOfName;
		chessTable[enemyStones[randNum].posY][enemyStones[randNum].posX] = '.';
		enemyStones[randNum].posX=newX;
		enemyStones[randNum].posY=newY;
	}
	
	return 1;
}

int moveSah( stones enemyStones[],int randNum,char chessTable[ROW][COL] )
{
	int isEaten;
	
	int newX = rand()%2 + enemyStones[4].posX;	
	int newY = rand()%2 + enemyStones[4].posY;	
	
	int validity1=checkSah(chessTable, enemyStones, 4, 
	    enemyStones[4].posX, enemyStones[4].posY, newX, newY);
	int validity2=canPass( enemyStones, 4, chessTable, enemyStones[4].posX,
	                                         enemyStones[4].posY, newX, newY );
	
	if( validity1 == -1 || validity2 == -1 )
		return -1;
	else {
		chessTable[newY][newX] = enemyStones[4].abbvOfName;
		chessTable[enemyStones[4].posY][enemyStones[4].posX] = '.';
		enemyStones[4].posX=newX;
		enemyStones[4].posY=newY;
	}
  	return 1;
  	
}

/*
//if there is a stone next to the black sah, sah can eat the stone but 
//when the randNum is 4(indexOfBlckSah) 
const int canSahEat( stones enemyStones[], int randNum, char chessTable[ROW][COL],
                                                      int oldPosX, int oldPosY )
{
	for( int i=0; i<3; ++i )
      for( int j=0; j<3; ++j ){
      	if( chessTable[oldPosY-1+j][oldPosX-1+i] != '.' && 
      	    !islower(chessTable[oldPosY-1+j][oldPosX-1+i]) )
      		if( i != 1 && j != 1 ){
      			chessTable[oldPosY-1+j][oldPosX-1+i] = enemyStones[randNum].abbvOfName;
      			chessTable[oldPosY][oldPosX] = '.';
      			enemyStones[randNum].posX=oldPosX-1+j;
				enemyStones[randNum].posY=oldPosY-1+i;
      			
      			return 1;
      	}
      }
	return -1;
}
*/

void winMessage(){
	cout << "#############################################################" << endl;
	cout << "                    You won the game!"                         << endl;                   				
	cout << "#############################################################" << endl;
}

void lostMessage(){
	cout << "#############################################################" << endl;
	cout << "                    You lost the game!"                        << endl;                   				
	cout << "#############################################################" << endl;
}
