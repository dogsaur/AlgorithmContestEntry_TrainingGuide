/*
	OJ: UVA
	Problem ID: 11324
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

#define MAXN 1100

int N, M, scc_cnt, dfs_clock;
int dfn[MAXN], low[MAXN], scc_color[MAXN], in_degree[MAXN], V[MAXN], dp[MAXN];
vector<int> G[MAXN];
stack<int> S;
queue<int> Q;
bool mat[MAXN][MAXN];

void init()
{
	for (int i = 0; i <=MAXN; i++)
	{
		G[i].clear();
	}
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
		if (y == x)
			break;
	}
}
void dfs(int x)
{
	low[x] = dfn[x] = ++dfs_clock;
	S.push(x);
	for (int i = 0; i < G[x].size(); i++)
	{
		int y = G[x][i];
		if (!dfn[y])
		{
			dfs(y);
			low[x] = min(low[x], low[y]);
		}
		else if (!scc_color[y])
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
	for (int i = 0; i<N; i++)
	{
		if (!dfn[i])
			dfs(i);
	}
}
void compress_graph()
{
	memset(V, 0, sizeof(V));
	for (int i = 0; i < N; i++)
	{
		V[scc_color[i]]++;
	}

	memset(in_degree, 0 , sizeof(in_degree));
	memset(mat, false, sizeof(mat));
	for (int u = 0; u < N; u++)
		for (int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if (scc_color[u] != scc_color[v])
			{
				mat[scc_color[u]][scc_color[v]] = true;
				in_degree[scc_color[v]]++;
			}
		}
}
int solve()
{
	memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= scc_cnt; i++)
    {
    	if (in_degree[i] == 0)
    	{
    		Q.push(i);
    		dp[i] = V[i];
    	}
    }
    while (!Q.empty())
	{
        int u = Q.front();
        Q.pop();
        for (int v = 1; v<=scc_cnt; v++)
        {
        	if (!mat[u][v])
        		continue;
        	Q.push(v);
            dp[v] = max(dp[v], dp[u]+V[v]);
        }
	}
	int ans = 0;
	for (int v = 1; v <= scc_cnt; v++ )
	{
		ans = max(ans, dp[v]);
	}
	return ans;
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
    	compress_graph();
    	cout << solve() << endl;
    }
    return 0;
}
