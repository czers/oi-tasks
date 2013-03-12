#include <cstdio>
#include <deque>
#include <climits>
#include <stack>
#include <cstdlib>

using namespace std;

#define IND(n,i,j) ((n)*(j)+(i))

int main()
{
    int n, k;
    scanf("%d", &n);
    int b[n], c[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &c[i]);
    scanf("%d", &k);
    deque<int> Q;
    int R[k+1], M[k+1];
    int *W = (int*)malloc(sizeof(int) * n * (k + 1));
    R[0] = 0;
    for (int i = 1; i <= k; i++)
        R[i] = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        for (int r = 0; r < b[i]; r++)
        {
            Q.clear();
            int l = 0;
            while (r + l * b[i] <= k)
            {
                int amount = r + l * b[i];
                M[l] = R[amount] - l;
                while (!Q.empty() && M[Q.back()] >= M[l])
                    Q.pop_back();
                Q.push_back(l);
                R[amount] = M[Q.front()] + l;
                W[IND(n, i, amount)] = l - Q.front();
                if (Q.front() == l - c[i])
                    Q.pop_front();
                l++;
            }
        }
    }
    int j = k, billCount = 0;
    stack<int> S;
    for (int i = n - 1; i >= 0; i--)
    {
        billCount += W[IND(n, i, j)];
        S.push(W[IND(n, i, j)]);
        j -= W[IND(n, i, j)] * b[i];
    }
    printf("%d\n", billCount);
    while (!S.empty())
    {
        printf("%d ", S.top());
        S.pop();
    }
    printf("\n");
    return 0;
}
