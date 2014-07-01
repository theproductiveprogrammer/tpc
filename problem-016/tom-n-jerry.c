/**
 * Soln:
 *
 * This is a simple problem.
 *
 * The mouse has to reach one of the corners...
 * ```
 *  (Mx, 1), (1, My), (Mx, maxy), (maxx, My)
 * ```
 * before the cats do. Therefore it escapes if
 * the number of steps from any corner is less
 * than the number of steps both cats must take
 * to reach there.
 *
 * The number of steps taken to reach a corner
 * is given by:
 * ```
 * (Mx, 1)
 *  mouse = |0| + |My - 1|
 *  cat = |Cx - Mx| + |Cy - 1|
 * (1, My)
 *  mouse = |Mx - 1| + 0
 *  cat = |Cx - 1| + |Cy - My|
 * (Mx, maxy)
 *  mouse = 0 + |My - maxy|
 *  cat = |Cx - Mx| + |Cy - maxy|
 * (maxx, My)
 *  mouse = |Mx - maxx| + 0
 *  cat = |Cx - maxx| + |Cy - My|
 *  ```
 */
#include <stdio.h>

#define ABSDIFF(a,b) (a < b ? b - a : a - b)

int main () {

        int maxx, maxy;
        int num;
        int mx, my, c1x, c1y, c2x, c2y;
        int m, c;

    scanf ("%d %d\n", &maxx, &maxy);
    scanf ("%d\n", &num);
    while (num--) {
        scanf ("%d %d %d %d %d %d\n",
                &mx, &my, &c1x, &c1y, &c2x, &c2y);

        c = ABSDIFF(c1x,mx) + c1y;
        if (my < c) {
            c = ABSDIFF(c2x,mx) + c2y;
            if (my < c) goto escaped;
        }

        c = c1x + ABSDIFF(c1y,my);
        if (mx < c) {
            c = c2x + ABSDIFF(c2y,my);
            if (mx < c) goto escaped;
        }

        m = ABSDIFF(my,maxy);
        c = ABSDIFF(c1x,mx) + ABSDIFF(c1y,maxy);
        if (m < c) {
            c = ABSDIFF(c2x,mx) + ABSDIFF(c2y,maxy);
            if (m < c) goto escaped;
        }

        m = ABSDIFF(mx, maxx);
        c = ABSDIFF(c1x,maxx) + ABSDIFF(c1y, my);
        if (m < c) {
            c = ABSDIFF(c2x,maxx) + ABSDIFF(c2y, my);
            if (m < c) goto escaped;
        }

        printf ("NO\n");
        continue;
escaped:
        printf ("YES\n");
    }

    return 0;
}

