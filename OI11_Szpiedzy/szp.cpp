#include <cstdio>
#include <cstdlib>
#include <stack>

const int MAXN = 1000001;

int main()
{
    int n, score = 0;
    int *beingSpied = (int*)malloc(sizeof(int) * MAXN);
    int *spyingWho = (int*)malloc(sizeof(int) * MAXN);
    bool *usedSpy = (bool*)malloc(sizeof(bool) * MAXN);
    for (int i = 0; i < MAXN; i++)
        usedSpy[i] = false;
    scanf("%d", &n);
    std::stack<int> notBeingFollowed;
    for (int i = 0; i < n; i++)
    {
        int spying;
        scanf("%d", &spying);
        spying--;
        beingSpied[spying]++;
        spyingWho[i] = spying;
    }
    for (int i = 0; i < n; i++)
        if (beingSpied[i] == 0)
            notBeingFollowed.push(i);
    while (!notBeingFollowed.empty())
    {
        int spy = notBeingFollowed.top();
        notBeingFollowed.pop();
        int targetSpy = spyingWho[spy];
        if (!usedSpy[spy] && !usedSpy[targetSpy])
        {
            score++;
            usedSpy[targetSpy] = true;
            int targetTargetSpy = spyingWho[targetSpy];
            beingSpied[targetTargetSpy]--;
            if (beingSpied[targetTargetSpy] == 0)
                notBeingFollowed.push(targetTargetSpy);
        }
        usedSpy[spy] = true;
    }
    for (int i = 0; i < n; i++)
    {
        if (!usedSpy[i])
        {
            int start = i, len = 1, current = spyingWho[i];
            usedSpy[i] = true;
            while (current != start && !usedSpy[current])
            {
                len++;
                usedSpy[current] = true;
                current = spyingWho[current];
            }
            score += len / 2;
        }
    }
    printf("%d\n", score);
    return 0;
}
