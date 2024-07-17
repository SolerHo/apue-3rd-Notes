/***************************************************
* 
* 描述：测试umask函数
* 
* **************************************************
*/

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(void) {
    umask(0);

    if (creat("foo", RWRWRW) < 0) {
        printf("create error for foo");
    }
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", RWRWRW) < 0) {
        printf("ctreate error for bar");
    }
    exit(0);
}

