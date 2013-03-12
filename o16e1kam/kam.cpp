#include <cstdio>

int main()
{
    int z, n, now, before, greatxor;
    scanf("%d", &z);
    while (z--)
    {
        before = greatxor = 0;
        scanf("%d", &n);
        while (n--)
        {
            scanf("%d", &now);
            if (n % 2 == 0)
                greatxor ^= (now - before);
            before = now;
        }
        if (greatxor)
            printf("TAK\n");
        else
            printf("NIE\n");
    }
    return 0;
}
