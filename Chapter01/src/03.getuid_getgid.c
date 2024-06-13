/***************************************************
 * 
 * 描述：获取用户ID和组ID
 * 
 * **************************************************
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    printf("uid = %d gid = %d\n", getuid(), getgid());
    exit(0);
}