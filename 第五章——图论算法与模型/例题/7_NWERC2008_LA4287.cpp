/*
	OJ: LA
	Problem ID: 4287
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
#define MAXN 21000

int N, M, scc_cnt, dfs_clock, scc_color[MAXN], dfn[MAXN], low[MAXN];
bool isin0[MAXN], isout0[MAXN];
vector<int> G[MAXN];
stack<int> S;
void init()
{
	for (int i = 0; i<MAXN; i++)
		G[i].clear();
}
void input()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        G[u].push_back(v);
    }
}

void add_scc(int x)
{
	scc_cnt++;
    while (true)
	{
		int y = S.top();
		S.pop();
		scc_color[y] = scc_cnt;
		if (x==y)
			break;
	}
}
void dfs(int x)
{
	low[x] = dfn[x] = ++dfs_clock;
	S.push(x);
	for (int i = 0; i<G[x].size(); i++)
	{
        int y = G[x][i];
        //cout << y << endl;
        if (!dfn[y])
		{
			dfs(y);
			low[x] = min(low[x], low[y]);
		}
		else if (!scc_color[y]) // insure y is in the current dfs tree
		{
            low[x] = min(low[x], dfn[y]);
		}
	}
	if (low[x] == dfn[x])
	{
		add_scc(x);
	}
}
void get_scc()
{
    scc_cnt = dfs_clock = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(scc_color, 0 , sizeof(scc_color));
    for (int i = 0; i < N; i++)
    {
    	if (!dfn[i])
    		dfs(i);
    }
}
int solve()
{
	for (int i = 1; i <= scc_cnt; i++)
	{
		isin0[i] = true;
		isout0[i] = true;
	}
	for (int u = 0; u<N; u++)
		for (int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if (scc_color[u] != scc_color[v])
			{
				isout0[scc_color[u]] = false;
				isin0[scc_color[v]] = false;
			}
		}
	if (scc_cnt==1)
		return 0;
	int sum1=0, sum2=0;
	for (int i = 1; i <= scc_cnt; i++)
	{
		if (isin0[i])
			sum1++;
		if (isout0[i])
			sum2++;
	}
	return max(sum1, sum2);
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
    	init();
		input();
		get_scc();
		cout << solve() << endl;
    }
    return 0;
}
