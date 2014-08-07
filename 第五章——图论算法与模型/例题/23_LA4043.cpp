/*
	OJ: LA
	Problem ID: 4043
	Author: Dogsaur
	Date: 2014-08-08
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
#include <cmath>
using namespace std;
const int MAXN = 200;
const double EPS = 1e-7;
const int INF = 1 << 27;

int N, lf[MAXN];
double mat[MAXN][MAXN];
double lx[MAXN], ly[MAXN], slack[MAXN];
bool VisX[MAXN], VisY[MAXN];
bool eq(double x, double y)
{
    return abs(x - y) < EPS;
}

bool Crosspath(int x)
{
    VisX[x] = true;
    for (int y = 0; y < N; y++) if (!VisY[y])
        {
            if (eq(lx[x]+ly[y], mat[x][y]))
            {
                VisY[y] = true;
                if (lf[y] == -1 || Crosspath(lf[y]))
                {
                    lf[y] = x;
                    return true;
                }
            }
            else
            {
                slack[y] = min(slack[y], lx[x] + ly[y] - mat[x][y]);
            }
        }
    return false;
}

void Update()
{
    double d = INF;
    for (int i = 0; i < N; i++) if (!VisY[i])
            d = min (d, slack[i]);
    /*for (int i = 0; i < N; i++) if (VisX[i])
    	for (int j = 0; j < N; j++) if (!VisY[j])
    		d = min (d, lx[i] + ly[j] - mat[i][j]);
    */
    //cout << d << endl;
    for (int i = 0; i < N; i++)
    {
        if (VisX[i]) lx[i] -=d;
        if (VisY[i])
            ly[i] +=d;
        else
            slack[i] -= d;
    }
}

void Init()
{
    memset(lf, -1, sizeof(lf));
    for (int i = 0; i < N; i++)
    {
        ly[i] = 0;
        lx[i] = 0;
        //lx[i] = -INF;
        //for (int j = 0; j < N; j++)
        //lx[i] = max(lx[i], mat[i][j]);
    }
}

void KM()
{
    Init();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) slack[j] = INF;
        while (true)
        {
            memset(VisX, false, sizeof(VisX));
            memset(VisY, false, sizeof(VisY));
            if (Crosspath(i))
                break;
            else
                Update();
            //cout << i << " "; //
        }
    }
}

pair<double, double> black[MAXN], white[MAXN];
double dist(int u, int v)
{
    double x = black[u].first - white[v].first;
    double y = black[u].second - white[v].second;
    return sqrt(x * x + y * y);
}

void input()
{
    for (int i = 0; i < N; i++)
        cin >> white[i].first >> white[i].second;
    for (int i = 0; i < N; i++)
        cin >> black[i].first >> black[i].second;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = -dist(i, j);
}

void output()
{
    for (int i = 0; i < N; i++)
        cout << lf[i]+1 << endl;
    cout << endl;
}

int main()
{
    while (scanf("%d", &N) == 1)
    {
        input();
        KM();
        output();
    }
    return 0;
}
