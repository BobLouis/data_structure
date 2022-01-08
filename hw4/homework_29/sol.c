
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/*
M = 100000
N = 10000
U = 10000
*/
typedef struct bitmap
{
    int *bits, range;
} Bitmap;

int BFilterExist(Bitmap *tmp, char *str);
void BFilterSet(Bitmap *tmp, char *str);
int tmpapExist(Bitmap *tmp, int x);
void tmpapSet(Bitmap *tmp, int x);
int hash(char *key, int len, int seed);
Bitmap *tmpapInit(int range);

int _h;

int main()
{
    int n, m;
    scanf("%d%d%d", &n, &m, &_h);
    char *str = (char *)malloc(sizeof(char) * 100);
    Bitmap *tmp = tmpapInit(m);
    for (int i = 1; i <= n; i++)
        scanf("%s", str), BFilterSet(tmp, str);
    for (int i = 1; i <= n; i++)
        scanf("%s", str), printf("%d\n", BFilterExist(tmp, str));
}

Bitmap *tmpapInit(int range)
{
    Bitmap *tmp = (Bitmap *)malloc(sizeof(Bitmap));
    tmp->bits = (int *)malloc(sizeof(int) * range + 1);
    tmp->range = range;
    memset(tmp->bits, 0, sizeof(tmp->range));
    return tmp;
}

int hash(char *key, int len, int seed)
{
    const int m = 0x1b873593;
    const int r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t *data = (const uint64_t *)key;
    const uint64_t *end = data + (len / 8);

    while (data != end)
    {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const uint8_t *data2 = (const uint8_t *)data;

    switch (len & 7)
    {
    case 7:
        h ^= ((uint64_t)data2[6]) << 48;
    case 6:
        h ^= ((uint64_t)data2[5]) << 40;
    case 5:
        h ^= ((uint64_t)data2[4]) << 32;
    case 4:
        h ^= ((uint64_t)data2[3]) << 24;
    case 3:
        h ^= ((uint64_t)data2[2]) << 16;
    case 2:
        h ^= ((uint64_t)data2[1]) << 8;
    case 1:
        h ^= ((uint64_t)data2[0]);
        h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h % 2147483647;
}

void tmpapSet(Bitmap *tmp, int x)
{
    tmp->bits[(x % tmp->range)] |= (1 << (x % 32));
}

int tmpapExist(Bitmap *tmp, int x)
{
    return (tmp->bits[(x % tmp->range)] & (1 << (x % 32))) != 0;
}

void BFilterSet(Bitmap *tmp, char *str)
{
    for (int i = 1; i <= _h; i++)
    {
        tmpapSet(tmp, (hash(str, strlen(str), 1 << i)));
    }
}

int BFilterExist(Bitmap *tmp, char *str)
{
    for (int i = 1; i <= _h; i++)
    {
        if (!tmpapExist(tmp, (hash(str, strlen(str), 1 << i))))
            return 0;
    }
    return 1;
}
