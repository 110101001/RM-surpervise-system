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

extern unsigned short *fbp;
struct fb_var_screeninfo vinfo;

void bmp_print(char* path){
    U8 *bitmap;
    int fd=open(path,O_RDONLY);
    BITMAPFILEHEADER *header;
    BITMAPINFO *info;
    header=malloc(sizeof(BITMAPFILEHEADER));
    info=malloc(sizeof(BITMAPINFO));
    read(fd,header,sizeof(BITMAPFILEHEADER));
    read(fd,info,sizeof(BITMAPINFO));
    int bitmap_size=3*info->bmiHeader.biWidth*info->bmiHeader.biHeight*sizeof(U8);
    bitmap=malloc(bitmap_size);
    printf("bitmap:%d@%x\n,",bitmap_size,(header->bfOffBits)/8);
    //fseek(fd,(header->bfOffBits)/8,SEEK_SET);
    read(fd,bitmap,bitmap_size);
    for(int x=0;x<info->bmiHeader.biWidth;x++){
        for(int y=0;y<info->bmiHeader.biHeight;y++){
            *(int*)(fbp+2*((x)+(y)*vinfo.xres))=*(int*)(bitmap+3*(x+y*info->bmiHeader.biWidth))<<8;
        }
    }   
}

void main(){
    display_init();
    bmp_print("./1.bmp");
    
}
