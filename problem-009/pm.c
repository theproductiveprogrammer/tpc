#include <stdio.h>

#define MAX_FSZ (1 * 1024 * 1024)
#define MAX_DEPTH (1 * 1024 * 1024)

#define CUR_INP (buf_i[ndx_i])
#define CUR_PATH (pt[pt_i])
#define CUR_PAT (buf_p[CUR_PATH])
#define NEXT_PAT (buf_p[CUR_PATH+1])
#define NEXT_NEXT_PAT (buf_p[CUR_PATH+2])
#define NEW_PATH (pt[pt_limit++])

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

    fpat = fopen (patf, "rb");
    sz_p = fread (buf_p, sizeof (char), MAX_FSZ, fpat);
    buf_p[sz_p] = 0;
    for (p_p=buf_p;*p_p;p_p++) if (*p_p == '\n' || *p_p == '\r') *p_p = 0;
    finp = fopen (inputf, "rb");
    sz_i = fread (buf_i, sizeof (char), MAX_FSZ, finp);
    buf_i[sz_i] = 0;
    for (p_i=buf_i;*p_i;p_i++) if (*p_i == '\n' || *p_i == '\r') *p_i = 0;

    for (p_p=buf_p,ndx_p=0;ndx_p <= sz_p;ndx_p++) {
        if (!buf_p[ndx_p]) {
            if (*p_p) {
                pt_limit = 1;
                pt[0] = p_p - buf_p;
                for (p_i=buf_i,ndx_i=0;ndx_i <= sz_i;ndx_i++) {
                    if (!CUR_INP) {
                        if (*p_i) {
                            for (pt_i = 0;pt_i < pt_limit;pt_i++) {
                                if (CUR_PATH!=-1) {
                                    if (CUR_PAT == '*') while (CUR_PAT == '*') CUR_PATH++;
                                    if (!CUR_PAT) {
                                        num++;
                                        if (dump) printf ("%s\n", p_i);
                                        break;
                                    }
                                }
                            }
                        }
                        p_i = buf_i + ndx_i + 1;
                        pt_limit = 1;
                        pt[0] = p_p - buf_p;
                    }
                    else {
                        for (pt_i = pt_limit;pt_i > 0;) {
                            pt_i--;
                            if (CUR_PATH != -1) {
                                if (!CUR_PAT) CUR_PATH = -1;
                                else if (CUR_PAT == '\\') {
                                    if ((NEXT_PAT | 0x20) != (CUR_INP | 0x20)) CUR_PATH = -1;
                                    else CUR_PATH += 2;
                                }
                                else if (CUR_PAT == '?') CUR_PATH++;
                                else if (CUR_PAT == '*') {
                                    while (NEXT_PAT == '*') CUR_PATH++;
                                    if (NEXT_PAT && ((NEXT_PAT | 0x20) == (buf_i[ndx_i+1] | 0x20))) {
                                        NEW_PATH = CUR_PATH+1;
                                    }
                                    if ((NEXT_PAT != '\\') && ((NEXT_PAT | 0x20) == (CUR_INP | 0x20))) {
                                        NEW_PATH = CUR_PATH+2;
                                    }
                                    else if (NEXT_PAT == '?') {
                                        NEW_PATH = CUR_PATH+2;
                                    }
                                    else if ((NEXT_PAT == '\\') &&
                                              (NEXT_NEXT_PAT == CUR_INP)) {
                                        NEW_PATH = CUR_PATH+3;
                                    }
                                }
                                else if ((CUR_PAT | 0x20) != (CUR_INP | 0x20)) CUR_PATH = -1;
                                else CUR_PATH++;
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
