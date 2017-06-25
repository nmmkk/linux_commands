#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

enum e_filetype {
    eFile = 0,
    eDir,
    eSymLink,
    eNotExist,
    eError,
    e_filetype_number
};

struct pathinfo {
    char const* path;
    char const* bname;
    struct stat status;
    enum e_filetype filetype;
};

static void usage(void)
{
    printf("mv <source> <dest>\n");
    return;
}

static char* get_basename(const char* path)
{
    char *p;
    if ((p = strrchr(path, '/')) == NULL)
        p = (char*)path;
    return p;
}

static enum e_filetype do_stat(char const* path, struct stat* p_stat)
{
    enum e_filetype r = eError;

    int err = (stat(path, p_stat) == 0 ? 0 : errno);
    if (err && err != ENOENT) {
        fprintf(stderr, "Failed to access %s (%s)\n", path, strerror(err));
        exit(1);
    }

    if (err == ENOENT) {
        p_stat = NULL;
        r = eNotExist;
    }
    else {
        switch (p_stat->st_mode & S_IFMT) {
            case S_IFREG:
                r = eFile;
                break;
            case S_IFDIR:
                r = eDir;
                break;
            case S_IFLNK:
                r = eSymLink;
                break;
            default:
                break;
        }
    }

    return r;
}

static void init_struct(struct pathinfo* p, char const* path)
{
    p->path = path;
    p->filetype = do_stat(p->path, &p->status);
    p->bname = get_basename(p->path);
}

int main(int argc, char const* argv[])
{
    struct pathinfo old;
    struct pathinfo new;

    if (argc == 3) {
        init_struct(&old, argv[1]);
        init_struct(&new, argv[2]);

        if (old.status.st_ino == new.status.st_ino) {
            fprintf(stderr, "'%s' and '%s' are the same file\n",
                    old.path, new.path);
            exit(1);
        }

        if (old.filetype == eDir && new.filetype == eFile) {
            fprintf(stderr, "cannot overwrite non-direcotry '%s' with directory '%s'\n",
                    new.path, old.path);
            exit(1);
        }

        // If oldpath points a file and newpath points a directory, file's
        // basename needs to be appended for rename().
        if (old.filetype == eFile && new.filetype == eDir) {
            char path[PATH_MAX];
            snprintf(path, sizeof(path), "%s/%s", new.path, old.bname);
            if ((rename(old.path, path)) != 0) {
                perror("rename");
                exit(1);
            }
        }
        else {
            if ((rename(old.path, new.path)) != 0) {
                perror("rename");
                exit(1);
            }
        }
    }
    else {
        // TODO: Should be extended to handle files more than 2.
        usage();
        exit(1);
    }

    return 0;
}
