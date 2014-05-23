/*
	OJ: UVA
	Problem ID: 10054
	Author: Dogsaur
	Date: 2014-05-22
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXE 2100
#define MAXN 60

int N,matrix[MAXN][MAXN],degree[MAXN];

void init()
{
    memset(degree, 0, sizeof(degree));
    memset(matrix, 0, sizeof(matrix));
}

void input()
{
    cin >> N;
    for (int i=0; i<N; i++)
    {
        int x, y;
        cin >> x >> y;
        matrix[x][y]++;
        matrix[y][x]++;
        degree[x]++;
        degree[y]++;
    }
}

void euler(int x)
{
    for (int i = 0; i<55; i++)
    {
        if (matrix[x][i])
        {
            matrix[x][i]--;
            matrix[i][x]--;
            //cout << x << " " << i << endl; 一直WA到现在，SPJ的问题吗？
            euler(i);
            cout << i << " " << x << endl;
        }
    }
}

bool solve()
{
    for (int i=0; i<55; i++)
        if (degree[i]%2 !=0)
            return false;
    return true;
}

void output(bool result)
{
    static int icase = 0;
    if (icase != 0)
    {
        cout << endl;
    }
    cout << "Case #" << ++icase <<endl;

    if (!result)
    {
        cout << "some beads may be lost" << endl;
        return;
    }

    for (int i=0; i<55; i++)
        if (degree[i])
        {
            euler(i);
            break;
        }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        init();
        input();
        output(solve());
    }
    return 0;
}

