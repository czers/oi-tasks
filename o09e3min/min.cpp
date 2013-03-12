#include <cstdio>

int main()
{
    int n;
    scanf("%d\n", &n);
    n--;
    bool minus[n];
    for (int i = 0; i < n; i++)
    {
        char c;
        scanf("%c\n", &c);
        if (c == '-')
            minus[i] = true;
        else
            minus[i] = false;
    }
    bool isOpen = false;
    for (int i = 0; i < n; i++)
    {
        if (minus[i] == true && isOpen == false)
            printf("-");
        else if (minus[i] == true && isOpen == true)
        {
            printf(")-");
            isOpen = false;
        }
        else if (minus[i] == false && isOpen == false)
        {
            printf("(-");
            isOpen = true;
        }
        else
            printf("-");
    }
    if (isOpen == true)
        printf(")");
    printf("\n");
    return 0;
}
