/*
	OJ: LA
	Problem ID: 5135
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
typedef struct edge
{
	edge(int _l, int _r)
	{
		l = _l;
		r = _r;
	}
	int l, r;
}edge;

int M,shaft_cnt, bcc_cnt, dfs_clock, bcc_color[MAXN], dfn[MAXN], low[MAXN];
bool iscut[MAXN];
long long resolution_cnt;
vector<int> G[MAXN], BCC[MAXN];
stack <edge> S;

void init()
{
	for (int i=0; i<MAXN; i++)
	{
		G[i].clear();
		BCC[i].clear();
	}
	memset(iscut, false, sizeof(iscut));
	shaft_cnt = 0;
	resolution_cnt = 1;
}
void input()
{
    for (int i = 0 ; i < M; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}

void add_bcc(int u, int v)
{
	bcc_cnt ++;
    while (true)
    {
        int x = S.top().l;
        int y = S.top().r;
        S.pop();
        if (bcc_color[x] != bcc_cnt)
        {
            BCC[bcc_cnt].push_back(x);
            bcc_color[x] = bcc_cnt;
        }
        if (bcc_color[y] != bcc_cnt)
        {
            BCC[bcc_cnt].push_back(y);
            bcc_color[y] = bcc_cnt;
        }
        if (x == u && y == v)
            break;
    }
}
void dfs(int u, int fa)
{
	cout << "u: " << u << endl;
    dfn[u] = low[u] = dfs_clock++;
    int child = 0;
    for (int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if (!dfn[v])
        {
        	child ++;
            S.push(edge(u, v));
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
            {
                iscut[u] = true;
				add_bcc(u, v);
            }
        }
        else if(dfn[v] < dfn[u] && v != fa)
        {
            S.push(edge(u, v));
            low[u] = min(low[u], dfn[v]);
        }

    }
    if (child == 1 && fa < 0 ) // !!! root is always a cut unless only one child it has.
    	iscut[u] = false;
}

void get_bcc()
{
	bcc_cnt = 0;
    dfs_clock = 1;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(bcc_color, 0, sizeof(bcc_color));
    dfs(0,-1);
}

void solve()
{
	if (bcc_cnt == 1)
	{
		shaft_cnt = 2;
		resolution_cnt = (long long) BCC[1].size() * (BCC[1].size() - 1) / 2;
		return;
	}

	for (int i = 1; i<=bcc_cnt; i++)
	{
		int cut_cnt = 0;
		for (int j =0; j<BCC[i].size(); j++)
			if (iscut[BCC[i][j]])
				cut_cnt++;
		if (cut_cnt == 1)
		{
			shaft_cnt ++;
			resolution_cnt *= (long long) (BCC[i].size() - cut_cnt);
		}
	}
}

void output()
{
	static int icase = 0;
	cout << "Case " << ++icase << ": " << shaft_cnt << " " << resolution_cnt << endl;
}

int main()
{
    while (cin >> M, M)
    {
    	init();
        input();
        get_bcc();
        solve();
        output();
    }
    return 0;
}
