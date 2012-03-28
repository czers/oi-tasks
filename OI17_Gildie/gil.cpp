#include <cstdio>

#define MAXN 200000

const int N = 1;
const int S = 2;
const int K = 3;

void SetReverse(int *a, int *b)
{
    if (*a == N)
    {
        if (*b == S)
            *a = K;
        else
            *a = S;
    }
}

int main()
{
    int n, m;
    int guild[MAXN];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        guild[i] = N;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        SetReverse(&guild[a], &guild[b]); 
        SetReverse(&guild[b], &guild[a]); 
    }
    for (int i = 0; i < n; i++)
    {
        if (guild[i] == N)
        {
            printf("NIE\n");
            return 0;
        }
    }
    printf("TAK\n");
    for (int i = 0; i < n; i++)
    {
        if (guild[i] == S)
            printf("S\n");
        else
            printf("K\n");
    }
    return 0;
}
