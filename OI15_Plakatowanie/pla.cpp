#include <cstdio>
#include <stack>

using namespace std;

int main()
{
    int n, w, s, p = 0;
    stack<int> S;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &s, &w);
        while (!S.empty() && S.top() > w)
            S.pop();
        if (S.empty() || S.top() < w)
        {
            S.push(w);
            p++;
        }
    }
    printf("%d\n", p);
    return 0;
}
