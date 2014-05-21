/*
	OJ: UVA
	Problem ID: 10047
	Author: Dogsaur
	Date: 2014-05-21
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

#define MAXR 30
#define MAXC 30

typedef struct point
{
    point() {};
    point(int _r, int _c, int _dir, int _col, int _t)
    {
        r = _r;
        c = _c;
        dir = _dir;
        color = _col;
        t = _t;
    }
    int r, c, dir, color,t;
} point;

int R, C, icase=0;
point S, T;
char maze[MAXR][MAXC];
bool visited[MAXR][MAXC][10][10];

const int dr[]= {-1,0,1,0}; //血一样的教训，北边行数是减的 不是坐标系啊亲！ dr[]= {1,0,-1,0};
const int dc[]= {0,1,0,-1};

void input()
{
    for (int i=0; i<R; i++)
        for (int j=0; j<C; j++)
        {
            cin >> maze[i][j];

            if (maze[i][j] == 'S')
            {
                S = point(i, j, 0, 2, 0);
            }
            if (maze[i][j] == 'T')
            {
                T = point(i, j, 0, 2, 0);
            }
        }
}

int get_dr(int x, int dir)
{
    if (x!=0)
        return 0;
    return dr[dir];
}
int get_dc(int x, int dir)
{
    if (x!=0)
        return 0;
    return dc[dir];
}
int next_dir(int x, int dir)
{
    return (dir + x + 4) % 4;
}

int next_color(int x, int color)
{
    if (x!=0)
        return color;
    return (color + 1) % 5;
}
bool islegal(point v)
{
    return v.r>=0 && v.r<R && v.c>=0 && v.c<C && maze[v.r][v.c] != '#';
}
bool istarget(point v)
{
    return v.r == T.r && v.c == T.c && v.color == T.color;
}
int bfs()
{
    queue<point> que;
    memset(visited, false, sizeof(visited));

    if (istarget(S))
        return 0;

    que.push(S);
    visited[S.r][S.c][S.dir][S.color] = true;
    while (!que.empty())
    {
        point u = que.front();
        que.pop();
        for (int i = -1; i<2; i++)
        {
            int r = u.r + get_dr(i, u.dir);
            int c = u.c + get_dc(i, u.dir);
            int dir = next_dir(i, u.dir);
            int color = next_color(i, u.color);
            int t = u.t+1;

            point v = point(r,c,dir,color,t);
            if (islegal(v) && !visited[v.r][v.c][v.dir][v.color])
            {
                que.push(v);
                visited[v.r][v.c][v.dir][v.color] = true;
            }
            if (istarget(v))
            {
                return v.t;
            }
        }
    }
    return -1;
}
void output(int x)
{
    static bool flag = false;
    if (flag)
    {
        cout << endl;
    }
    flag = true;

    cout << "Case #" << ++icase <<endl;

    if (x==-1)
        cout << "destination not reachable" << endl;
    else
        cout << "minimum time = " << x <<" sec" << endl;

}
int main()
{
    while (cin >> R >> C, R || C)
    {
        input();
        output(bfs());
    }
    return 0;
}
