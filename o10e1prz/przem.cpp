#include <cstdio>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

class PathNode
{
    public:
        int node;
        int cost;
        PathNode(int node, int cost)
        {
            this->node = node;
            this->cost = cost;
        }
};

struct PathNodeCompare {
    bool operator()(const PathNode &a, const PathNode &b)
    {
        if (a.cost != b.cost)
            return (a.cost > b.cost);
        return a.node > b.node;
    }
};

typedef priority_queue<PathNode, vector<PathNode>, PathNodeCompare>
        PathQueue;

int main()
{
    const int gold = 0;
    int n, k;
    scanf("%d", &n);
    int tax[n];
    bool visited[n]; for (int i = 0; i < n; i++) visited[i] = false;
    vector<int> edges[n];
    vector<int> costs[n];
    vector<int> reverse_edges[n];
    vector<int> reverse_costs[n];
    int costsFrom[n]; for (int i = 0; i < n; i++) costsFrom[i] = INT_MAX/4;
    int costsTo[n]; for (int i = 0; i < n; i++) costsTo[i] = INT_MAX/4;
    for (int i = 0; i < n; i++)
        scanf("%d", &tax[i]);
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        int a, b, cost;
        scanf("%d%d%d", &a, &b, &cost);
        a--; b--;
        edges[a].push_back(b);
        costs[a].push_back(cost);
        reverse_edges[b].push_back(a);
        reverse_costs[b].push_back(cost);
    }
    PathQueue Q;
    Q.push(PathNode(gold, 0));
    while (!Q.empty())
    {
        PathNode v = Q.top();
        Q.pop();
        if (!visited[v.node])
        {
            visited[v.node] = true;
            costsFrom[v.node] = v.cost;
            for (int i = 0; i < edges[v.node].size(); i++)
                Q.push(PathNode(edges[v.node][i],
                            v.cost + costs[v.node][i]));
        }
    }
    for (int i = 0; i < n; i++) visited[i] = false;
    Q = PathQueue();
    Q.push(PathNode(gold, 0));
    while (!Q.empty())
    {
        PathNode v = Q.top();
        Q.pop();
        if (!visited[v.node])
        {
            visited[v.node] = true;
            costsTo[v.node] = v.cost;
            for (int i = 0; i < reverse_edges[v.node].size(); i++)
                Q.push(PathNode(reverse_edges[v.node][i],
                            v.cost + reverse_costs[v.node][i]));
        }
    }
    int minCost = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (minCost > (costsTo[i] + costsFrom[i] + tax[i] / 2))
            minCost = costsTo[i] + costsFrom[i] + tax[i] / 2;
    }
    printf("%d\n", minCost);
    return 0;
}
