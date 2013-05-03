//============================================================================
// Name        : .cpp
// Author      : Grzegorz Gajoch
// Description : 
//============================================================================

#include <cstdio>
#include <iostream>
#include <inttypes.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>

using namespace std;

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(x, n) for(int x=0; x < (n); ++x)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(n) (int)n.size()
#define ALL(c) c.begin(),c.end()
#define PB(n) push_back(n)
typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef vector<bool> VB;
#define MP make_pair
#define ST first
#define ND second
const int INF = 1000000001;

#define debug



#define ROWS 15
#define COLUMNS 7


bool screen[ROWS][COLUMNS];

struct Block
{
        uint8_t X1 : 3;
	uint8_t X2 : 3;
	uint8_t X3 : 3;
	uint8_t X4 : 3;

	uint8_t Y1 : 4;
	uint8_t Y2 : 4;
	uint8_t Y3 : 4;
	uint8_t Y4 : 4;
	
	uint8_t type : 3;
	uint8_t orient : 1;

	Block(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, uint8_t x4, uint8_t y4, uint8_t orient, uint8_t type)
	{
		X1 = x1;
		X2 = x2;
		X3 = x3;
		X4 = x4;
		Y1 = y1;
		Y2 = y2;
		Y3 = y3;
		Y4 = y4;
		this->type = type;
		this->orient = orient;
	}
	Block()
	{
		X1 = X2 = X3 = X4 = Y1 = Y2 = Y3 = Y4 = type = orient = 0;
	}
};


Block activeBlock;


#define SCREEN(x) (screen[activeBlock.Y ## x ][activeBlock.X ## x ])
#define ALLBLOCK SCREEN(1) = SCREEN(2) = SCREEN(3) = SCREEN(4)



void setActiveBlock()
{
	ALLBLOCK = true;
}
void unsetActiveBlock()
{
	ALLBLOCK = false;
}
#define FORALLELEMENTS(a) ( a (1) || a (2) || a (3) ||  a (4) )

#define XACTIVEBLOCKCOORS(a) (activeBlock.X ## a) 
#define TOUCHLEFT(a) (XACTIVEBLOCKCOORS(a) == 0)
#define TOUCHRIGHT(a) (XACTIVEBLOCKCOORS(a) == (COLUMNS-1))
#define SCREENATRIGHT(a) (screen[activeBlock.Y ## a ][activeBlock.X ## a + 1])
#define SCREENATLEFT(a) (screen[activeBlock.Y ## a ][activeBlock.X ## a - 1])

void shiftActiveBlockLeft()
{
	unsetActiveBlock();
	if( FORALLELEMENTS(TOUCHLEFT) || FORALLELEMENTS(SCREENATLEFT) ) return;
	--XACTIVEBLOCKCOORS(1);
	--XACTIVEBLOCKCOORS(2);
	--XACTIVEBLOCKCOORS(3);
	--XACTIVEBLOCKCOORS(4);
	setActiveBlock();
}

void shiftActiveBlockRight()
{
	unsetActiveBlock();
	if( FORALLELEMENTS(TOUCHRIGHT) || FORALLELEMENTS(SCREENATRIGHT) ) return;
	++XACTIVEBLOCKCOORS(1);
	++XACTIVEBLOCKCOORS(2);
	++XACTIVEBLOCKCOORS(3);
	++XACTIVEBLOCKCOORS(4);
	setActiveBlock();
}


#define UNDERACTIVEBLOCK(x) (screen[activeBlock.Y ## x+1][activeBlock.X ## x ])
#define ZEROY(x) (activeBlock.Y ## x == (ROWS-1))

bool shiftActiveBlockDown()
{
	if( UNDERACTIVEBLOCK(1) || UNDERACTIVEBLOCK(2) || UNDERACTIVEBLOCK(3) || UNDERACTIVEBLOCK(4) || ZEROY(1) || ZEROY(2) || ZEROY(3) || ZEROY(4) ) return false;
	++activeBlock.Y1;
	++activeBlock.Y2;
	++activeBlock.Y3;
	++activeBlock.Y4;
	return true;
}

#define X(a) (tempBlock.X ## a)
#define Y(a) (tempBlock.Y ## a)
#define TAKEN(x) (screen[Y(x)][X(x)])
#define ANYTAKEN() (TAKEN(1) || TAKEN(2) || TAKEN(3) || TAKEN(4))

#define SHIFTORIENT() (activeBlock.orient = !activeBlock.orient)

bool rotateActiveBlock()
{
	Block tempBlock = activeBlock;
	unsetActiveBlock();
	printf("(%d)\n",activeBlock.type);
	if( activeBlock.type == 1 )
	{
		if( activeBlock.orient == 0)
		{
			if( screen[Y(2)][X(2)-1] || screen[Y(2)][X(2)+1] || screen[Y(2)][X(2)+2] || X(2) < 1 || X(2) +2 >= COLUMNS ) return false;
			Y(1) = Y(3) = Y(4) = Y(2);
			X(1) = X(2)-1;
			X(3) = X(2)+1;
			X(4) = X(2)+2;
		}
		else
		{
			if( screen[Y(2)-1][X(2)] || screen[Y(2)+1][X(2)] || screen[Y(2)+2][X(2)] || Y(2) == 0 || Y(2) + 2 >= ROWS ) return false;
			X(1) = X(3) = X(4) = X(2);
			Y(1) = Y(2)-1;
			Y(3) = Y(2)+1;
			Y(4) = Y(2)+2;
		}
	}
	else if( activeBlock.type == 2 )
	{
		if( activeBlock.orient == 0 )
		{
			X(1) = X(4);
			Y(1) = Y(2)-1;
			--Y(4);

		}
		else
		{
			if( X(2) == 0 ) return false;
			X(1) = X(2)-1;
			++Y(1);
			++Y(4);
		}
	}
	else if( activeBlock.type == 3 )
	{
		if( activeBlock.orient == 0 )
		{
			++Y(2);
			X(3) = X(2);
			Y(3) = Y(2)+1;
		}
		else
		{
			if( Y(2) == 0 ) return false;
			--Y(2);
			Y(3) = Y(4);
			X(3) = X(4)-1;
		}
	}
	else if( activeBlock.type == 4 )
	{
		if( activeBlock.orient == 0 )
		{
			if( Y(2)+2 >= ROWS ) return false;
			X(3) = X(4) = X(2);
			Y(3) = Y(2)+1;
			Y(4) = Y(3)+1;
		}
		else
		{
			if( X(2) + 1 >= COLUMNS ) return false;
			X(3) = X(2)+1;
			Y(3) = Y(2);
			X(4) = X(1);
			Y(4) = Y(1)+1;
		}
	}
	else if( activeBlock.type == 5 )
	{
		if( activeBlock.orient == 0 )
		{
			if(X(2) == 0 ) return false;
			Y(1) = Y(2);
			X(1) = X(2)-1;
			++X(4);
		}
		else
		{
			--X(4);
			X(1) = X(2);
			Y(1) = Y(4)+1;
		}
	}
	if( ANYTAKEN() ) return false;
	else
	{
		activeBlock = tempBlock;
	}
	SHIFTORIENT();
	setActiveBlock();
	return true;
}

bool generate_new_block()
{
	Block a;
	uint8_t ran = rand()%6;
	switch(ran)
	{
	case 0:
//OO
//OO
		a = Block(3,0,4,0,3,1,4,1,0,0); 
		break;
	case 1:
//OOOO
		a = Block(1,0,2,0,3,0,4,0,1,1);
		break;
	case 2:
//OO
// OO
		a = Block(3,0,4,0,4,1,5,1,0,2); 
		break;
	case 3:
// OO
//OO
		a = Block(4,0,5,0,3,1,4,1,0,3);
		break;
	case 4:
//OOO
//O
		a = Block(2,0,3,0,4,0,2,1,1,4);
		break;
	case 5:
//OOO
//  O
		a = Block(2,0,3,0,4,0,4,1,1,5);
		break;
	}

#define FIELD(x) (screen[a.Y ## x][a.X ## x])

	if( FIELD(1) || FIELD(2) || FIELD(3) || FIELD(4) ) return 0;
	activeBlock = a;
}


void print_screen()
{
	system("clear");
	REP(x,COLUMNS+2)
	{
		printf("-");
	}
	printf("\n");
	REP(y,ROWS)
	{
		printf("|");
		REP(x,COLUMNS)
		{
			if( screen[y][x] ) printf("0");
			else printf(" ");
		}
		printf("|\n");
	}
	REP(x,COLUMNS+2)
	{
		printf("-");
	}
	printf("\n");
}

void clear_screen() 
{
	for(uint8_t y = 0; y < ROWS; ++y)
	{
		for(uint8_t x = 0; x < COLUMNS; ++x)
		{
			screen[y][x] = 0;
		}
	}
}
void checkForLines();
void update_screen()
{
	unsetActiveBlock();
	if( shiftActiveBlockDown() == false )
	{
		setActiveBlock();
		generate_new_block();
		setActiveBlock();
	}
	checkForLines();
	setActiveBlock();
}





void checkForLines()
{
	for(uint8_t Y = 0; Y < ROWS; ++Y)
	{
		bool line = true;
		for(uint8_t X = 0; X < COLUMNS; ++X)
		{
			if( screen[Y][X] == false )
			{
				line = false;
				break;
			}
		}
		if( line )
		{
			for(uint8_t a = Y; a > 1; --a)
			{
				for(uint8_t X = 0; X < COLUMNS; ++X)
				{
					screen[a][X] = screen[a-1][X];
				}
			}
		}
	}
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	generate_new_block();
	setActiveBlock();
	while(1)
	{
		update_screen();
		print_screen();
		char x;
		printf("MOVE : ");
		while( true )
		{
			scanf("%c",&x);
			if( x == '.' ) shiftActiveBlockRight();
			else if( x == ',' ) shiftActiveBlockLeft();
			else if( x == '/' ) rotateActiveBlock();
			else if( x == '\'') {}
			else continue;
			break;
		}
	}
}
