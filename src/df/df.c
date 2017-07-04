#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/ucred.h>
#include <sys/mount.h>

int main(int argc, char const* argv[])
{
    struct statfs mntbuf[128];
    int len = getfsstat(&mntbuf[0], sizeof(mntbuf), MNT_NOWAIT);
    if (len < 0) {
        perror("getfsstat");
        exit(1);
    }

    printf("%-34s %11s %11s %10s %7s %s\n",
            "Filesystem",
            "512-blocks",
            "Used",
            "Available",
            "Capacity",
            "Mounted on");
    int n = 0;
    for (int n = 0; n < len; n++) {
        struct statfs *p = &mntbuf[n];
        // printf("\tDebug: bsize = %u\n", p->f_bsize);

        uint32_t multiple = 0;
        uint64_t blocks = 0;
        uint64_t avail = 0;
        uint64_t bfree = 0;
        uint32_t capacity = 0;

        if (p->f_blocks > 0) {
            multiple = p->f_bsize / 512;
            blocks = p->f_blocks;
            avail = p->f_blocks - p->f_bfree;
            bfree = p->f_bfree;
            capacity = (avail * 100) / blocks;
        }

        printf("%-34s %11lld %11lld %10lld %7llu%% %s\n",
                p->f_mntfromname,
                blocks * multiple,
                avail * multiple,
                p->f_bfree * multiple,
                capacity,
                p->f_mntonname);
    }

    return 0;
}

// vim: set sw=4 ts=4 et ai cindent :
