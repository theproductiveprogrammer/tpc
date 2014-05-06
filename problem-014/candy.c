#include <stdio.h>
#include <stdlib.h>

int cmpf (const void *p1, const void* p2)
{
    return (*(int*)p1) - (*(int*)p2);
}

int main ()
{
        int d = 0;
        int n, i, kc[200];
        int l, h;

    scanf ("%d", &n);
    for (i = 0;i < n;++i) scanf ("%d %d", kc+(2*i),kc+(2*i+1));

    qsort (kc, i, sizeof (int)*2, cmpf);

    l = 0; h = n - 1;
    while (l <= h) {
        if (d == 0) {
            if (kc[2*h] & 1) d = kc[2*h+1];
            h--;
        }
        else {
            n = d / (kc[2*l+1]);
            if (n < kc[2*l]) {
                kc[2*l] -= n;
            }
            else {
                n = kc[2*l];
                l++;
            }
            if (d > 0) d -= n * kc[2*l+1];
            else d += n * kc[2*l+1];
        }
    }

    printf ("%d\n", d);

    return 0;
}

