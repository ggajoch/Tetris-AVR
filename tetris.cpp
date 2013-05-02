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


struct ScreenField
{
	uint8_t value;
	uint8_t blockNr;
};

ScreenField screen[ROWS][COLUMNS];


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

	uint8_t locked : 1;

	Block(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, uint8_t x4, uint8_t y4)
	{
		X1 = x1;
		X2 = x2;
		X3 = x3;
		X4 = x4;
		Y1 = y1;
		Y2 = y2;
		Y3 = y3;
		Y4 = y4;
		locked = 0;
	}
	Block()
	{
		X1 = X2 = X3 = X4 = Y1 = Y2 = Y3 = Y4 = locked = 0;
	}
};


Block blocks[20];
uint8_t numberOfBlocks = 0;

bool generate_new_block()
{
	Block a;
	uint8_t ran = rand()%6;
	switch(ran)
	{
	case 0:
		a = Block(1,0,2,0,3,0,4,0);
		break;
	case 1:
		a = Block(2,0,3,0,2,1,2,2);
		break;
	case 2:
		a = Block(2,0,3,0,3,1,3,2);
		break;
	case 3:
		a = Block(2,0,3,0,2,1,3,1);
		break;
	case 4:
		a = Block(2,0,3,0,3,1,4,1);
		break;
	case 5:
		a = Block(3,0,4,0,2,1,3,1);
		break;
	}

#define FIELD(x) (screen[a.Y ## x][a.X ## x].value)

	if( FIELD(1) || FIELD(2) || FIELD(3) || FIELD(4) ) return 0;
	blocks[numberOfBlocks] = a;
}


void print_screen()
{
	system("clear");
	REP(y,ROWS)
	{
		REP(x,COLUMNS)
		{
			if( screen[y][x].value ) printf("0");
			else printf("X");
		}
		printf("\n");
	}
}


#define COORDS(x) screen[blocks[index].Y ## x+1][blocks[index].X ## x]

#define CHECK_VALUE(x) 	(COORDS(x).value && blocks[COORDS(x).blockNr].locked )

bool mark_if_locked(uint8_t index)
{
	if( CHECK_VALUE(1) || CHECK_VALUE(2)|| CHECK_VALUE(3) || CHECK_VALUE(4) || blocks[index].Y1 == 14 || blocks[index].Y2 == 14 || blocks[index].Y3 == 14 || blocks[index].Y4 == 14 )
	{
		return true;
	}
	return false;
}


void clear_screen() 
{
	for(uint8_t y = 0; y < ROWS; ++y)
	{
		for(uint8_t x = 0; x < COLUMNS; ++x)
		{
			screen[y][x].value = 0;
		}
	}
}
int8_t newElementIndex = -1;

void update_screen()
{
	if( newElementIndex != -1 )
	{
		numberOfBlocks = newElementIndex;
		newElementIndex = -1;
		if( !  generate_new_block() )
		{
			exit(0);
		}
	}
	for(uint8_t i = 1; i <= numberOfBlocks; ++i)
	{
		if( ! blocks[i].locked )
		{
			++blocks[i].Y1;
			++blocks[i].Y2;
			++blocks[i].Y3;
			++blocks[i].Y4;
			if( mark_if_locked(i) )
			{
				printf("AAAAAAAAAAAAAAAAAAAA %d\n",i);
				blocks[i].locked = true;
				newElementIndex = numberOfBlocks+1;
			}
		}
	}
	clear_screen();

	for(uint8_t i = 1; i <= numberOfBlocks; ++i)
	{
		screen[blocks[i].Y1][blocks[i].X1].value = 1;
		screen[blocks[i].Y2][blocks[i].X2].value = 1;		
		screen[blocks[i].Y3][blocks[i].X3].value = 1;		
		screen[blocks[i].Y4][blocks[i].X4].value = 1;
		screen[blocks[i].Y1][blocks[i].X1].blockNr = screen[blocks[i].Y2][blocks[i].X2].blockNr = screen[blocks[i].Y3][blocks[i].X3].blockNr = screen[blocks[i].Y4][blocks[i].X4].blockNr = i;
	}
}



int main(int argc, char **argv)
{
	numberOfBlocks = 0;
	newElementIndex = true;;

	while(1)
	{
		update_screen();
		print_screen();
		printf("\n\n");
		sleep(1);
	}
}
