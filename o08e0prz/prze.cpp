#include <cstdio>
#include <utility>
#include <queue>

using namespace std;

typedef pair<int, char> point_t;
typedef priority_queue<point_t> axis_t;
const int start_value = 1;
const int end_value = 0;

int main()
{
    axis_t Q;
    int n, open_intervals = 0;
    scanf("%d", &n);
    while (n--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        // Negative values to use default priority queue ordering
        point_t start = point_t(-a, start_value);
        point_t end = point_t(-b, end_value);
        Q.push(start);
        Q.push(end);
    }
    while (!Q.empty())
    {
        point_t current = Q.top();
        Q.pop();
        if (current.second == start_value)
        {
            open_intervals++;
            if (open_intervals == 1)
                printf("%d ", -current.first);
        }
        else
        {
            open_intervals--;
            if (open_intervals == 0)
                printf("%d\n", -current.first);
        }
    }
    return 0;
}
