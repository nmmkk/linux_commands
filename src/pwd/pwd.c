#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char const* argv[])
{
    char pathname[PATH_MAX];
    getcwd(pathname, sizeof(pathname));
    printf("%s\n", pathname);
    return 0;
}
