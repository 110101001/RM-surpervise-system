#ifndef DISPLAY_H_
#define DISPLAY_H_
//b<32 g<64 r<32 
#define RGB(r,g,b) ((short)b+((short)g<<5)+((short)r<<11))
#define point(x,y) *(fbp+(x)+(y)*vinfo.xres)
#define draw_point(x,y,r,g,b) point(x,y)=RGB(r,g,b) 
#define ABS(x) x>0?x:-x

int display_init();
void display_point(int x,int y,unsigned short rgb);
void display_rect(int x1,int y1,int x2,int y2,short rgb);
void display_clear(int rgb);
void display_line(int x1,int y1,int x2,int y2,short rgb);
void display_circle(int cx,int cy,int r,int rgb);

#endif
