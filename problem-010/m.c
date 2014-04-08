#include <stdio.h>

#define NUMROWS 1234
#define NUMCOLS 5678

int ROWS[NUMROWS+1];
int COLS[NUMCOLS+1];
int LROWS[NUMROWS+1];
int LCOLS[NUMCOLS+1];

#define V(a,i) (a[(i)]?a[(i)]:(a[(i)]=i))
#define SWAP(a,i1,i2) t=V(a,i1); a[i1]=V(a,i2); a[i2]=t; L##a[a[i1]]=i1;L##a[a[i2]]=i2;

#define gc getchar_unlocked
int read_int() {
        char c = gc();
    while(c<'0') c = gc();
        int ret = 0;
    while(c>='0') {
        ret = 10 * ret + c - '0';
        c = gc();
    }
    return ret;
}

#define pc putchar_unlocked
void put_int (int i)
{
        char op[100];
        int n = 0;
        int t;

    while (i) {
        op[n++] = (i % 10) + '0';
        i = i / 10;
    }

    while (n--) pc (op[n]);
}

int main ()
{
        char cmd;
        int x,y,v,t;

    while ((cmd = gc()) != EOF){
        switch (cmd) {
            case 'R': /*swap row*/
                x = read_int(); y = read_int ();
                SWAP(ROWS,x,y);
                break;
            case 'C': /*swap col*/
                x = read_int(); y = read_int ();
                SWAP(COLS,x,y);
                break;
            case 'Q': /*show val*/
                x = read_int(); y = read_int ();
                put_int ((V(ROWS,x)-1)*NUMCOLS+V(COLS,y));
                pc ('\n');
                break;
            case 'W': /*find val*/
                v = read_int(); v--;
                put_int (V(LROWS, (v / NUMCOLS) + 1));
                pc (' ');
                put_int (V(LCOLS, (v % NUMCOLS) + 1));
                pc ('\n');
                break;
        }
    }
    return 0;
}
