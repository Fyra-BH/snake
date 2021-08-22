#include "stdio.h"
#include <stdlib.h>

#include "control.h"
#include "snake.h"

int main(int argc, char const *argv[])
{
    int ch = 0;
    // gui_test();
    system("ls -l");
    return 0;

    control_init();
    snake_init();
    
    while(1)
    {
        ch = get_char();
        if (ch)
        {
           // printf("key = %d\n\r", ch);
            switch (ch)
            {
                case 27://cesc
                    control_exit();
                case 'w':{
                   // printf("w\n\r");
                    s_node_t * p=newnode();
                    p->dir=UP;
                    Kyaru(p);
                    curtail();
                    break;}
                case 'a':{
                  //  printf("a\n\r");
                    s_node_t * p=newnode();
                    p->dir=LEFT;
                    Kyaru(p);
                    curtail();
                    break;}
                case 's':{
                   // printf("s\n\r");
                    s_node_t * p=newnode();
                    p->dir=DOWN;
                    Kyaru(p);
                    curtail();
                    break;}
                case 'd':{
                   // printf("d\n\r");
                    s_node_t * p=newnode();
                    p->dir=RIGHT;
                    Kyaru(p);
                    curtail();
                    break;}
                case 'q':{
                        print_node();
                    break;}
            }
        }           
    }
}
