#include <stdio.h>

static int cat(FILE *f)
{
    char buf[4096];
    size_t r;

    while ((r = fread(buf, sizeof(char), sizeof(buf), f)) != 0)
        printf("%s", buf);

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
