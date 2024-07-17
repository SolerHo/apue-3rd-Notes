/***************************************************
* 
* 描述：tmpnam 和 tmpfile 函数测试
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4096

int main(void)
{
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL)); // first temp file

    tmpnam(name); // second temp file
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL) { // create temp file
        printf("tmpfile error");
    }

    fputs("one line of output\n", fp); // write to temp file
    rewind(fp); // then read it back

    if (fgets(line, sizeof(line), fp) == NULL) {
        printf("fgets error");
    }

    fputs(line, stdout); // print the line we wrote

    exit(0);
}