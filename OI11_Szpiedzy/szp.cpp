#include <cstdio>
#include <cstdlib>
#include <stack>

int main()
{
    int n, score = 0;
    std::stack<int> notBeingFollowed;
    scanf("%d", &n);
    int *beingSpied = (int*)malloc(sizeof(int) * n);
    int *spyingWho = (int*)malloc(sizeof(int) * n);
    bool *usedSpy = (bool*)malloc(sizeof(bool) * n);

    for (int i = 0; i < n; i++)
    {
        usedSpy[i] = false;
        beingSpied[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int spying;
        scanf("%d", &spying);
        spying--;
        spyingWho[i] = spying;
        beingSpied[spying]++;
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
