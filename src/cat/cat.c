#include <stdio.h>

static int cat(FILE *f)
{
    int c;

    while ((c = fgetc(f)) != EOF) {
        putc(c, stdout);
    }

    return 0;
}

int main(int argc, char const* argv[])
{
    FILE *f;

    if (argc == 1)
        cat(stdin);
    else
        for (int i = 0; i < argc - 1; i++) {
            f = fopen(argv[i + 1], "r");
            cat(f);
            fclose(f);
        }

    return 0;
}
