#include <stdint.h>
#include <cstdio>
#include <limits>
#include <vector>
#include <set>
#include <utility>

const int kMaxN = 200;
const int kMaxP = 13;
const int kMaxM = 3000;
const int kMaxSwordMask = 8192;

void PrintSwords(int16_t swords) {
    for (int i = 0; i < 16; i++) {
        if (swords & (1 << i))
            printf("1");
        else
            printf("0");
    }
    printf("[%d]", swords);
}

int16_t add_sword(int16_t swords, int sword) {
    return swords | (1 << sword);
}

int16_t sum_swords(int16_t first, int16_t second) {
    return first | second;
}

int16_t add_monster(int16_t monsters, int monster) {
    return monsters | (1 << monster);
}

bool can_defeat(int16_t monsters, int16_t swords) {
//    printf("CD: "); PrintSwords(monsters & (~swords)); printf("\n");
    return (monsters & (~swords)) == 0;
}

typedef std::pair<int, int16_t> DijkstraNode;

int min_costs[kMaxN][kMaxSwordMask];

struct DijkstraCompare {
    bool operator()(const DijkstraNode &a, const DijkstraNode &b) {
        if (min_costs[a.first][a.second] != min_costs[b.first][b.second])
            return min_costs[a.first][a.second] < min_costs[b.first][b.second];
        if (a.first != b.first)
            return a.first < b.first;
        if (a.second != b.second)
            return a.second < b.second;
    }
};

typedef std::set<DijkstraNode, DijkstraCompare> Dijkstra;

int main() {
    for (int i = 0; i < kMaxN; i++)
        for (int j = 0; j < kMaxSwordMask; j++)
            min_costs[i][j] = std::numeric_limits<int>::max() / 2;
    int n, m, p, k;
    scanf("%d%d%d%d", &n, &m, &p, &k);
    int16_t smiths[kMaxN];
    for (int i = 0; i < k; i++) {
        int w, q;
        scanf("%d%d", &w, &q); 
        w--;
        while (q--) {
            int r;
            scanf("%d", &r);
            r--;
            smiths[w] = add_sword(smiths[w], r);
        }
    }
    std::vector<int> edges[kMaxN];
    std::vector<int> costs[kMaxN];
    std::vector<int16_t> monsters[kMaxN];
    for (int i = 0; i < m; i++) {
        int v, w, t, s;
        scanf("%d%d%d%d", &v, &w, &t, &s);
        v--;
        w--;
        edges[v].push_back(w);
        edges[w].push_back(v);
        costs[v].push_back(t);
        costs[w].push_back(t);
        int16_t road_monsters = 0;
        while (s--) {
            int u;
            scanf("%d", &u);
            u--;
            road_monsters = add_monster(road_monsters, u);
        }
        monsters[v].push_back(road_monsters);
        monsters[w].push_back(road_monsters);
    }
    Dijkstra Dij;
    min_costs[0][0] = 0;
    Dij.insert(std::make_pair<int, int16_t>(0, 0));
    bool goal_reached;
    //bool visited[kMaxN];
    int best_cost = std::numeric_limits<int>::max();
    while (!Dij.empty() && !goal_reached) {
        std::pair<int, int16_t> v = *Dij.begin();
        Dij.erase(Dij.begin());
//        visited[v.first] = true;
//        printf("VISIT: %d c: %d swds: ", v.first, min_costs[v.first][v.second]); PrintSwords(v.second); printf("\n");
        if (v.first == n - 1) {
            goal_reached = true;
            best_cost = min_costs[v.first][v.second];
        }
        int edges_count = edges[v.first].size();
        for (int i = 0; i < edges_count; i++) {
            int new_cost = min_costs[v.first][v.second] + costs[v.first][i];
            int16_t new_swords = sum_swords(v.second, smiths[v.first]);
            int destination = edges[v.first][i];
 //           printf(" MAYBE: %d ocost: %d ncost: %d nswds: ", destination, min_costs[destination][new_swords], new_cost); PrintSwords(new_swords); printf(" mon: "); PrintSwords(monsters[v.first][i]); 
            if (//!visited[destination] &&
                    new_cost < min_costs[destination][new_swords] &&
                    can_defeat(monsters[v.first][i], new_swords)) {
                std::pair<int, int16_t> next_node =
                    std::make_pair(destination, new_swords);
                Dij.erase(next_node);
                min_costs[destination][new_swords] = new_cost;
                Dij.insert(next_node);
//                printf(" UPDATED"); 
            }
//            printf("\n");
        }
    }
    if (best_cost == std::numeric_limits<int>::max())
        printf("-1\n");
    else
        printf("%d\n", best_cost);
    return 0;
}
