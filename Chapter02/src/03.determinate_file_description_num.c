 /***************************************************
 * 
 * 描述：确定文件描述符个数
 * 
 * **************************************************
 */

#include <errno.h>
#include <limits.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

// if OPEN_MAX is indeterminate, this might be inadequte

#define OPEN_MAX_GUESS 256

long open_max(void)
{
    if (open_max == 0) { // first time through
        errno = 0;
    }

    if ((open_max = sysconf(_SC_OPEN_MAX)) < 0) {
        if (errno == 0) {
            openmax = OPEN_MAX_GUESS; // it's indeterminate
        } else {
            printf("sysconf error for _SC_OPEN_MAX");
        }
    }
}