/*
	OJ: UVA
	Problem ID: 11383
	Author: Dogsaur
	Date: 2014-08-07
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

class KM
{
    static const int MAXN = 520;
    static const int INF = 1 << 27;
public:
    int lx[MAXN], ly[MAXN], slack[MAXN];
    int nn, lf[MAXN], mat[MAXN][MAXN];
    bool VisX[MAXN], VisY[MAXN];

    bool Crosspath(int x)
    {
        VisX[x] = true;
        for (int y = 0; y < nn; y++) if (!VisY[y])
            {
                if (lx[x] + ly[y] == mat[x][y])
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
        int d = INF;
        for (int i = 0; i < nn; i++) if (!VisY[i])
                d = min (d, slack[i]);
        for (int i = 0; i < nn; i++)
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
        for (int i = 0; i < nn; i++)
        {
            ly[i] = 0;
            lx[i] = 0;
            lx[i] = -INF;
            for (int j = 0; j < nn; j++)
                lx[i] = max(lx[i], mat[i][j]);
        }
    }

    void km(int _nn)
    {
    	nn = _nn;
        Init();
        for (int i = 0; i < nn; i++)
        {
            for (int j = 0; j < nn; j++) slack[j] = INF;
            while (true)
            {
                memset(VisX, false, sizeof(VisX));
                memset(VisY, false, sizeof(VisY));
                if (Crosspath(i))
                    break;
                else
                    Update();
            }
        }
    }
};

KM solver;
int N;

void input()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &solver.mat[i][j]);
        }
}

void output()
{
    int ans = 0;
    for (int i = 0; i < N-1; i++)
    {
        printf("%d ", solver.lx[i]);
        ans += solver.lx[i];
    }
    printf("%d\n", solver.lx[N-1]);
    ans += solver.lx[N-1];

    for (int i = 0; i < N-1; i++)
    {
        printf("%d ", solver.ly[i]);
        ans += solver.ly[i];
    }
    printf("%d\n", solver.ly[N-1]);
    ans += solver.ly[N-1];

    printf("%d\n", ans);
}
int main()
{
    while (scanf("%d", &N) == 1 )
    {
        input();
        solver.km(N);
        output();
    }
    return 0;
}
