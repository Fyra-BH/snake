/**
 * 
 * 
*/
#include "control.h"
#include "snake.h"

extern s_node_t *head;

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

//控制蛇的运动
void contorl(char ch)
{
    // 判断命令是否存在
    if(\
        ch!= 'w'\
        &&ch!= 'W'\
        &&ch!= 'a'\
        &&ch!= 'A'\
        &&ch!= 's'\
        &&ch!= 'S'\
        &&ch!= 'd'\
        &&ch!= 'D'\
    ){
        return;
    }
s_node_t * p=newnode();
p->dir=head->dir;

switch (ch)
    {
        case 27://cesc
            control_exit();
        case 'w':{
            if(head->dir!=DOWN)//不能调头
                p->dir=UP;
            break;
        }
        case 'a':{
            if(head->dir!=RIGHT)//不能调头
                p->dir=LEFT;
            break;
        }
        case 's':{
            if(head->dir!=UP)//不能调头
                p->dir=DOWN;
            break;
        }
        case 'd':{
            if(head->dir!=LEFT)//不能调头
                p->dir=RIGHT;
            break;
        }
        case 'q':{
            print_node();
            break;
        }
    }
    //接头去尾
    Kyaru(p);
    if (eat_food())
    {
       //产生新的食物
        printf("eat_food\n");
        generate_food();
    }else
    {
        curtail();
    }
    draw_snake();
    if(smash_detect())
    {
        exit(2);
    }
    //绘制
}