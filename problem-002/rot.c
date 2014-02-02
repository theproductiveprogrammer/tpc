#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE      65535
#define DISPLAY_SIZE    24
#define TMP_ARR_SIZE    16

void show (int arr[], int n)
{
        int eos, soe;   /* end of start, start of end */
        int i;

    if (n > DISPLAY_SIZE) {
        eos = DISPLAY_SIZE / 2;
        soe = (n - DISPLAY_SIZE - (DISPLAY_SIZE / 2));
    }
    else {
        eos = n;
        soe = 0;
    }

    for (i = 0;i < eos;++i) printf ("|%d", arr[i]);
    printf ("...");
    for (i = soe;i < n;++i) printf ("|%d", arr[i]);
    printf ("\n");
}

void rot (int arr[], int d, int n)
{
        int tmparr[TMP_ARR_SIZE];
        int *tmp = tmparr;

    /* first find out the 'minimum' amount to rotate
     * as multiple rotations will result in the same effect.
     * For example, rotating by 'n' will leave the array unchanged */
    d = d % n;
    if (!d) return;

    /* create temporary area if needed */
    if (d > TMP_ARR_SIZE) tmp = malloc (d);

    /* copy first n elements out */
    memcpy (tmp, arr, d * sizeof (int));
    /* move remaining elements back */
    memmove (arr, arr + d, (n - d) * sizeof (int));
    /* put first n elements back */
    memcpy (arr + (n - d), tmp, d * sizeof (int));

    /* clean up if needed */
    if (tmp != tmparr) free (tmp);
}

int main (int argc, char** argv)
{
        int arr[ARRAY_SIZE];
        int d, n = sizeof(arr) / sizeof (arr[0]);
        int i;

    /* get number of elements to rotate */
    if (argc != 2) return -1;
    d = atoi (argv [1]);

    /* setup */
    for (i = 0;i < n;++i) arr[i] = i;

    /* show and tell */
    printf ("Rotating an array of %d by %d\n", n, d);
    show (arr, n);
    rot (arr, d, n);
    show (arr, n);

    /* done */
    return 0;
}


