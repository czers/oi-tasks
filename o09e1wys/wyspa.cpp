#include <cstdio>

int main()
{
    int n;
    scanf("%d", &n);
    int dist[n], circumference = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &dist[i]);
        circumference += dist[i];
    }
    int fromIndex = 0, toIndex = 0;
    int bestDistance = 0, currentDistance = 0;
    while (fromIndex != n - 1)
    {
        if (currentDistance * 2 < circumference)
        {
            currentDistance += dist[toIndex];
            toIndex = (toIndex + 1) % n;
        }
        else
        {
            currentDistance -= dist[fromIndex];
            fromIndex++;
        }
        if (currentDistance > bestDistance &&
                currentDistance * 2 <= circumference)
            bestDistance = currentDistance;
    }
    printf("%d\n", bestDistance);
    return 0;
}
