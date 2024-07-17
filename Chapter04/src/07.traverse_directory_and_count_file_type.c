/***************************************************
* 
* 描述：递归降序遍历目录层次结构，并按文件类型计数
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>


/* function type that is called for each filename */
typedef int MyFunc(const char *, const struct stat *, int );

static MyFunc myfunc;
static int myftw(char *, MyFunc *);
static int dopath(MyFunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[])
{
    int ret;
    if (argc != 2) {
        printf("usage : ftw < starting-pathname>");
        exit(0);
    }

    ret = myftw(argv[1], myfunc); // does it all
    ntot = nreg = ndir + nblk + nfifo + nslink + nsock;

    if (ntot == 0) {
        ntot = 1; // avoid divide by 0; print 0 for all counts
    }

    printf("regular files = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
    printf("directories = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
    printf("block special = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
    printf("char special = %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
    printf("FIFOs = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
    printf("sockets = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);

    exit (ret);
}



/**
* descend through the hierarchy, starting at "pathname"
* The caller's func() is called for every file.
*
*/

#define FTW_F 1 // file other than directory
#define FTW_D 2 // directory
#define FTW_DNR 3 // directory that can't be read
#define FTW_NS 4 // file that we can't stat

static char *fullpath; // contain full pathname for every file
static size_t pathlen; // 

static int myftw(char *pathname, MyFunc *func) {
    fullpath = path_alloc(&pathlen);  // malloc PATH_MAX + 1 bytes

    if (pathlen <= strlen(pathname)) {
        pathlen = strlen(pathname) * 2;
        if ((fullpath == realloc(fullpath, pathlen)) == NULL) {
            printf("realloc failed");
        }
    }
    strcpy(fullpath, pathname);
    return (dopath(func));
}

static int dopath (MyFunc *func) {
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret, n;

    if (lstat(fullpath, &statbuf) < 0) {
        printf("lstat error");
        return (func(fullpath, &statbuf, FTW_NS));
    }

    if (S_ISDIR(statbuf.st_mode) == 0) {
        printf("directory");
        return (func(fullpath, &statbuf, FTW_F));
    }

    /***
     * it's a directory, First call func() for the directory,
     * then process each filename in the directory
     *
    **/
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0) {
        return ret;
    }

    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen) {
        pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathname)) == NULL) {
            printf("realloc error");
        }
    }

    fullpath[n++] = '/';
    fullpath[n] = 0;

    if ((dp == opendir(fullpath)) == NULL) {
        return (func(fullpath, &statbuf, FTW_DNR))
    }

    while ((dirp = readdir(dp)) !== NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
            continue;
        }

        strcpy(&fullpath[n], dirp->d_name); // append name after
        if ((ret = dopath(func)) != 0) {
            break;
        }
    }

    fullpath[n - 1] = 0; // erase everything from slash onward
    if (closedir(dp) < 0) {
        printf("can't close directory %s", fullpath);
    }

    return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type) {
    switch (type)
    {
    case FTW_F:
        switch (statptr->st_mode & S_IFMT)
        {
            case S_IFREG:
                nreg++;
                break;
            case S_IFBLK:
                nblk++;
                break;
            case S_IFCHR:
                nchr++;
                break;
            case S_IFIFO:
                nfifo++;
                break;
            case S_IFLNK:
                nslink++;
                break;
            case S_IFSOCK:
                nsock++;
                break;
            case S_IFDIR:
                printf("for S_IFDIR for %s", pathname);
            default:
                break;
        }
        break;
    case FTW_D:
        ndir++;
        break;
    case FTW_DNR:
        printf("can't read directory %s", pathname);
        break;
    case FTW_NS:
        printf("stat error for %s", pathname);
        break;
    default:
        printf("unknown type %d foir pathname %s", type, pathname);
    }

    return 0;
}


