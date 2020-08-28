#include "gui.h"
#include <stdio.h>

char *fbp;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
/*
 * framebuffer application code, the start code of Linux GUI application
 * compile :
 *          $/usr/local/arm/2.95.3/bin/arm-linux-gcc -o fbtest fbtest.c
 *          $cp fbtest /tftpboot/examples
 * run in target:
 *          #mount 192.168.1.180:/tftpboot/ /mnt/nfs
 *          #cd /mnt/nfs/examples
 *          #./fbtest
 */
 
void fb_init(){
    int fbfd = 0;
    long int screensize = 0;
    
    int x = 0, y = 0;
    int k;
    int xmax, ymax;
    //long int location = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (!fbfd) {
        printf("Error: cannot open framebuffer device.\n");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
        printf("Error reading fixed information.\n");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("Error reading variable information.\n");
        exit(3);
    }
	
    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    
    printf("%dx%d, %dbpp, screensize = %ld\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel, screensize );

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                       fbfd, 0);
    if ((int)fbp == -1) {
        printf("Error: failed to map framebuffer device to memory.\n");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");
    if(vinfo.bits_per_pixel == 16){ // 16bpp only
       // 16bpp framebuffer test
        printf("16bpp framebuffer test\n");
        printf("two bytes in fbp is a pixel of LCD, just set the value of fbp to put color to LCD\n");
        printf("byte format:\n");
        printf("  bit:| 15 14 13 12 11 | 10 9 8 7 6 5 | 4 3 2 1 0 |\n");
        printf("      |     red        |   green      |    blue   |\n");
	}
}

void PutPixel(unsigned int x,unsigned int y,unsigned int c)
{
    if(x<800 && y<480) {
    	*(fbp + y * 800*2 + x *2) = 0x00FF&c;
    	*(fbp + y * 800*2 + x *2 +1) = (0xFF00&c)>>8;
    }
}
void Glib_Line(int x1,int y1,int x2,int y2,int color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}

void Glib_Rectangle(int x1,int y1,int x2,int y2,int color)
{
    Glib_Line(x1,y1,x2,y1,color);
    Glib_Line(x2,y1,x2,y2,color);
    Glib_Line(x1,y2,x2,y2,color);
    Glib_Line(x1,y1,x1,y2,color);
}

void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color)
{
    int i;

    for(i=y1;i<=y2;i++)
	Glib_Line(x1,i,x2,i,color);
}

//填充函数
void frame_fill(int c)
{

        for(int y = 0; y < vinfo.yres; y++)
        {
            for(int x = 0; x < vinfo.xres; x++)
            {
                *(fbp + y * vinfo.xres*2 + x*2) = 0xff&c;
                *(fbp + y * vinfo.xres*2 + x*2 +1) = 0xff&(c>>8);
            }
        }
}

void Draw_Circle(unsigned short  x0,unsigned short y0,unsigned char r,unsigned short color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	while(a<=b)
	{
		PutPixel(x0-b,y0-a,color);             //3           
		PutPixel(x0+b,y0-a,color);             //0           
		PutPixel(x0-a,y0+b,color);             //1                
		PutPixel(x0-a,y0-b,color);             //2             
		PutPixel(x0+b,y0+a,color);             //4               
		PutPixel(x0+a,y0-b,color);             //5
		PutPixel(x0+a,y0+b,color);             //6 
		PutPixel(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}

/******************************************************************************
      函数说明：显示字符
      入口数据：x,y    起点坐标
                num    要显示的字符
                mode   1叠加方式  0非叠加方式
      返回值：  无
******************************************************************************/
void ShowChar(u16 x,u16 y,u8 num,u16 color)
{
    u8 temp;
    u8 pos,t;
	  u16 x0=x;     
    if(x>800-16||y>480-16)return;	    //设置窗口		   
	num=num-' ';//得到偏移后的值

	for(pos=0;pos<16;pos++)
	{
		temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
		for(t=0;t<8;t++)
		{                 
			if(temp&0x01)PutPixel(x+t,y+pos,color);//画一个点     
			temp>>=1; 
		}
	}
		   	 	  
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y    起点坐标
                *p     字符串起始地址
      返回值：  无
******************************************************************************/
void ShowString(u16 x,u16 y,const u8 *p,u16 color)
{         
    while(*p!='\0')
    {       
        if(x>800-16){x=0;y+=16;}
        if(y>480-16){y=x=0;frame_fill(RED);}
        ShowChar(x,y,*p,color);
        x+=8;
        p++;
    }  
}
