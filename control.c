/**
 * 
 * 
*/
#include "control.h"

int control_init(){
    system(STTY_US TTY_PATH);
}
int control_exit(){
    system(STTY_DEF TTY_PATH);
    exit(1);
}

int get_char()
{
    fd_set rfds;
    struct timeval tv;
    int ch = 0;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 10; //设置等待超时时间

    //检测键盘是否有输入
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
    {
        ch = getchar(); 
    }

    return ch;
}
