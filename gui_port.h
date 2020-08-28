/**
 * 
 * 
*/
#include "gui.h"

#ifndef _GUI_PORT__H_
#define _GUI_PORT__H_

#define FRAME_WIDTH     32
#define FRAME_HEIGHT    24

#include <stdio.h>
#include <string.h>

void gui_test(void);
void gui_clear(char p);
void gui_flush(void);
void gui_draw_rect(int x1,int y1,int x2,int y2,int color);
#endif