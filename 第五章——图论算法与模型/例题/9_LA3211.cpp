/*
	OJ: LA
	Problem ID: 3211
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

#define MAXN 5000
int N,et[MAXN], lt[MAXN], mark[MAXN];
vector<int> G[MAXN];
stack<int> S;

// returns the max time
int input()
{
    int maxt = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> et[i] >> lt[i];
        maxt = max(maxt, lt[i]);
    }
    return maxt;
}

void init()
{
	for (int i = 0; i < 2*N; i++)
	{
		G[i].clear();
	}
	memset(mark, 0, sizeof(mark));
}

void add_clause(int x, int xval, int y, int yval)
{
	x = 2*x + xval^1;
	y = 2*y + yval^1;
	G[x^1].push_back(y);
	G[y^1].push_back(x);
}

bool dfs(int x)
{
    if (mark[x^1])
    	return false;
	if (mark[x])
		return true;
	mark[x] = true;
	S.push(x);
	for (int i = 0; i < G[x].size(); i++)
	{
		if (!dfs(G[x][i]))
			return false;
	}
	return true;
}

bool solve()
{
	for (int i = 0; i < N*2; i+=2)
		if (!mark[i] && !mark[i+1])
		{
			if (!dfs(i))
			{
				while (!S.empty())
				{
					mark[S.top()] = false;
					//cout << S.top() << "- ";
					S.pop();
				}
				//cout << endl;
				if (!dfs(i+1))
					return false;
			}
		}
		return true;
}

bool test(int interval)
{
	init();
    for (int i = 0; i < N; i++)
        for (int j = i+1; j < N; j++)
        {
            if (abs(et[i]-et[j]) < interval)
                add_clause(i, 1, j, 1);
            if (abs(et[i]-lt[j]) < interval)
                add_clause(i, 1, j, 0);
            if (abs(lt[i]-et[j]) < interval)
                add_clause(i, 0, j, 1);
            if (abs(lt[i]-lt[j]) < interval)
                add_clause(i, 0, j, 0);
        }
    return solve();
}

int bi_search(int maxt)
{
    int l = 0, r = maxt;
    while (l < r)
    {
        int mid = (l+r+1)/2;
        if (test(mid))
            l = mid;
        else
            r = mid-1;
    }
    return l;
}

int main()
{
    while (scanf("%d",&N)==1)
    {
        cout << bi_search(input()) << endl;
    }
    return 0;
}
