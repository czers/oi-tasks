#include <cstdio>
#include <limits>
#include <set>
#include <algorithm>

const int kMaxN = 5000;
const int kMaxA = 50000;

int min_costs[kMaxA];

struct NodeCompare {
    bool operator()(const int &a, const int &b) {
        if (min_costs[a] != min_costs[b])
            return (min_costs[a] < min_costs[b]);
        return a < b;
    }
};

typedef std::set<int, NodeCompare> DijkstraSet;

int main() {
    int n;
    int a[kMaxN];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    const int min_a = a[0];
    // Initialize minimal costs
    for (int i = 0; i < min_a; i++)
        min_costs[i] = std::numeric_limits<int>::max();
    min_costs[0] = 0;
    // Find optimal edges
    int edges[kMaxA];
    for (int i = 0; i < min_a; i++)
        edges[i] = std::numeric_limits<int>::max();
    for (int i = 0; i < n; i++) {
        const int mod_a = a[i] % min_a;
        edges[mod_a] = std::min(edges[mod_a], a[i]);
    }
    edges[0] = std::numeric_limits<int>::max();
    std::sort(edges, edges + min_a);
    const int edges_count = std::lower_bound(edges, edges + min_a,
            std::numeric_limits<int>::max()) - edges;
    // Init visited info for Dijkstra algorithm
    bool visited[kMaxA];
    for (int i = 0; i < min_a; i++)
        visited[i] = false;
    // Run Dijkstra
    DijkstraSet S;
    S.insert(0);
    while (!S.empty()) {
        const int v = *S.begin();
        S.erase(S.begin());
        visited[v] = true;
        for (int i = 0; i < edges_count; i++) {
            const int jump = (v + edges[i]) % min_a;
            if (!visited[jump]) {
                const int new_cost = min_costs[v] + edges[i];
                if (new_cost < min_costs[jump]) {
                    S.erase(jump);
                    min_costs[jump] = new_cost;
                    S.insert(jump);
                }
            }
        }
    }
    // Print results
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
