#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000000;

int main()
{
    int n, m;
    vector<int> occ[MAXN + 1];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        occ[a].push_back(i);
    }
    scanf("%d", &m);
    while (m--)
    {
        bool possible = true;
        int c, i = -1;
        scanf("%d", &c);
        while (c--)
        {
            int a;
            scanf("%d", &a);
            vector<int>::iterator iter = upper_bound(occ[a].begin(),
                    occ[a].end(), i);
            if (iter == occ[a].end())
                possible = false;
            else
                i = *iter;
        }
        if (possible)
            printf("TAK\n");
        else
            printf("NIE\n");
    }
    return 0;
}
