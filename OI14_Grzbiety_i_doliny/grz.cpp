#include <cstdlib>
#include <cstdio>
#include <vector>
#include <stack>
#include <utility>

const int MAXN = 1000;
const int ny[] = { -1, -1, -1, 0, 0,  1, 1, 1 };
const int nx[] = { -1,  0, 1, -1, 1, -1, 0, 1 };
const int nl = 8;
const int NOTFOUND = -1;

using namespace std;

int main()
{
    int n, summit = 0, valley = 0;
    int map[MAXN][MAXN];
    bool visited[MAXN][MAXN];
    int *stackX, *stackY, top = 0;
    vector<int> nmax, nmin;
    stackX = (int *)malloc(sizeof(int) * MAXN * MAXN + MAXN);
    stackY = (int *)malloc(sizeof(int) * MAXN * MAXN + MAXN);
    scanf("%d", &n);
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &map[i][j]);
            visited[i][j] = false;
        }
    }
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (!visited[i][j])
            {
                int g = nmin.size();
                nmin.push_back(NOTFOUND);
                nmax.push_back(NOTFOUND);
                top = 0;
                stackX[top] = i; stackY[top] = j;
                top++;
                visited[i][j] = true;
                while (top > 0)
                {
                    int cx = stackX[top - 1], cy = stackY[top - 1];
                    top--;
                    for (int nc = 0; nc < nl; nc++)
                    {
                        int x = cx + nx[nc], y = cy + ny[nc];
                        if (0 <= x && x < n && 0 <= y && y < n)
                        {
                            if (map[cx][cy] == map[x][y] &&
                                    visited[x][y] == false)
                            {
                                visited[x][y] = true;
                                stackX[top] = x;
                                stackY[top] = y;
                                top++;
                            }
                            else if (map[x][y] < map[cx][cy])
                                nmin[g] = map[x][y];
                            else if (map[x][y] > map[cx][cy])
                                nmax[g] = map[x][y];
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < nmin.size(); i++)
    {
        if (nmax[i] == NOTFOUND && nmin[i] == NOTFOUND)
        {
            valley = 1;
            summit = 1;
        }
        else if (nmin[i] == NOTFOUND)
            valley++;
        else if (nmax[i] == NOTFOUND)
            summit++;
    }
    printf("%d %d\n", summit, valley);
    return 0;
}
