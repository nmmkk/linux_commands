#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

static int ls(char const *path) {
    DIR *d;
    struct dirent *r;

    if ((d = opendir(path)) == NULL) {
        perror("opendir");
        exit(2);
    }
    while ((r = readdir(d)) != NULL) {
        if (strcmp(r->d_name, ".") == 0 || strcmp(r->d_name, "..") == 0) {
            continue;
        }
        puts(r->d_name);
    }
    closedir(d);

    return 0;
}

int main(int argc, char const* argv[])
{
    char path[PATH_MAX];

    if (argc == 1) {
        if ((getcwd(path, sizeof(path))) == NULL) {
            perror("getcwd");
            exit(1);
        }
        ls(path);
    }
    else if (argc == 2) {
        ls(argv[1]);
    }
    else {
        // If 2 or more paths are given, print the path name before dumping the
        // directory contents.
        for (int i = 1; i < argc; i++) {
            if (i > 1) {
                // Add a blank line for ease of reading
                printf("\n");
            }
            printf("%s:\n", argv[i]);
            ls(argv[i]);
        }
    }

    return 0;
}
