/***************************************************
* 
* 描述：测试 getcwd 函数
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *path_alloc(size_t *);

int main(void)
{
    char *ptr;
    size_t size;

    if (chdir("/usr/spool/uucppublic") < 0) {
        printf("chdir failed");
    }
    ptr = path_alloc(&size);

    if (getcwd(ptr, size) == NULL) {
        printf("getcwd failed");
    }
    printf("cwd == %s\n", ptr);

    exit(0);
}

char *path_alloc(size_t *) {

}