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
	uint8_t active;
	uint8_t blockNr;
};

ScreenField screen[ROWS][COLUMNS];


struct Block
{
        uint8_t X1 : 4;
	uint8_t X2 : 4;
	uint8_t X3 : 4;
	uint8_t X4 : 4;

	uint8_t Y1 : 3;
	uint8_t Y2 : 3;
	uint8_t Y3 : 3;
	uint8_t Y4 : 3;

	uint8_t locked : 1;
};


Block blocks[20];
uint8_t numberOfBlocks = 0;



void make_screen()
{

}

void print_screen()
{
	system("clear");
	REP(y,ROWS)
	{
		REP(x,COLUMNS)
		{
//			if( screen[y][x] ) printf("0");
//			else printf(" ");
		}
	}
}

bool can_move(Block * test)
{
	if( blocks[screen[test->Y1][test->X1].blockNr].locked )
	{
	}
}


void update_screen()
{

}


int main(int argc, char **argv)
{
	printf("AAAAAAAAAAA");


}
