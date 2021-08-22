#ifndef _SNAKE__H
#define _SNAKE__H

//思路:蛇在运动时，相当于不停地接头去尾，需要考虑的是下一步头的朝向

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//显示区域
#define     SIZE_X      320
#define     SIZE_Y      240

//构成蛇方块的大小
#define     BLOCK_SIZE  10

//坐标范围
#define     POS_X      (SIZE_X/BLOCK_SIZE)
#define     POS_Y      (SIZE_Y/BLOCK_SIZE)

//方向枚举
enum DIRECTIONS{
    UP=1,
    DOWN=2,
    LEFT=3,
    RIGHT=4
};
//使用链表来表示蛇
//定义节点
typedef struct s_node
{
 struct s_node *prior;
 struct s_node *next;
 uint16_t pos[2];//position(x,y)
 enum DIRECTIONS dir;//方向参数，只对头有效 
}s_node_t;


void snake_init();
void Kyaru(s_node_t *p);//接头
void curtail();//去尾
s_node_t *newnode();

void *mymalloc(size_t size);
void myfree(void *__ptr);
void print_node();

#endif   