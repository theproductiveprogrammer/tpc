#include <stdio.h>

#define MAX_FSZ (1 * 1024 * 1024)
#define MAX_DEPTH (1 * 1024 * 1024)

int main (int argc, char* argv[])
{
        int dump;
        char *inputf, *patf;
        FILE *finp, *fpat;
        char buf_i[MAX_FSZ+1], buf_p[MAX_FSZ+1];
        long sz_i, sz_p, ndx_i, ndx_p;
        char *p_i, *p_p;
        int num = 0;
        int pt_limit, pt_i, pt[MAX_DEPTH];

    if (!strcmp (argv[1], "-d")) {
        dump = 1;
        inputf = argv[2];
        patf = argv[3];
    }
    else {
        dump = 0;
        inputf = argv[1];
        patf = argv[2];
    }

    /* read in pattern file */
    fpat = fopen (patf, "rb");
    sz_p = fread (buf_p, sizeof (char), MAX_FSZ, fpat);
    buf_p[sz_p] = 0;
    /* and split into lines */
    for (p_p=buf_p;*p_p;p_p++) if (*p_p == '\n' || *p_p == '\r') *p_p = 0;

    /* read in input file */
    finp = fopen (inputf, "rb");
    sz_i = fread (buf_i, sizeof (char), MAX_FSZ, finp);
    buf_i[sz_i] = 0;
    /* and split into lines */
    for (p_i=buf_i;*p_i;p_i++) if (*p_i == '\n' || *p_i == '\r') *p_i = 0;

    /* loop over patterns */
    for (p_p=buf_p,ndx_p=0;ndx_p <= sz_p;ndx_p++) {
        if (!buf_p[ndx_p]) {
            /* found next line */
            if (*p_p) {
                /* found a pattern in p_p */
                pt_limit = 1;
                pt[0] = p_p - buf_p;
                for (p_i=buf_i,ndx_i=0;ndx_i <= sz_i;ndx_i++) {
                    if (!buf_i[ndx_i]) {
                        /* found next line */
                        if (*p_i) {
                            /* found an input in p_i */
                            for (pt_i = 0;pt_i < pt_limit;pt_i++) {
                                if (pt[pt_i]!=-1) {
                                    if (buf_p[pt[pt_i]] == '*') while (buf_p[pt[pt_i]] == '*') pt[pt_i]++;
                                    if (!buf_p[pt[pt_i]]) {
                                        /* found a matching path */
                                        num++;
                                        if (dump) printf ("%s\n", p_i);
                                        break;
                                    }
                                }
                            }
                        }
                        p_i = buf_i + ndx_i + 1;
                        /* reset paths */
                        pt_limit = 1;
                        pt[0] = p_p - buf_p;
                    }
                    else {
                        for (pt_i = pt_limit;pt_i > 0;) {
                            pt_i--;
                            if (pt[pt_i] != -1) {
                                if (!buf_p[pt[pt_i]]) pt[pt_i] = -1;
                                else if (buf_p[pt[pt_i]] == '\\') {
                                    if ((buf_p[pt[pt_i]+1] | 0x20) != (buf_i[ndx_i] | 0x20)) pt[pt_i] = -1;
                                    else { /*printf ("c:%c,p:%c%c, inc+2\n", buf_i[ndx_i],buf_p[pt[pt_i]],buf_p[pt[pt_i]+1]);*/pt[pt_i] += 2;}
                                }
                                else if (buf_p[pt[pt_i]] == '?') pt[pt_i]++;
                                else if (buf_p[pt[pt_i]] == '*') {
                                    while (buf_p[pt[pt_i]+1] == '*') pt[pt_i]++;
                                    if (buf_p[pt[pt_i]+1] && ((buf_p[pt[pt_i]+1] | 0x20) == (buf_i[ndx_i+1] | 0x20))) {
   /*                                   printf ("c:%c,p:%c,next->c:%c,p:%c inc 1\n", buf_i[ndx_i], buf_p[pt[pt_i]],
                                                buf_i[ndx_i+1], buf_p[pt[pt_i]+1]);*/
                                        pt[pt_limit++] = pt[pt_i]+1;
                                    }
                                    if ((buf_p[pt[pt_i]+1] != '\\') && ((buf_p[pt[pt_i]+1] | 0x20) == (buf_i[ndx_i] | 0x20))) {
   /*                                   printf ("c:%c,p:%c,next->c:%c,p:%c inc 2\n", buf_i[ndx_i], buf_p[pt[pt_i]],
                                                buf_i[ndx_i+1], buf_p[pt[pt_i]+1]);*/
                                        pt[pt_limit++] = pt[pt_i]+2;
                                    }
                                    else if (buf_p[pt[pt_i]+1] == '?') {
 /*                                     printf ("c:%c,p:%c,next->c:%c,p:%c inc+2\n", buf_i[ndx_i], buf_p[pt[pt_i]],
                                                buf_i[ndx_i+1], buf_p[pt[pt_i]+1]);*/
                                        pt[pt_limit++] = pt[pt_i]+2;
                                    }
                                    else if ((buf_p[pt[pt_i]+1] == '\\') &&
                                              (buf_p[pt[pt_i]+2] == buf_i[ndx_i])) {
 /*                                     printf ("c:%c,p:%c,next->c:%c,p:%c inc+3\n", buf_i[ndx_i], buf_p[pt[pt_i]],
                                                buf_i[ndx_i+1], buf_p[pt[pt_i]+1]);*/
                                        pt[pt_limit++] = pt[pt_i]+3;
                                    }
                                }
                                else if ((buf_p[pt[pt_i]] | 0x20) != (buf_i[ndx_i] | 0x20)) pt[pt_i] = -1;
                                else { /*printf ("%c,%c\n", buf_p[pt[pt_i]], buf_i[ndx_i]);*/ pt[pt_i]++;}
                            }
                        }
                    }
                }
                if (dump) printf ("\n");
            }
            p_p = buf_p + ndx_p + 1;
            pt_limit = 1;
            pt[0] = p_p - buf_p;
        }
    }

    printf ("%d\n", num);

    fclose (fpat);
    fclose (finp);

    return 0;
}
