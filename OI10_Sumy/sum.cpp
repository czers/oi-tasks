#include <cstdio>
#include <queue>
#include <vector>
#include <limits>

const int MAXN = 5000;

class GraphNode
{
    public:
        int node;
        int cost;
        GraphNode(int node, int cost)
        {
            this->node = node;
            this->cost = cost;
        }
};

struct GraphNodeCompare {
    bool operator()(const GraphNode &a, const GraphNode &b)
    {
        if (a.cost != b.cost)
            return (a.cost > b.cost);
        return a.node > b.node;
    }
};

typedef std::priority_queue<GraphNode, std::vector<GraphNode>,
        GraphNodeCompare> DijkstraQueue;

int main() {
    int n;
    int a[MAXN];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    const int min_a = a[0];
    bool used_modulo[min_a];
    std::vector<int> edges[min_a];
    std::vector<int> costs[min_a];
    for (int i = 0; i < n; i++) {
        const int mod_a = a[i] % min_a;
        if (!used_modulo[mod_a]) {
            used_modulo[mod_a] = true;
            for (int j = 0; j < min_a; j++) {
                const int modulo_jump = (j + a[i]) % min_a;
                edges[j].push_back(modulo_jump);
                costs[j].push_back(a[i]);
            }
        }
    }
    DijkstraQueue Q;
    bool visited[min_a];
    int min_costs[min_a];
    for (int i = 0; i < min_a; i++)
        min_costs[i] = std::numeric_limits<int>::max();
    Q.push(GraphNode(0, 0));
    while (!Q.empty()) {
        GraphNode v = Q.top();
        printf("POP: %d c: %d\n", v.node, v.cost);
        Q.pop();
        if (!visited[v.node]) {
            visited[v.node] = true;
            min_costs[v.node] = v.cost;
            for (int i = 0; i < edges[v.node].size(); i++) {
                if (!visited[edges[v.node][i]])
                {
                    Q.push(GraphNode(edges[v.node][i],
                                     v.cost + costs[v.node][i]));
                    printf("PUSH: %d c: %d\n", edges[v.node][i],
                            v.cost + costs[v.node][i]);
                }
            }
        }
    }
    int k;
    scanf("%d", &k);
    while (k--) {
        int b;
        scanf("%d", &b);
        const int mod_a = b % min_a;
        if (min_costs[mod_a] <= b)
            printf("TAK\n");
        else
            printf("NIE\n");
    }
    return 0;
}
