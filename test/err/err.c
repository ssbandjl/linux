/* Function: obtain the errno string
*   char *strerror(int errno)
*/
 
#include <stdio.h>
#include <string.h>     //for strerror()
//#include <errno.h>
int main()
{
    int tmp = 0;
    for(tmp = 0; tmp <=256; tmp++)
    {
        printf("errno: %2d\t%s\n",tmp,strerror(tmp));
    }
    return 0;
}

2. 打印错误信息
1). 打印错误信息 / perror
作用：
打印系统错误信息

头文件：

#include <stdio.h>  
函数原型：

void perror(const char *s)
参数：

s: 字符串提示符

输出形式：
const char *s: strerror(errno) //提示符：发生系统错误的原因
返回值：
无返回值
2). 字符串显示错误信息 / strerror
作用：
将错误码以字符串的信息显示出来

头文件：

#include <string.h>  
函数原型：

char *strerror(int errnum);
参数：

errnum: 即errno

返回值：
返回错误码字符串信息


glibc, https://elixir.bootlin.com/glibc/latest/source/string/strerror.c
#include <string.h>
#include <locale/localeinfo.h>

char *
strerror (int errnum)
{
  return __strerror_l (errnum, __libc_tsd_get (locale_t, LOCALE));
}

