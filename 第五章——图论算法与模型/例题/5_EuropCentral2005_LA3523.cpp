/*
	OJ: Live Archive
	Problem ID: 3523
	Author: Dogsaur
	Date: 2014-05-25
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXN 1100
#define MAXE 1100000
typedef struct edge
{
    edge(int _l, int _r)
    {
        l = _l;
        r = _r;
    }
    int l, r;
} edge;

vector<int> G[MAXN];
vector<int> BCC[MAXN];
stack<edge> S;
int N, M, bcc_cnt, dfs_clock;
int dfn[MAXN], low[MAXN], bcc_color[MAXN], bi_color[MAXN];
bool on_odd[MAXN], dislike[MAXN][MAXN];

void init()
{
    for (int i=0; i<MAXN; i++)
    {
        BCC[i].clear();
        G[i].clear();
    }
    memset(bcc_color, 0, sizeof(bcc_color));
    memset(bi_color, 0, sizeof(bi_color));
    memset(on_odd, false, sizeof(on_odd));
}

void input()
{
    for (int i = 0; i < M; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        dislike[x][y] = true;
        dislike[y][x] = true;
    }
}

void build_graph()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (!dislike[i][j] && i!=j)
            {
                G[i].push_back(j);
            }
        }
}

void dfs(int fa, int u)
{
    low[u] = dfn[u] = dfs_clock++;

    for (int i=0; i<G[u].size(); i++)
    {
        int v = G[u][i];
        if (!dfn[v])
        {
            S.push(edge(u,v));
            dfs(u,v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
            {
                //new biconnected component , only if v is first visited ,
                //otherwise v is not a child of u in dfs tree that can't recognize a max_bcc_sub_grah
                bcc_cnt++;  //cnt should start from 1
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
                    {
                        break;
                    }
                }
            }
        }
        if (v!=fa && dfn[v] < dfn[u])
        {
            S.push(edge(u,v));
            low[u] = min(low[u], dfn[v]);	// "low[u] = min(low[u], low[v]);" is wrong
        }
    }
}

void get_BCC()
{
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    bcc_cnt = 0;
    for (int i=0; i<N; i++)
    {
        if (dfn[i] == 0)
        {
            dfs_clock = 1;
            dfs(-1, i);
        }
    }
}

bool is_bipartite(int u)
{
    for (int i = 0; i<G[u].size(); i++)
    {
        int v = G[u][i];
        if (bcc_color[u] != bcc_color[v])
            continue;
        if (!bi_color[v])
        {
            bi_color[v] = -bi_color[u];
            if (!is_bipartite(v))
                return false;
        }
        if (bi_color[v] == bi_color[u])
            return false;
    }
    return true;
}

int solve()
{
    for (int i=1; i<=bcc_cnt; i++)
    {
        int v = BCC[i][0];
        for (int j=0; j<BCC[i].size(); j++)
            bcc_color[BCC[i][j]] = i;
        memset(bi_color, 0 , sizeof(bi_color));
        bi_color[v] = 1;
        if (!is_bipartite(v))
            for (int j=0; j<BCC[i].size(); j++)
                on_odd[BCC[i][j]] = true;
    }

    int sum =0;
    for (int i =0; i<N; i++)
        if (!on_odd[i])
            sum++;
    return sum;

}
int main()
{
    while (scanf("%d%d",&N,&M),N||M)
    {
        init();
        input();
        build_graph();
        get_BCC();
        cout << solve() << endl;
    }

    return 0;
}
