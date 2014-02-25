#include <stdio.h>
#include <stdint.h>

int primes[] = {2,3,5,7,11};

int main ()
{
        int n, i, j;
        union {
           double d;
           char s[sizeof(double)];
        } a;

    scanf ("%d", &n);
    while (n--) {
        a.d = 0;
        scanf ("%s", a.s);
        for (i = 1;;) {
            a.d *= primes[1]; if ((i>480) && (floor (a.d) - a.d == 0.0)) break;++i;
            a.d *= primes[2]; if ((i>480) && (floor (a.d) - a.d == 0.0)) break;++i;
            a.d *= primes[3]; if ((i>480) && (floor (a.d) - a.d == 0.0)) break;++i;
            a.d *= primes[4]; if ((i>480) && (floor (a.d) - a.d == 0.0)) break;++i;
            a.d *= primes[0]; if ((i>480) && (floor (a.d) - a.d == 0.0)) break;++i;
        }
        printf ("%lf %d\n", a.d, i);
    }
    return 0;
}

