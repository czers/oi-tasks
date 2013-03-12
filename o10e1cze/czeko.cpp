#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    m--; n--;
    int xs[m], ys[n];
    for (int i = 0; i < m; i++)
        scanf("%d", &xs[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &ys[i]);
    sort(xs, xs + m);
    sort(ys, ys + n);
    int x_index = m - 1, y_index = n - 1, sum = 0;
    while (x_index >= 0 || y_index >= 0)
    {
        if (x_index >= 0 && y_index >= 0)
        {
            if (xs[x_index] > ys[y_index])
            {
                sum += xs[x_index] * (n - y_index);
                x_index--;
            }
            else
            {
                sum += ys[y_index] * (m - x_index);
                y_index--;
            }
        }
        else if (x_index >= 0)
        {
                sum += xs[x_index] * (n - y_index);
                x_index--;
        }
        else
        {
                sum += ys[y_index] * (m - x_index);
                y_index--;
        }
    }
    printf("%d\n", sum);
    return 0;
}
