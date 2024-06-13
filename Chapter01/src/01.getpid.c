/***************************************************
 * 
 * 描述：获取进程id
 * 
 * **************************************************
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    printf ("hello world from process ID : %ld\n", (long) getpid());
    exit(0);
}