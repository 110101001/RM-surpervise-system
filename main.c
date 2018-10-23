#include<unistd.h>
#include"display.h"

#define RAD 40
#define VEL 8

void main(){
    display_init();
    display_clear(RGB(0,0,0));
    while(1){
        for(int x=100;x<500;x+=VEL){
            display_rect(x-RAD-VEL-1,x-RAD-VEL-1,x+RAD-VEL,x+RAD-VEL,RGB(0,0,0));
            display_circle(x,x,RAD,RGB(0,63,0));
            display_rect(x+200-RAD-VEL-1,x-RAD-VEL-1,x+200+RAD-VEL,x+RAD-VEL,RGB(0,0,0));
            display_circle(x+200,x,RAD,RGB(0,63,0));
            usleep(50000);
        }
        for(int x=500;x>100;x-=VEL){
            display_rect(x-RAD+VEL,x-RAD+VEL,x+RAD+VEL+1,x+RAD+VEL+1,RGB(0,0,0));
            display_circle(x,x,RAD,RGB(0,63,0));
            display_rect(x+200-RAD+VEL,x-RAD+VEL,x+200+RAD+VEL+1,x+RAD+VEL+1,RGB(0,0,0));
            display_circle(x+200,x,RAD,RGB(0,63,0));
            usleep(50000);
        }
    }
}
