/*
	OJ: Live Archive
	Problem ID: Seoul2008_LA4255
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

#define MAXN 20

int N,sum[MAXN], in_degree[MAXN];
bool matrix[MAXN][MAXN];

void input()
{
	memset(in_degree, 0, sizeof(in_degree));
    cin >> N;
    for (int i = 1; i<=N; i++)
        for (int j = i; j<=N; j++)
        {
            char ch;
            cin >> ch;
            if (ch == '+')
            {
                matrix[i-1][j] = true;
                in_degree[j]++;
            }
            if (ch == '-')
            {
                matrix[j][i-1] = true;
                in_degree[i-1]++;
            }
        }
}

void solve()
{

    queue<int> que;
    for (int i=0; i<=N; i++)
    {
        if (in_degree[i]==0)
        {
            sum[i] = 0;
            que.push(i);
        }
    }

    while (!que.empty())
    {
        int v = que.front();
        que.pop();
        for (int i=0; i<=N; i++)
        {
            if (matrix[v][i])
            {
                sum[i] = sum[v]+1;
                matrix[v][i] = false;
                in_degree[i]--;
                if (in_degree[i]==0)
                    que.push(i);
            }
        }
    }
}
void output()
{
    for (int i=1; i<N; i++)
    {
    	cout << sum[i] -sum[i-1] << " ";
    }
    cout <<sum[N] - sum[N-1] <<endl;
}
int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        input();
        solve();
        output();
    }
    return 0;
}
