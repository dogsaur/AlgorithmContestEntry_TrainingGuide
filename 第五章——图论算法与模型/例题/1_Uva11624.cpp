/*
	OJ: UVA
	Problem ID: 11624
	Author: Dogsaur
	Date: 2014-05-20
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

#define MAXR 1100
#define MAXC 1100

typedef struct point
{
    point(int rr, int cc)
    {
        r = rr;
        c = cc;
    }
    point(int rr, int cc, int tmp_time_maze)
    {
        r = rr;
        c = cc;
        time_maze = tmp_time_maze;
    }
    int r,c,time_maze;
} point;

const int dr[]= {0,0,1,-1},dc[]= {-1,1,0,0};

int R,C,ans;
int fire_time[MAXR][MAXC];
char maze[MAXR][MAXC];
bool visited[MAXR][MAXC];

void input()
{
    cin >> R >> C;
    for (int i=0; i<R; i++)
        for (int j=0; j<C; j++)
        {
            cin >> maze[i][j];
        }
}

bool islegal(int r, int c)
{
    return r>=0 && r<R && c>=0 && c<C;
}

void calc_firetime()
{
    memset(fire_time, 0x7f, sizeof(fire_time));
    queue<point> fireque;
    for (int i=0; i<R; i++)
        for (int j=0; j<C; j++)
        {
            if (maze[i][j]=='F')
            {
                fireque.push(point(i,j));
                fire_time[i][j] = 0;
            }
        }
    while (!fireque.empty())
    {
        point u = fireque.front();
        fireque.pop();
        for (int i=0; i<4; i++)
        {
            int r = u.r + dr[i];
            int c = u.c + dc[i];
            if (islegal(r,c) &&	fire_time[r][c]>fire_time[u.r][u.c]+1 && maze[r][c]!='#')
            {
                fireque.push(point(r,c));
                fire_time[r][c] = fire_time[u.r][u.c]+1;
            }
        }
    }
}
void solve()
{
    queue<point> joeque;
    memset(visited, false, sizeof(visited));
    ans = -1;
    for (int i=0; i<R; i++)
        for (int j=0; j<C; j++)
        {
            if (maze[i][j]=='J')
            {
                joeque.push(point(i,j,0));
                visited[i][j] = true;
            }
        }

    while (!joeque.empty())
    {
        point u = joeque.front();
        joeque.pop();

        for (int i=0; i<4; i++)
        {
            int r = u.r + dr[i];
            int c = u.c + dc[i];
            int t = u.time_maze +1;
            if (islegal(r, c))
            {

                if (fire_time[r][c] > t && !visited[r][c] && maze[r][c]!='#')
                {
                    visited[r][c] = true;
                    joeque.push(point(r,c,t));
                }
            }
            else
            {
                ans = t;
                return;
            }
        }
    }
}
void output()
{
/*
    for (int i = 0; i<R; i++)
    {
        for (int j = 0; j<C; j++)
        {
            cout << fire_time[i][j] <<"\t";
        }
        cout << endl;
    }

    for (int i = 0; i<R; i++)
    {
        for (int j = 0; j<C; j++)
        {
            cout << visited[i][j] <<"\t";
        }
        cout << endl;
    }
*/
    if (ans != -1)
        cout << ans << endl;
    else
        cout << "IMPOSSIBLE" <<endl;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        input();
        calc_firetime();
        solve();
        output();
    }
    return 0;
}
