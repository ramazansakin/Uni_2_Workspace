#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define BLACK_ROOK 'k'	// definations of blacks
#define BLACK_KNIGHT 'a'
#define BLACK_BISHOP 'f'
#define BLACK_QUEEN 'v'
#define BLACK_KING 's'
#define BLACK_PAWN 'p'

#define WHITE_ROOK 'K'	//definations of whites
#define WHITE_KNIGHT 'A'
#define WHITE_BISHOP 'F'
#define WHITE_QUEEN 'V'
#define WHITE_KING 'S'
#define WHITE_PAWN 'P'

#define EMPTY '.' //defination of empty place

#define WHITE "\033[1;36m"	//defination of printing colors
#define BLACK "\033[1;31m"	
							
void printBoard(char board[][8]);	//screen printing function
void fillBoard(char board[][8]);	//fills board with starting positions
int move(char board[][8],char x,char y,char destx,char desty,int color);
//gets move than calls one of the functions below or returns 0 if move isnt valid
int movePawn(char board[][8],char x,char y,char destx,char desty,int color);
int moveRook(char board[][8],char x,char y,char destx,char desty,int color);
int moveBishop(char board[][8],char x,char y,char destx,char desty,int color);
int moveQueen(char board[][8],char x,char y,char destx,char desty,int color);
int moveKing(char board[][8],char x,char y,char destx,char desty,int color);
int moveKnight(char board[][8],char x,char y,char destx,char desty,int color);
//control movement by the rules than makes it if it can

int endGame(char board[][8]);//returns 1 or -1 if there is a missing king else 0
int getPlace(char board[][8],char x,char y);//returns 1 or -1 by the color or returns 0 if it is empty
int absolute(int n);//returns the absolute value of n
int randomMove(char& x,char& y,char& destx,char& desty);//returns a random move

int main(){
	char x,y,destx,desty;
	string line;
	int color = 1, winner=0;
	char board[8][8];
	srand(time(NULL));
	system("clear");
	fillBoard(board);
	printBoard(board);
	while(1){
		winner=endGame(board);
		if(winner==1){
			cout << "Game over. Winner is White"<<endl;
			return 0;
		}		//ends the game if there is a winner
		else if(winner==-1){
			cout << "Game over. Winner is Black"<<endl;
			return 0;
		}
		if(color==1){
			cout << "Enter Your Move" << ":";
			getline(cin,line);
			x=line[0];
			y=line[1];	//gets move from user
			destx=line[3];
			desty=line[4];
		}
		else if(color==-1)	//gets a random move from computer
			randomMove(x,y,destx,desty);
		x = (x>='a'&&x<='z') ? x - 'a' + 'A' : x;
		destx = (destx>='a'&&destx<='z') ? destx - 'a' + 'A' : destx;
		y = (y>='a'&&y<='z') ? y - 'a' + 'A' : y;
		desty = (desty>='a'&&desty<='z') ? desty - 'a' + 'A' : desty;
		if(move(board,x,y,destx,desty,color)){
			color*=-1;
			system("clear");	//if move is valid makes it and prints
			printBoard(board);	//it to screen
			if(x!=0)
				cout << "Last move:" << x << y << "-" << destx << desty << endl;
		}
	}
	return 0;
}

void fillBoard(char board[][8]){
	//places the pieces
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			board[i][j]=EMPTY;

	board[0][0]=BLACK_ROOK;
	board[0][1]=BLACK_KNIGHT;
	board[0][2]=BLACK_BISHOP;
	board[0][3]=BLACK_KING;
	board[0][4]=BLACK_QUEEN;
	board[0][5]=BLACK_BISHOP;
	board[0][6]=BLACK_KNIGHT;
	board[0][7]=BLACK_ROOK;

	for(int i=0;i<8;i++)
		board[1][i]=BLACK_PAWN;

	for(int i=0;i<8;i++)
		board[6][i]=WHITE_PAWN;

	board[7][0]=WHITE_ROOK;
	board[7][1]=WHITE_KNIGHT;
	board[7][2]=WHITE_BISHOP;
	board[7][3]=WHITE_KING;
	board[7][4]=WHITE_QUEEN;
	board[7][5]=WHITE_BISHOP;
	board[7][6]=WHITE_KNIGHT;
	board[7][7]=WHITE_ROOK;
}

void printBoard(char board[][8]){
	//prints the board
	cout << "  A B C D E F G H" << endl;
	for(int i = 0;i < 8;i++){
		cout << 8 - i << ' ';
		for(int j = 0; j < 8; j++){
			if(getPlace(board,j+'A','8' - i)==-1)
				cout << BLACK;
			else if(getPlace(board,j+'A','8' - i)==1)
				cout << WHITE;
			cout << board[i][j] << ' ' << "\033[m";

		}
		cout << 8 - i << endl;
	}
	cout << "  A B C D E F G H" << endl;
}

int move(char board[][8],char x,char y,char destx,char desty,int color){
	//calls the rigth function by the piece in (x,y)
	if(x<'A'||x>'H'||y<'1'||y>'8'||destx<'A'||destx>'H'||desty<'1'||desty>'8'||color!=getPlace(board,x,y))
		return 0;
	switch(board['8'-y][x-'A']){
		case BLACK_PAWN: case WHITE_PAWN:
			return movePawn(board,x,y,destx,desty,color);
		case BLACK_ROOK: case WHITE_ROOK:
			return moveRook(board,x,y,destx,desty,color);
		case BLACK_KNIGHT: case WHITE_KNIGHT:
			return moveKnight(board,x,y,destx,desty,color);
		case BLACK_BISHOP: case WHITE_BISHOP:
			return moveBishop(board,x,y,destx,desty,color);
		case BLACK_QUEEN: case WHITE_QUEEN:
			return moveQueen(board,x,y,destx,desty,color);
		case BLACK_KING: case WHITE_KING:
			return moveKing(board,x,y,destx,desty,color);
	}
}

int movePawn(char board[][8],char x,char y,char destx,char desty,int color){
	//moves pawn by its rules
	if(desty==y+color && ((x == destx && !getPlace(board,destx,desty)) 
		|| (absolute(x-destx)==1 && color==getPlace(board,destx,desty)*-1))){
		board['8' - desty][destx - 'A'] = (color == 1) ? WHITE_PAWN : BLACK_PAWN;
		board['8' - y][x - 'A'] = EMPTY;
		return 1;
	}
		return 0;
}

int moveRook(char board[][8],char x,char y,char destx,char desty,int color){
	//moves rook by its rules
	int stepY,stepX;
	if((desty!=y&&destx==x) || (desty==y&&destx!=x)){
		//only x or y will change
		stepY=(desty - y > 0) ? 1 : -1;
		if(desty - y == 0)
			stepY = 0;
		stepX=(destx - x > 0) ? 1 : -1;
		if(destx - x == 0)
			stepX = 0;
		for(int i = y + stepY, j = x + stepX;i!=desty||j!=destx;i+=stepY,j+=stepX)
			if(getPlace(board,j,i))//controls the places step by step by rooks route
				return 0;
		if(getPlace(board,destx,desty)!=color){
			board['8' - desty][destx - 'A'] = (color == 1) ? WHITE_ROOK : BLACK_ROOK;
			board['8' - y][x - 'A'] = EMPTY;
			return 1;//if there is not a same color piece makes the move 
		}
	}
	return 0;
}

int moveBishop(char board[][8],char x,char y,char destx,char desty,int color){
	//moves bishop by its rules
	int stepY,stepX;
	if(absolute(desty - y) == absolute(destx - x) && destx!=x){
		// x's distance and y's distance is equal
		stepY=(desty - y > 0) ? 1 : -1;
		stepX=(destx - x > 0) ? 1 : -1;
		for(int i = y + stepY, j = x + stepX;i!=desty||j!=destx;i+=stepY,j+=stepX)
			if(getPlace(board,j,i))//controls the places step by step by bishops route
				return 0;
		if(getPlace(board,destx,desty)!=color){
			board['8' - desty][destx - 'A'] = (color == 1) ? WHITE_BISHOP : BLACK_BISHOP;
			board['8' - y][x - 'A'] = EMPTY;
			return 1;//if there is not a same color piece makes the move
		}
	}
	return 0;
}

int moveKnight(char board[][8],char x,char y,char destx,char desty,int color){
	if((absolute(destx - x) == 2 && absolute(desty - y) == 1)||(absolute(destx - x) == 1 && absolute(desty - y) == 2))
		if(getPlace(board,destx,desty)!=color){//moves Knight by its rules
			board['8' - desty][destx - 'A'] = (color == 1) ? WHITE_KNIGHT : BLACK_KNIGHT;
			board['8' - y][x - 'A'] = EMPTY;
			return 1;
		}
	return 0;
}

int moveKing(char board[][8],char x,char y,char destx,char desty,int color){
	//moves Knight by its rules
	if(absolute(destx - x)<=1 && absolute(desty - y)<=1 && (destx!=x || desty!=y))
		if(getPlace(board,destx,desty)!=color){
			board['8' - desty][destx - 'A'] = (color == 1) ? WHITE_KING : BLACK_KING;
			board['8' - y][x - 'A'] = EMPTY;
			return 1;
		}
	return 0;
}

int moveQueen(char board[][8],char x,char y,char destx,char desty,int color){
	int stepY,stepX;
	if(((desty!=y&&destx==x) || (desty==y&&destx!=x) || absolute(desty - y) == absolute(destx - x)) && (destx!=x || desty!=y)){
		//only x or y will change or x's distance and y's distance is equal
		stepY=(desty - y > 0) ? 1 : -1;
		if(desty - y == 0)
			stepY = 0;
		stepX=(destx - x > 0) ? 1 : -1;
		if(destx - x == 0)
			stepX = 0;//controls the places step by step by queens route
		for(int i = y + stepY, j = x + stepX;i!=desty||j!=destx;i+=stepY,j+=stepX)
			if(getPlace(board,j,i))
				return 0;
		if(getPlace(board,destx,desty)!=color){
			board['8' - desty][destx - 'A'] = (color == 1) ? WHITE_QUEEN : BLACK_QUEEN;
			board['8' - y][x - 'A'] = EMPTY;
			return 1;//if there is not a same color piece makes the move
		}
	}
	return 0;
}

int endGame(char board[][8]){
	bool whiteKing = false, blackKing = false;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==BLACK_KING)
				blackKing=true;
			else if(board[i][j]==WHITE_KING)
				whiteKing=true;
		}
	}
	if(whiteKing==false)
		return -1;//returns -1 if there is no white king on board
	else if(blackKing==false)
		return 1;//returns 1 if there is no black king on board
	else
		return 0;//returns 0 if there are both kings on board
}

int getPlace(char board[][8],char x,char y){
	switch(board['8' - y][x - 'A']){
		case BLACK_PAWN: case BLACK_BISHOP: case BLACK_KNIGHT:
		case BLACK_ROOK: case BLACK_KING: case BLACK_QUEEN:
		return -1;//returns -1 if there is a black piece in (x,y)
		case WHITE_PAWN: case WHITE_BISHOP: case WHITE_KNIGHT:
		case WHITE_ROOK: case WHITE_KING: case WHITE_QUEEN:
		return 1;//returns 1 if there is a white piece in (x,y)
		case EMPTY: default:
		return 0;//returns 0 if there is no piece in (x,y)
	}
}

int absolute(int n){//returns the absolute value of  given integer
	return (n>0) ? n : -n;
}

int randomMove(char& x,char& y,char& destx,char& desty){
	x = rand()%8 + 'A';//gives a random move
	y = rand()%8 + '1';
	destx = rand()%8 + 'A';
	desty = rand()%8 + '1';
}
