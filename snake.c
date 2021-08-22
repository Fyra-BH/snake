#include "snake.h"
  
/**
 * 链表结构：
 *  tail    -next->     node    -next->     ...     -next->     head
 *  tail    <-prior-    node    <-prior-    ...     <-prior-    head 
 * 
*/

//头节点不允许其他文件操作
static s_node_t *start_node=NULL;
s_node_t *head=NULL;

//初始化头节点
void snake_init(){
    start_node = (s_node_t *)mymalloc(sizeof(s_node_t));
    start_node->next=NULL;
    start_node->prior=NULL;
    start_node->pos[0]=POS_X/2;
    start_node->pos[1]=POS_Y/2;
    head = start_node;
}
//接头
//注意，求位置时只加不减，超出的部分用求余解决
void Kyaru(s_node_t *new_head)
{
    
    head->next=new_head;
    new_head->next=NULL;
    new_head->prior=head;
    head=new_head;

    //新的头位置确定
    switch (head->dir)
    {
    case UP:
            head->pos[0] = head->prior->pos[0];
            head->pos[1] = (head->prior->pos[1]-1+POS_Y)%POS_Y;
        break;
    case DOWN:
            head->pos[0] = head->prior->pos[0];
            head->pos[1] = (head->prior->pos[1]+1)%POS_Y;
        break;
    case LEFT:
            head->pos[0] = (head->prior->pos[0]-1+POS_X)%POS_X;
            head->pos[1] = head->prior->pos[1];
        break;
    case RIGHT:
            head->pos[0] = (head->prior->pos[0]+1)%POS_X;
            head->pos[1] = head->prior->pos[1];
    default:
        break;
    }

}

//去尾,如果没尾就不去
void curtail(){
    s_node_t *p=head;
    while (p->prior)
    {
        p=p->prior;
        if(p->prior==NULL)//到尾了
        {
            p->next->prior=NULL;//新的尾节点诞生
            myfree(p);//释放节点内存
        }
    }  
 }

//新建节点
s_node_t *newnode()
{
    s_node_t *node = (s_node_t *)mymalloc(sizeof(s_node_t));
    node->next=NULL;
    node->prior=NULL;
    return node;
}


void print_node()
{
    s_node_t *p=head;
    do
    { 
        static int i=0;
        printf("node%d x=%d,y=%d\r\n",i++,p->pos[0],p->pos[1]);
    }
    while (p->prior);
    
}
//堆分配接口
void *mymalloc(size_t size)
{
    void *p= malloc(size);
#ifdef DEBUG
    printf("\rmalloc addr 0x%x\n",(uint32_t)p);
#endif
    return p;
}

void myfree(void *__ptr)
{
#ifdef DEBUG
    printf("\rfree addr 0x%x\n",(uint32_t)__ptr);
#endif
    free(__ptr);
} 