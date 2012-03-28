#include <cstdio>
#include <vector>
#include <queue>

const int maxNodeCount = 100000;
const int VISITED_FROM_NOONE = -1;

using namespace std;

void setBoolArray(bool array[], int size, bool value)
{
    for (int i = 0; i < size; i++)
        array[i] = value;
}

void setIntArray(int array[], int size, int value)
{
    for (int i = 0; i < size; i++)
        array[i] = value;
}

int main()
{
    int nodeCount, edgeCount;
    bool visited[maxNodeCount];
    vector<int> graph[maxNodeCount];
    vector<int> cycleLeaders;
    vector<int> cycleLeadersNeighbours;
    queue<int> dfsQueue;
    int visitedFrom[maxNodeCount];
    setBoolArray(visited, maxNodeCount, false);
    setIntArray(visitedFrom, maxNodeCount, VISITED_FROM_NOONE);
    scanf("%d%d", &nodeCount, &edgeCount);
    while (edgeCount--)
    {
        int edgeStart, edgeEnd;
        scanf("%d%d", &edgeStart, &edgeEnd);
        edgeStart--; edgeEnd--;
        graph[edgeStart].push_back(edgeEnd);
        graph[edgeEnd].push_back(edgeStart);
    }
    for (int i = 0; i < nodeCount; i++)
    {
        unsigned int cycleNo = cycleLeaders.size();
        if (!visited[i])
        {
            dfsQueue.push(i);
            visited[i] = true;
        }
        while (!dfsQueue.empty())
        {
            int currentNode = dfsQueue.front();
            dfsQueue.pop();
            for (unsigned int k = 0; k < graph[currentNode].size(); k++)
            {
                int neighbourNode = graph[currentNode][k];
                if (visited[neighbourNode] &&
                        visitedFrom[currentNode] != neighbourNode &&
                        cycleNo == cycleLeaders.size())
                {
                    cycleLeaders.push_back(currentNode);
                    cycleLeadersNeighbours.push_back(neighbourNode);
                }
                else if (!visited[neighbourNode])
                {
                    visited[neighbourNode] = true;
                    visitedFrom[neighbourNode] = currentNode;
                    dfsQueue.push(neighbourNode);
                }
            }
        }
    }
    setBoolArray(visited, maxNodeCount, false);
    setIntArray(visitedFrom, maxNodeCount, VISITED_FROM_NOONE);
    for (unsigned int i = 0; i < cycleLeaders.size(); i++)
    {
        int leaderNode = cycleLeaders[i];
        dfsQueue.push(leaderNode);
        visited[leaderNode] = true;
        visitedFrom[leaderNode] = cycleLeadersNeighbours[i];
        while (!dfsQueue.empty())
        {
            int currentNode = dfsQueue.front();
            dfsQueue.pop();
            for (unsigned int k = 0; k < graph[currentNode].size(); k++)
            {
                int neighbourNode = graph[currentNode][k];
                if (!visited[neighbourNode] &&
                        (currentNode != leaderNode || neighbourNode !=
                         visitedFrom[leaderNode]))
                {
                    visited[neighbourNode] = true;
                    visitedFrom[neighbourNode] = currentNode;
                    dfsQueue.push(neighbourNode);
                }
            }
        }
    }
    bool isSetupCorrect = true;
    for (int i = 0; i < nodeCount; i++)
        if (visitedFrom[i] == VISITED_FROM_NOONE)
            isSetupCorrect = false;
    if (isSetupCorrect)
    {
        printf("TAK\n");
        for  (int i = 0; i < nodeCount; i++)
            printf("%d\n", visitedFrom[i] + 1);
    }
    else
        printf("NIE\n");
    return 0;
}
