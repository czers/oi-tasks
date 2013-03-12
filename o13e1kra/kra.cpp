#include <cstdio>

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int tube[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &tube[i]);
    int radius = tube[0];
    for (int i = 1; i < n; i++)
    {
        if (tube[i] > radius)
            tube[i] = radius;
        else
            radius = tube[i];
    }
    int i = n - 1;
    while (i >= 0 && m--)
    {
        int d;
        scanf("%d", &d);
        while (tube[i] < d && i >= 0)
            i--;
        i--;
    }
    if (m > 0)
        printf("0\n");
    else
        printf("%d\n", i + 2);
    return 0;
}
