#include<stdio.h>
#include<stdlib.h>
#include<sys/fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<linux/fb.h>
#include<sys/ioctl.h>
#include"bmp.h"
#include"display.h"

#define BMR(x,y) *(bitmap+3*(x+y*info->bmiHeader.biWidth))
#define BMB(x,y) *(bitmap+3*(x+y*info->bmiHeader.biWidth)+1)
#define BMG(x,y) *(bitmap+3*(x+y*info->bmiHeader.biWidth)+2)

extern unsigned int *fbp;
struct fb_var_screeninfo vinfo;

void bmp_print(int x0,int y0,char* path){
	U8 *bitmap;
	int fd=open(path,O_RDONLY);
	BITMAPFILEHEADER *header;
	BITMAPINFO *info;
	header=malloc(sizeof(BITMAPFILEHEADER));
	info=malloc(sizeof(BITMAPINFO));
	read(fd,header,sizeof(BITMAPFILEHEADER));
	read(fd,info,sizeof(BITMAPINFO));
	int bitmap_size=3*info->bmiHeader.biWidth*info->bmiHeader.biHeight*sizeof(U8);
	//printf("pix size is %d\n",info->bmiHeader.biBitCount);
	bitmap=malloc(bitmap_size);
	lseek(fd,137,SEEK_SET);
	read(fd,bitmap,bitmap_size);
	for(int y=0;y<info->bmiHeader.biHeight;y++){
		for(int x=0;x<info->bmiHeader.biWidth;x++){
			point(x+x0,y0+y)=RGB(BMR(x,y),BMG(x,y),BMB(x,y));
			//point(x,y)=RGB(255,255,0);
			//printf("%d,%d\n",x,y);
		}
	}   
	close(fd);
}

