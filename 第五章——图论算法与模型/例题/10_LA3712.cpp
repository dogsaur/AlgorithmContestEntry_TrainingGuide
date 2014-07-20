/*
	OJ: LA
	Problem ID: 3713
	Author: Dogsaur
	Date: 2014-07-20
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXN 110000
int N, M, age[MAXN];
bool mark[2*MAXN], issenior[MAXN];
vector<int> G[2*MAXN];
stack<int> S;

void init()
{
    for (int i = 0; i < 2*N; i++)
    {
        G[i].clear();
    }
    memset(mark, false, sizeof(mark));
}

bool issametype(int x, int y)
{
	return issenior[x] == issenior[y];
}

void add_clause(int x, int xval, int y, int yval)
{
    x = 2 * x + xval^1;
    y = 2 * y + yval^1;
    G[x^1].push_back(y);
    G[y^1].push_back(x);
}

void input()
{
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> age[i];
        sum += age[i];
    }
    for (int i = 0; i < N; i++)
    {
    	if (age[i] * N >= sum)
    		issenior[i] = true;
		else
			issenior[i] = false;
    }
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        if (issametype(u,v))
        {
            add_clause(u, 1, v, 1);
            add_clause(u, 0, v, 0);
        }
        else
        {
            add_clause(u, 1, v, 1);
        }
    }
}

bool dfs(int x)
{
    if (mark[x^1]) return false;
    if (mark[x]) return true;
    mark[x] = true;
    S.push(x);
    for (int i =0; i < G[x].size(); i++)
        if (!dfs(G[x][i]))
            return false;
    return true;
}

bool solve()
{
    for (int i = 0; i < 2*N; i+=2)
    {
        if (!mark[i] && !mark[i+1])
        {
            if (!dfs(i+1))
            {
                while (!S.empty())
                {
                    mark[S.top()] = false;
                    S.pop();
                }
                if (!dfs(i))
                    return false;
            }
        }
    }
    return true;
}

void output(bool result)
{
    if (!result)
    {
        cout << "No solution." << endl;
        return;
    }
    for (int i = 0; i < N; i++)
    {
        if (mark[2*i])
        {
            if (issenior[i])
                cout << "A" << endl;
            else
                cout << "B" << endl;
        }
        else
        {
            cout << "C" << endl;
        }
    }
}

int main()
{
    while (cin >> N >> M, N || M)
    {
        init();
        input();
        output(solve());
    }
    return 0;
}
