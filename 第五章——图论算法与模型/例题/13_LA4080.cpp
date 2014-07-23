/*
	OJ: LA
	Problem ID: 4080
	Author: Dogsaur
	Date: 2014-07-23
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

const int MAXN = 110;
int INF = 1<<30;
typedef struct Edge
{
	Edge(int _l, int _r, int _w):l(_l),r(_r),w(_w){};
	int l,r,w;
}Edge;

typedef struct HeapNode
{
	HeapNode(int _num, int _w):num(_num),w(_w){};
	bool operator <(const HeapNode& rhs)const{return w > rhs.w;}
	int num, w;
}HeapNode;

typedef struct Dijkstra
{
	int v_cnt;
	vector<Edge> G[MAXN];
	int _dist[MAXN], _pre[MAXN];
	int *dist, *pre;

	void init(int n)
	{
		v_cnt = n;
		dist = _dist;
		pre = _pre;
		for (int i = 0; i < v_cnt; i++)
		{
			G[i].clear();
		}
	}
	void add_edge(int l, int r, int w)
	{
        G[l].push_back(Edge(l,r,w));
	}
	void dijkstra(int source, int _dist[], int _pre[])
	{
		pre = _pre;
		return dijkstra(source, _dist);
	}
	void dijkstra(int source, int _dist[])
	{
		dist = _dist;
		return dijkstra(source);
	}
	void dijkstra(int source)
	{
		priority_queue<HeapNode> PQ;
		bool done[MAXN];
		memset(done, false, sizeof(done));
		for (int i = 0; i < v_cnt; i++)
		{
			dist[i] = INF;
			pre[i] = -1;
		}
		dist[source] = 0;
		PQ.push(HeapNode(source, 0));
		while (!PQ.empty())
		{
			int u = PQ.top().num;
			PQ.pop();
			if (done[u])
				continue;
			done[u] = true;
			for (int i = 0; i < G[u].size(); i++)
			{
				int v = G[u][i].r;
				if (dist[u] + G[u][i].w < dist[v])
				{
					dist[v] = dist[u] + G[u][i].w;
					pre[v] = u;
					PQ.push(HeapNode(v, dist[v]));
				}
			}
		}
	}
}Dijkstra;

Dijkstra Dij;
int N, M, L;
int dist0[MAXN][MAXN],dist[MAXN][MAXN], pre[MAXN][MAXN];
bool on_dij_tree[MAXN][MAXN][MAXN];

void init()
{
    memset(on_dij_tree, false, sizeof(on_dij_tree));
}
void input()
{
    INF = L;
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        Dij.add_edge(u, v, w);
        Dij.add_edge(v, u, w);
    }
}

int calc(int x, int y)
{
    for (int i = 0; i< N; i++)
    {
        if (x<0 || on_dij_tree[i][x][y] || x<0 )
        {
            Dij.dijkstra(i, dist[i], pre[i]);
        }
    }
    int sum = 0;
    for (int u = 0;  u < N; u++)
    {
        for (int v = 0; v < N; v++)
        {
            sum += dist[u][v];
            if (x < 0)
            {
                dist0[u][v] = dist[u][v];
            }
            else
            {
                dist[u][v] = dist0[u][v];
            }
        }
    }
    return sum;
}

void mark()
{
    for (int u = 0;  u < N; u++)
    {
        for (int v = 0; v < N; v++)
        {
            int p = v;
            while (p>=0)
            {
                on_dij_tree[u][p][pre[u][p]] = true;
                on_dij_tree[u][pre[u][p]][p] = true;
                p = pre[u][p];
            }
        }
    }
}
int solve()
{
    cout << calc(-1, -1) << " ";

    mark();

    int ans = -1;


    for (int u = 0; u < N; u++)
        for (vector<Edge>::iterator itr = Dij.G[u].begin(); itr!=Dij.G[u].end(); ++itr)
        {

            Edge e(itr->l, itr->r, itr->w);
            Edge e_(0, 0, 0);
            int v = e.r;

            /* when use erase to delete elements in a vector,	//
         	// be careful for its iterator will move forward	*/

            //remove forward edge
            Dij.G[u].erase(itr);

            //remove backward edge
            vector<Edge>::iterator itrv;
            for (itrv = Dij.G[v].begin(); itrv!=Dij.G[v].end(); itrv++)
            {
                e_ = *itrv;
                if (e_.l == e.r && e_.r == e.l && e_.w == e.w)
                {
                    Dij.G[v].erase(itrv);
                    break;
                }
            }
			ans = max(ans, calc(u, v));

			//revert
            Dij.G[u].insert(itr, e);
            Dij.G[v].insert(itrv, e_);
        }
    cout << ans <<endl;
}
int main()
{
    while (scanf("%d%d%d",&N, &M, &L)==3)
    {
        init();
        Dij.init(N);
        input();
        solve();
    }
    return 0;
}
