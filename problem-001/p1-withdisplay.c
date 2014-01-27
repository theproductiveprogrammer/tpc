
/* this is the key array of valid denominations.
 * NB: this should be in ascending order and unique */
int DENOMINATIONS[] = { 1, 2, 5, 10, 20, 50, 100 };
int DC = sizeof (DENOMINATIONS)/sizeof (DENOMINATIONS[0]);  /* count */

/* display the results for debugging
 * NB: the 128 is to allow space for experimentation with DENOMINATIONS */
int DIVISOR[128];

int showhelp (char** argv)
{
    printf ("Find the number of ways to make change for a given amount\n");
    printf ("%s <number>\n", argv [0]);
    return 1;
}

void showcount ()
{
        int i, t;

    printf ("[ ");
    for (i = 0, t = 0; i < DC; ++i) {
        t += DENOMINATIONS [i] * DIVISOR [i];
        printf ("$%dx%-3d  ", DENOMINATIONS[i], DIVISOR[i]);
    }
    printf ("] = %d\n", t);
}

int make_change (int amount, int* denominations, int cur_denom)
{
        int d, r, c = 0;

    /* reached the terminal */
    if (amount == 0) showcount ();
    if (amount == 0) return 1;
    if (cur_denom < 0) return 0;

    /* find divisor */
    d = amount / denominations [cur_denom];
    /* and remainder */
    r = amount - (d * denominations [cur_denom]);

    /* loop over number of divisors
     * == number of change of this  denomination */
    for (;d >= 0;d--) {
        /* save current divisor */
        DIVISOR[cur_denom] = d;
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

