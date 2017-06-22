#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>

static int cd(char const *path)
{
    int r;
    if ((r = chdir(path)) != 0)
        perror("chdir");
    return r;
}

static void show_usage(void)
{
    printf("usage: cd [<pathname>]\n");
    printf("\n");
    printf("Note: This program does not change current directory of the shell\n");
    printf("  process. It just changes the working directory of the process of\n");
    printf("  this program.\n");
}

int main(int argc, char const* argv[])
{
    char pathname[PATH_MAX];

    if (argc == 1) {
        char *p;
        if ((p = getenv("HOME")) == NULL) {
            p = getpwuid(getuid())->pw_dir;
        }
        snprintf(pathname, sizeof(pathname) - 1, "%s", p);
    }
    else if (argc == 2) {
        snprintf(pathname, sizeof(pathname) - 1, "%s", argv[1]);
    }
    else {
        // Too many arguments
        show_usage();
        exit(1);
    }

    if (cd(pathname) != 0)
        exit(2);

    printf("The *working directory* of this process is now <%s>\n", pathname);

    return 0;
}

