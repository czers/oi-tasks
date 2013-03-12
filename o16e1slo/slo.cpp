#include <cstdio>
#include <climits>
#include <cstdlib>

#define MAXN 1000000

int main()
{
    long long int n, min = INT_MAX;
    long long int w = 0;
    bool odw[MAXN];
    long long int *m, *a, *b, *p, *c, *minC, *s, *cc;
    scanf("%lld", &n);
    m = (long long int *)malloc(n * sizeof(long long int));
    a = (long long int *)malloc(n * sizeof(long long int));
    b = (long long int *)malloc(n * sizeof(long long int));
    p = (long long int *)malloc(n * sizeof(long long int));
    c = (long long int *)malloc(n * sizeof(long long int));
    s = (long long int *)malloc(n * sizeof(long long int));
    cc = (long long int *)malloc(n * sizeof(long long int));
    minC = (long long int *)malloc(n * sizeof(long long int));
    for (int i = 0; i < n; i++)
        scanf("%lld", &m[i]);
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
        scanf("%lld", &b[i]);
    for (int i = 0; i < n; i++)
    {
        a[i]--; b[i]--;
        p[b[i]] = a[i];
        odw[i] = false; 
        s[i] = 0;
        minC[i] = INT_MAX;
        cc[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (odw[i] == false)
        {
            long long int x = i;
            while (odw[x] == false)
            {
                odw[x] = true;
                c[x] = i;
                cc[c[x]]++;
                x = p[x];
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (min > m[i])
            min = m[i];
        s[c[i]] += m[i];
        if (minC[c[i]] > m[i])
            minC[c[i]] = m[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (i == c[i])
        {
            long long int met1 = s[c[i]] + (cc[c[i]] - 2) * minC[c[i]];
            long long int met2 = s[c[i]] +
                    minC[c[i]] + (cc[c[i]] + 1) * min;
            if (met1 < met2)
                w += met1;
            else
                w += met2;
        }
    }
    printf("%lld\n", w);
    return 0;
}
