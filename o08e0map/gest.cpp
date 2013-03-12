#include <cstdio>

int* Fget(int *F, int i, int j, int n)
{
    return (F + i * n + j);
}

int Fvalue(int *F, int i, int j, int n)
{
    if (i >= n) i = n - 1;
    if (j >= n) j = n - 1;
    if (i < 0 || j < 0)
        return 0;
    else
        return *Fget(F, i, j, n);
}

void Fprint(int *F, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", *Fget(F, i, j, n));
        printf("\n");
    }
}

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    int F[n][n], W[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", Fget((int *)F, i, j, n));
    //Fprint((int *)F, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            *Fget((int *)F, i, j, n) =
                    Fvalue((int *)F, i, j, n)
                    + Fvalue((int *)F, i-1, j, n)
                    + Fvalue((int *)F, i, j-1, n)
                    - Fvalue((int *)F, i-1, j-1, n);
    //Fprint((int *)F, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            *Fget((int *)W, i, j, n) =
                    Fvalue((int *)F, i+r, j+r, n)
                    - Fvalue((int *)F, i-r-1, j+r, n)
                    - Fvalue((int *)F, i+r, j-r-1, n)
                    + Fvalue((int *)F, i-r-1, j-r-1, n);
    Fprint((int *)W, n);
    return 0;
}
