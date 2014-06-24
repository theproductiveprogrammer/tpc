/**
 * Query on a tree
 *
 * Steps to solve
 * 1. Create an array of NxN (all node to node edges)
 * 2. Fill edges in NxN from input (mirror (a,b) and (b,a))
 * 3. Store edge to edge number mapping (for CHANGE operation)
 * 4. Resolve each node paths
 *    1. Resolve each child
 *    2. For each child, find all reach-able paths
 *       and save child (-gative index) as our path to those reachable paths
 * 5. On CHANGE
 *    1. Find edge to edge mapping from store
 *    2. Update edge on both mirrors
 * 6. On QUERY
 *    1. Set Sum to 0
 *    2. Start on node a
 *    3. While node is not b
 *       1. Find current node path to b
 *       2. if (-gative), use as child index
 *          1. Add value at child index to running sum
 *          2. set current node to child
 *       3. Otherwise add to sum and return sum
 * 7. On DONE
 *    1. End
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tree[10001][10001];
int edge_a[10001];
int edge_b[10001];
int resolved[10001];

void resolve_node (int n, int nn) {
    int i, j;

    if (resolved[n] == 1) return;

    for (i = 0;i < nn;++i) {
        if (tree[n][i]) {
            resolve_node (i, nn);
            for (j = 0;j < nn;++j) {
                if (j!=n && tree[i][j]) tree[n][j] = -i;
            }
        }
    }

    resolved[n] = 1;
}

void print_path_max (int a, int b) {
    int max = 0;
    int p;

    while (1) {
        p = tree[a][b];
        if (p < 0) {
            if (max < tree[a][-p]) max = tree[a][-p];
            a = -p;
        }
        else {
            if (max < p) max = p;
            printf ("%d\n", max);
            return;
        }
    }
}

void dump (int nn) {
    int i, j;
    printf ("--dump\n");
    for (i = 0;i < nn;++i) {
        for (j = 0;j < nn;++j) {
            printf ("%d ", tree[i][j]);
        }
        printf ("\n");
    }
    printf ("--\n");
}

int main () {
    int ntc, nn, a, b, ec;
    int i, ndx;
    char cmd[64];
    int done;

    // number of test cases
    scanf ("%d", &ntc);
    while (ntc--) {

        // number of nodes
        scanf ("%d", &nn);
        // clear memory
        memset (resolved, 0, nn);
        for (i = 0;i < nn - 1;++i) {
            scanf ("%d %d %d", &a, &b, &ec);
            if (!resolved[a]) memset (tree[a], 0, sizeof(tree[0]));
            if (!resolved[b]) memset (tree[b], 0, sizeof(tree[0]));
            resolved[a] = resolved[b] = -1;
            tree[a][b] = ec;
            edge_a[i] = a;
            edge_b[i] = b;
        }
        // resolve all tree paths
        for (i = 0;i < nn;++i) {
            resolve_node (i, nn);
        }
        // update back links
        for (i = 0;i < nn;++i) tree[edge_b[i]][edge_a[i]] = tree[edge_a[i]][edge_b[i]];
        // user queries
        done = 0;
        while (!done) {
            scanf ("%s", cmd);
            switch (*cmd) {
                case 'C':
                    scanf ("%d %d", &ndx, &ec);
                    ndx--;
                    tree[edge_a[ndx]][edge_b[ndx]] =
                    tree[edge_b[ndx]][edge_a[ndx]] = ec;
                    break;
                case 'Q':
                    scanf ("%d %d", &a, &b);
                    print_path_max (a, b);
                    break;
                default:
                    done = 1;
            }
        }
    }

    return 0;
}

