/***************************************************
* 
* 描述：对各个标准I/O流打印缓冲状态信息
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>

void pr_stdio(const char *, FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffer_size(FILE *);

int main(void) {
    FILE *fp;
    fputs("enter any character\n", stdout);
    if (getchar() == EOF) {
        printf("getchar error");
    }

    fputs("one line to standard error\n", stderr);

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if ((fp = fopen("/etc/passwd", "r")) == NULL) {
        printf("fopen error");
    }
    if (getc(fp) == EOF) {
        printf("getc error");
    }

    pr_stdio("/etc/passwd", fp);
    exit(0);
}

void pr_stdio(const char *name, FILE *fp)
{
    printf("stream == %s", name);
    if (is_linebuffered(fp)) {
        printf("unbuffered");
    } else if (is_linebuffered(fp)) {
        printf("line unbuffered");
    } else {
        printf("fully buffered");
    }
    printf(", buffer size = %d\n", buffer_size(fp));
}

#if defined(_IO_UNBUFFERED)

int is_unbuffered(FILE *fp)
{
    return (fp->_flags & _IO_UNBUFFERED);
}

int is_linebuffered(FILE *fp)
{
    return (fp->_flags & _IO_LINE_BUF);
}


int buffer_size(FILE *fp)
{
    return (fp->_IO_buf_end  - fp->_IO_buf_base);
}

#elif defined(__SNBF)

int is_unbuffered(FILE *fp)
{
    return (fp->_flags & __SNBF);
}

int is_linebuffered(FILE *fp)
{
    return (fp->_flags & __SLBF);
}


int buffer_size(FILE *fp)
{
    return fp->_buf.size;
}

#elif defined(_IONBF)

// #ifdef _LP64
// #define _flag __pad[4]
// #define _ptr __pad[1]
// #define _base __pad[2]
// #endif

int is_unbuffered(FILE *fp)
{
    return (fp->_flags & _IONBF);
}

int is_linebuffered(FILE *fp)
{
    return (fp->_flags & _IOLBF);
}


int buffer_size(FILE *fp)
{
#ifdef _LP64
    return (fp->_IO_buf_end  - fp->_IO_buf_base);
#else
    return (BUFSIZ);
#endif
}

#else

#error unknown stdio implementation!
#endif

