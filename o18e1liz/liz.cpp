#include <cstdio>
#include <cstdlib>

const int MAXN = 1000000;
const int T = 2;
const int W = 1;
const int NOTFOUND = -1;

void Remember(int l, int r, int k,
        int intervalL[], int intervalR[], int taste[])
{
    while (k >= 1)
    {
        //printf("Set: %d l: %d(%d) r: %d(%d)\n", k,
        //        l, taste[l], r, taste[r]);
        //fflush(stdout);
        intervalL[k] = l;
        intervalR[k] = r;
        if (taste[l] == T)
            l++;
        else if (taste[r] == T)
            r--;
        else
        {
            l++;
            r--;
        }
        k -= 2;
    }
}

int main()
{
    int n, m, cena = 0, l = NOTFOUND, r = NOTFOUND, k;
    int *taste, *intervalL, *intervalR;
    char c;
    taste = (int*)malloc(sizeof(int) * (MAXN + 1));
    intervalL = (int*)malloc(sizeof(int) * (2 * MAXN + 1));
    intervalR = (int*)malloc(sizeof(int) * (2 * MAXN + 1));
    for (int i = 0; i < (2 * MAXN + 1); i++)
        intervalL[i] = intervalR[i] = NOTFOUND;
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%c", &c);
        if (c == 'T')
            taste[i] = T;
        else
            taste[i] = W;
        cena += taste[i];
    }
    Remember(1, n, cena, intervalL, intervalR, taste);
    for (int i = 1; i <= n; i++)
    {
        if (taste[i] == W)
        {
            if (l == NOTFOUND)
                l = i;
            r = i;
        }
    }
    if (l != NOTFOUND && r < n - l + 1)
        Remember(l + 1, n, cena - 2 * l + 1,
                intervalL, intervalR, taste);
    else if (r != NOTFOUND)
        Remember(1, r - 1, cena - 2 * (n - r) - 1,
                intervalL, intervalR, taste);
    while (m--)
    {
        scanf("%d", &k);
        if (intervalL[k] == NOTFOUND)
            printf("NIE\n");
        else
            printf("%d %d\n", intervalL[k], intervalR[k]);
    }
    return 0;
}
