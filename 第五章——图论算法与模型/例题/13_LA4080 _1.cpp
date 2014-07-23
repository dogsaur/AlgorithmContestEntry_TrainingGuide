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

#define MAXN 110
typedef struct Edge
{
    Edge(int _l, int _r, int _w):l(_l),r(_r),w(_w) {};
    int l,r,w;
} Edge;


int N, M, L;
int dist[MAXN][MAXN];
vector<Edge> edges;
void init()
{
    edges.clear();
}
void input()
{
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        edges.push_back(Edge(u, v, w));
    }
}
void build_graph(int x)
{
    for (int u = 0;  u < N; u++)
        for (int v = 0; v < N; v++)
            dist[u][v] = L;
    for (int u = 0;  u < N; u++)
        dist[u][u] = 0;

    for (int i = 0; i < M; i++)
    {
        if (i == x)
            continue;
        int u = edges[i].l;
        int v = edges[i].r;
        dist[u][v] = min(dist[u][v], edges[i].w);
        dist[v][u] = min(dist[v][u], edges[i].w);
    }
}
int floyd()
{
    for (int k = 0; k < N; k++)
        for (int u = 0;  u < N; u++)
            for (int v = 0; v < N; v++)
                if (dist[u][k] + dist[k][v] < dist[u][v])
                    dist[u][v] = dist[u][k] + dist[k][v];
    int sum = 0;
    for (int u = 0;  u < N; u++)
        for (int v = 0; v < N; v++)
        {
            if (v == u)
                continue;
            sum += dist[u][v];
        }
    return sum;
}
int main()
{
    while(scanf("%d%d%d",&N, &M, &L) == 3)
    {
        init();
        input();
        build_graph(-1);
        cout << floyd() << " ";
        int ans = -1;
        int chosen = -1;
        for (int i = 0; i < M; i++)
        {
            build_graph(i);
            ans = max(ans, floyd());
        }
        cout << ans << endl;
    }
    return 0;
}
