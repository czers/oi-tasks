#include <cstdio>

class FindUnion
{
    private:
        int rank;
        FindUnion *parent;
    public:
        static void MakeSet(FindUnion &x)
        {
            x.parent = &x;
            x.rank = 0;
        }
        static void Union(FindUnion &x, FindUnion &y)
        {
            FindUnion *xRoot = FindUnion::Find(x);
            FindUnion *yRoot = FindUnion::Find(y);
            if (xRoot == yRoot)
                return;
            if (xRoot->rank < yRoot->rank)
                xRoot->parent = yRoot;
            else if (xRoot->rank > yRoot->rank)
                yRoot->parent = xRoot;
            else
            {
                yRoot->parent = xRoot;
                xRoot->rank += 1;
            }
        }
        static FindUnion* Find(FindUnion &x)
        {
            if (x.parent != &x)
                x.parent = FindUnion::Find(*x.parent);
            return x.parent;
        }
        static int FindIndex(FindUnion &x, FindUnion fu[])
        {
            return FindUnion::Find(x) - fu; 
        }
};

int main()
{
    int n;
    scanf("%d", &n);
    FindUnion fu[n];
    for (int i = 0; i < n; i++)
        FindUnion::MakeSet(fu[i]);
    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        a--;
        FindUnion::Union(fu[i], fu[a]);
    }
    bool setRoot[n];
    for (int i = 0; i < n; i++)
        setRoot[i] = false;
    for (int i = 0; i < n; i++)
        setRoot[FindUnion::FindIndex(fu[i], fu)] = true;
    int count = 0;
    for (int i = 0; i < n; i++)
        if (setRoot[i] == true)
            count++;
    printf("%d\n", count);
    return 0;
}
