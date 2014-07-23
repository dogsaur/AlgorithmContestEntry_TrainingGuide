/*
	OJ: UVA
	Problem ID: 10917
	Author: Dogsaur
	Date: 2014-07-21
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

#define MAXN 2000
#define INF 1<<30
typedef struct HeapNode
{
    HeapNode(int num, int dist):num(num), dist(dist) {}
    bool operator <(const HeapNode& rhs)const
    {
        return dist > rhs.dist;
    }
    int num, dist;
} HeapNode;
typedef struct Edge
{
    Edge(int l, int r, int dist):l(l), r(r), dist(dist) {}
    int l, r, dist;
} Edge;

int N, M, S, T, dist[MAXN], pre[MAXN], dp[MAXN];
vector<Edge> G[MAXN];
vector<int> G1[MAXN];
void init()
{
    for (int i = 0; i<N; i++)
    {
        G[i].clear();
        G1[i].clear();
    }
    memset(dp, -1, sizeof(dp));
}
void input()
{
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        G[u].push_back(Edge(u, v, w));
        G[v].push_back(Edge(v, u, w));
    }
    S = 0;
    T = 1;
}

bool done[MAXN];
void dijkstra(int source, int cnt, int dist[], int pre[])
{
    for (int i =0; i < cnt; i++)
        dist[i] = INF;
    memset(done, false, sizeof(done));

    priority_queue<HeapNode> PQ;
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
            if (dist[u] + G[u][i].dist < dist[v])
            {
                dist[v] = dist[u] + G[u][i].dist;
                pre[v] = u;
                PQ.push(HeapNode(v, dist[v]));
            }
        }
    }
}

int DP(int root)
{
    if(dp[root]!=-1)
    {
        return dp[root];
    }
    if(root==1)
    {
        return dp[root]=1;
    }
    int i;
    dp[root]=0;
    for(i=0; i<G[root].size(); i++)
    {
        int to = G[root][i].r;
        if(dist[root]>dist[to])
        {
            dp[root]+=DP(to);
        }
    }
    return dp[root];
}

int main()
{
    while (cin >> N, N)
    {
        cin >> M;
        init();
        input();
        dijkstra(T, N, dist, pre);
        cout << DP(0) << endl;
    }
    return 0;
}
