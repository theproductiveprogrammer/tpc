
/* this is the key array of valid denominations.
 * NB: this should be in ascending order and unique 
 * Note also that we have optimized away the 1 case */
int DENOMINATIONS[] = { 2, 5, 10, 20, 50, 100 };
int DC = sizeof (DENOMINATIONS)/sizeof (DENOMINATIONS[0]);  /* count */

int showhelp (char** argv)
{
    printf ("Find the number of ways to make change for a given amount\n");
    printf ("%s <number>\n", argv [0]);
    return 1;
}

int make_change (int amount, int* denominations, int cur_denom)
{
        int d, r, c = 0;

    /* reached the terminal */
    if (!cur_denom) return ((amount / denominations[0]) + 1);

    /* find divisor */
    d = amount / denominations [cur_denom];
    /* and remainder */
    r = amount - (d * denominations [cur_denom]);

    /* loop over number of divisors
     * == number of change of this  denomination */
    for (;d >= 0;d--) {
        /* find change for the current remainder
         * with the remaining denominations */
        c += make_change (r, denominations, cur_denom - 1);
        /* remove one note of this denomination */
        r += denominations [cur_denom];
    }

    /* return the total count of denominations found */
    return c;
}

int main (int argc, char** argv)
{
        int n;

    /* give help if we don't get correct inputs */
    if (argc != 2) return showhelp (argv);

    /* convert given argument to number or fail */
    n = atoi (argv [1]);
    if (!n) return showhelp (argv);

    printf ("There are %d ways to make change for %d\n",
            make_change (n, DENOMINATIONS, DC - 1), n);

    /* done */
     return 0;
}

