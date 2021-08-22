/**
 * 
 * 
*/

#include "gui_port.h"


char text_frame[FRAME_HEIGHT][FRAME_WIDTH];

void gui_test()
{
    gui_clear('a');
    sleep(1);
    gui_flush();
    gui_clear('b');
    sleep(1);
    gui_flush();
    gui_clear('d');
    sleep(1);
    gui_flush();
    gui_clear('c');
    sleep(1);
    gui_flush();
}
void gui_clear(char p)
{
  memset(text_frame,p,FRAME_HEIGHT*FRAME_WIDTH);
}

void gui_flush()
{
    
    for (size_t i = 0; i < FRAME_HEIGHT; i++)
    {   
        char buf[FRAME_WIDTH+2];
        buf[FRAME_WIDTH]='\r';
        buf[FRAME_WIDTH+1]='\n';
        memcpy(buf,&text_frame[i][0],FRAME_WIDTH);
        printf(buf);
    }
    
}