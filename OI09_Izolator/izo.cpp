#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    int isolation[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &isolation[i]);
    sort(isolation, isolation + n);
    int sum = 0;
    for (int i = n / 2; i < n; i++)
        sum += 2 * isolation[i];
    if (n % 2)
        sum -= isolation[n/2];
    printf("%d\n", sum);
    return 0;
}
