#include <cstdio>
#include <climits>
#include <stack>
#include <vector>
#include <set>

#define MAXN 100000
#define MAXK 100000
#define MAXP 500000

using namespace std;

struct futureCmp
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const
    {
        if (a.first != b.first)
            return a.first > b.first;
        else
            return a.second > b.second;
    }
};

void printFuture(set<pair<int, int>, futureCmp> future)
{
    set<pair<int, int>, futureCmp> our =
        set<pair<int, int>, futureCmp>(future);
    printf("Future:\n");
    while (!our.empty())
    {
        printf("C: %d N: %d\n", our.begin()->second, our.begin()->first);
        our.erase(our.begin());
    }
}

int main()
{
    int n, k, p, a, onFloor = 0, score = 0;
    int flow[MAXP], occCount[MAXN];
    bool floor[MAXN];
    vector<int> occ[MAXN]; 
    set<pair<int, int>, futureCmp > future;
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 0; i < p; i++)
    {
        scanf("%d", &a);
        a--;
        flow[i] = a;
        occ[a].push_back(i);
    }
    for (int i = 0; i < n; i++)
        occ[i].push_back(INT_MAX);
    for (int i = 0; i < n; i++)
        occCount[i] = 0;
    for (int i = 0; i < n; i++)
        floor[i] = false;
    for (int i = 0; i < p; i++)
    {
        int curr = flow[i];
        //printFuture(future);
        if (!floor[curr])
        {
            if (onFloor == k)
            {
                //printf("Putting on shelf: %d (next occ: %d)\n",
                //        future.begin()->second,
                //        future.begin()->first);
                floor[future.begin()->second] = false;
                future.erase(future.begin());
            }
            else
                onFloor++;
            //printf("Putting on floor: %d\n", curr);
            floor[curr] = true;
            score++;
        }
        future.erase(pair<int, int>(occ[curr][occCount[curr]], curr));
        occCount[curr]++;
        future.insert(pair<int, int>(occ[curr][occCount[curr]], curr)); 
    }
    printf("%d\n", score);
    return 0;
}
