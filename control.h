 #ifndef _CONTROL__H
 #define _CONTROL__H

//摘自https://blog.csdn.net/qq_14835443/article/details/50446099?depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-1&utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-1

#include <stdio.h>
#include <stdlib.h>

#include "sys/select.h"

#define TTY_PATH            "/dev/tty"
#define STTY_US             "stty raw -echo -F "
#define STTY_DEF            "stty -raw echo -F "

int control_init();
int get_char();

#endif