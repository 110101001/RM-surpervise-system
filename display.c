#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<errno.h>
#include<fcntl.h>
#include<linux/fb.h>
#include<sys/ioctl.h>
#include"display.h"

extern int errno;
unsigned short *fbp = 0;
struct fb_var_screeninfo vinfo;

float InvSqrt (float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);        // 计算第一个近似根
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);       // 牛顿迭代法
    return x;
}

int display_init(){
    int fd;
    fd=open("/dev/fb0" , O_RDWR);
    ioctl(fd, FBIOGET_VSCREENINFO,&vinfo);
    int ssize=vinfo.xres*vinfo.yres*vinfo.bits_per_pixel/8;
    fbp = (unsigned short *) mmap(0,ssize,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("Display Init:\n Screen Size:%dx%d\n BitPerPix:%d\n",vinfo.xres,vinfo.yres,vinfo.bits_per_pixel);
    return errno;

}

void display_point(int x,int y,unsigned short rgb){
    point(x,y)=rgb;
}

void display_rect(int x1,int y1,int x2,int y2,short rgb){
    for(int i=y1;i<y2;i++)
        for(int j=x1;j<x2;j++)
            point(j,i)=rgb;
}

void display_clear(int rgb){
    for(int i=0;i<vinfo.yres;i++)
        for(int j=0;j<vinfo.xres;j++)
            point(j,i)=rgb;
}

void display_line(int x1,int y1,int x2,int y2,short rgb){
    int dx = ABS(x2 - x1), dy = ABS(y2 - y1);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy;
    int twoDyminusDx = 2 * (dy - dx);
    int x, y;

    /*根据斜率正负决定起始点和终结点*/
    if (x1 > x2){
        x = x2;
        y = y2;
        x2 = x1;
    }
    else{
        x = x1;
        y = y1;
    }
    point(x, y)=rgb;

    while (x < x2){
        x++;
        if (p < 0)
            p += twoDy;
        else{
            y++; p += twoDyminusDx;
        }
        point(x, y)=rgb;
    }
}

void display_circle(int cx,int cy,int r,int rgb){
    int sqrt2r=(int)(r*InvSqrt(2.0));
    for(int y=-r;y<=-sqrt2r;y++){
        int l=(int)(InvSqrt(1.0/(float)(r*r-y*y)));
        for(int x=-l;x<=l;x++){
            point(cx+x,cy+y)=rgb;
            point(cx-x,cy-y)=rgb;
            point(cx+y,cy+x)=rgb;
            point(cx-y,cy-x)=rgb;
        }
    }
    display_rect(cx-sqrt2r,cy-sqrt2r,cx+sqrt2r,cy+sqrt2r,rgb);
}
