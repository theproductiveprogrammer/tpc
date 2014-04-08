#include <stdio.h>

#define NUMROWS 1234
#define NUMCOLS 5678

short ROWS[NUMROWS+1];
short COLS[NUMCOLS+1];
short LROWS[NUMROWS+1];
short LCOLS[NUMCOLS+1];

#define V(a,i) (a[(i)]?a[(i)]:i)
#define SWAP(a,i1,i2) { int t=V(a,i1); a[i1] = V(a,i2); a[i2] = t; L##a[a[i1]]=i1;L##a[a[i2]]=i2;}

int main ()
{
        char cmd;
        int x,y,v;

    while (scanf("%c", &cmd)>0) {
        switch (cmd) {
            case 'R': /*swap row*/
                scanf("%d %d", &x, &y);
                SWAP(ROWS,x,y);
                break;
            case 'C': /*swap col*/
                scanf("%d %d", &x, &y);
                SWAP(COLS,x,y);
                break;
            case 'Q': /*show val*/
                scanf("%d %d", &x, &y);
                printf ("%d\n",(V(ROWS,x)-1)*NUMCOLS+V(COLS,y));
                break;
            case 'W': /*find val*/
                scanf("%d", &v); v--;
                printf ("%d %d\n", V(LROWS, (v / NUMCOLS) + 1),
                                   V(LCOLS, (v % NUMCOLS) + 1)
                       );
                break;
        }
    }
    return 0;
}
