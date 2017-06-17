#include <stdio.h>
#include <stdbool.h>

static int g_nlines = 0;
static int g_nwords = 0;
static int g_nbytes = 0;

static void print_result(int l, int w, int b, const char *filename)
{
    if (filename == NULL)
        printf("%8d %7d %7d\n", l, w, b);
    else
        printf("%8d %7d %7d %s\n", l, w, b, filename);
}

static int read_file(FILE *f, const char *filename)
{
    char buffer[4096];
    int nlines = 0;
    int nwords = 0;
    int nbytes = 0;
    size_t nread;
    bool onword = false;

    while ((nread = fread(buffer, sizeof(char), sizeof(buffer), f)) > 0) {
        for (int i = 0; i < nread; i++) {
            nbytes++;
            if (buffer[i] == '\n') {
                nlines++;
            }
            if (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\t') {
                if (onword == false)
                    nwords++;
                onword = true;
            }
            else {
                onword = false;
            }
        }
    }

    print_result(nlines, nwords, nbytes, filename);

    g_nlines += nlines;
    g_nwords += nwords;
    g_nbytes += nbytes;

    return 0;
}

int main(int argc, char const* argv[])
{
    int nfiles = argc - 1;

    if (nfiles == 0)
        read_file(stdin, NULL);
    else {
        while (nfiles > 0) {
            FILE *f;
            const char *filename = argv[argc - nfiles--];
            f = fopen(filename, "r");
            read_file(f, filename);
            fclose(f);
        }
        if (argc > 2) {
            print_result(g_nlines, g_nwords, g_nbytes, "total");
        }
    }

    return 0;
}

// vim: sw=4 ts=4 expandtab
