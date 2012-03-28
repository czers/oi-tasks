#include <cstdio>

const long long int primes[] = {2,3,5,7,11,13,17,19,23,29};

void traverse(const long long int index, const long long int divisors_count,
        const long long int p, const long long int n,
        long long int &best_antiprime, long long int &best_count)
{
    long long int newp = p, power_count = 0;
    if (p <= n && divisors_count > best_count)
    {
        best_antiprime = p;
        best_count = divisors_count;
    }
    else if (p <= n && divisors_count == best_count && best_antiprime > p)
    {
        best_antiprime = p;
    }
    while (newp < n)
    {
        power_count++;
        newp *= primes[index];
        traverse(index + 1, divisors_count * (power_count+1), newp, n,
                best_antiprime, best_count);
    }
}


int main()
{
    long long int n, best_antiprime = 1, best_count = 1;
    scanf("%lld", &n);
    traverse(0, 1, 1, n, best_antiprime, best_count);
    printf("%lld\n", best_antiprime);
    return 0;
}
