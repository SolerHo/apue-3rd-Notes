 /***************************************************
 * 
 * 描述：为路径名动态分配存储区的函数
 * 
 * **************************************************
 */

#include <errno.h>
#include <limits.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

/* if MAX_PATH is indeterminate, no guarantee this is adequete */
#define PATH_MAX_GUESS 1024

char *path_allocate(size_t *sizep) /*also return allocated size, if nonnull */
{
    char *ptr;
    size_t size;

    if (posix_version == 0) {
        posix_version = sysconf(_SC_VERSION);
    }

    if (xsi_version == 0) {
        xsi_version = sysconf(_SC_XOPEN_VERSION);
    }

    if (pathmax == 0) { /* first time through */
        errno = 0;
        if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
            if (errno == 0) {
                pathmax = PATH_MAX_GUESS; /*it's indeterminate */
            } else {
                printf("pathconf error for _PAC_PATH_MAX");
            }
        } else {
            pathmax++; /* add one since it's relative to root */
        }

        /**
         * Before POSIX.1-2001, we aren't guaranteed that PATH_MAX includes
         * the terminating null byte, same goes for XPG3
        **/

        if ((posix_version < 2001123L) && (xsi_version < 4)) {
            size = pathmax + 1;
        } else {
            size = pathmax;
        }

        if ((ptr = malloc(size)) == NULL) {
            printf("malloc error for pathname");
        }

        if (sizep != NULL) {
            *sizep = size;
        }

        return (ptr);
    }
}
