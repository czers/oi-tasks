#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    int n, score = 0;
    scanf("%d", &n);
    stack<int> notBeingFollowed;
    vector<int> beingSpied[n];
    int spyingWho[n];
    bool onMission[n];
    for (int i = 0; i < n; i++)
    {
        int spying;
        scanf("%d", &spying);
        spying--;
        beingSpied[spying].push_back(i);
        spyingWho[i] = spying;
    }
    for (int i = 0; i < n; i++)
        if (beingSpied[i].size() == 0)
            notBeingFollowed.push(i);
    while (!notBeingFollowed.empty())
    {
        int spy = notBeingFollowed.pop();
        if (!onMission[spyingWho[spy]])
        {
        }
    }
    return 0;
}
