#include "display.h"
#include "bmp.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <pthread.h>

#define RAT_NUM 5
#define MIN_TIME 6
#define RIDAUS 50
#define TIME 10
#define WIDE 800
#define HEIGHT 480

#define TS_WIDE 4000
#define TS_HEIGHT 4000;

int pos_x, pos_y;
int score_sum;
void *getkey (void);
void *draw (void);

typedef struct rat{
	int x,y;
	int t;

}rat;

rat Rats[RAT_NUM]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

void manageRat(){
	for(int i=0;i<RAT_NUM;i++){
		if(Rats[i].t==0){
			display_rect(Rats[i].x-RIDAUS,Rats[i].y-RIDAUS,Rats[i].x+RIDAUS,Rats[i].y+RIDAUS,RGB(255,255,255));
			Rats[i].t=rand()%TIME+MIN_TIME;
			int nearFlag=1;
			while(nearFlag){
				nearFlag=0;
				Rats[i].x=rand()%(WIDE-2*RIDAUS)+RIDAUS;
				Rats[i].y=rand()%(HEIGHT-2*RIDAUS)+RIDAUS;
				for(int j=0;j<RAT_NUM;j++){
					if( i!=j&&(Rats[j].x-Rats[i].x)*(Rats[j].x-Rats[i].x)+(Rats[j].y-Rats[i].y)*(Rats[j].y-Rats[i].y) < 6*RIDAUS*RIDAUS){
						nearFlag=1;
					}
				}
			}
		}
		Rats[i].t-=1;
	}
}

int killRat(int x, int y){
	int score=0;
	for(int i=0;i<RAT_NUM;i++){
		if(Rats[i].t!=0){
			if( (x-Rats[i].x)*(x-Rats[i].x)+(y-Rats[i].y)*(y-Rats[i].y) < RIDAUS*RIDAUS){
				score+=1;
				Rats[i].t=0;
				display_circle(Rats[i].x,Rats[i].y,RIDAUS,RGB(255,0,0));
			}
		}
	}
	return score;
}

int drawRat(){
	//display_clear(RGB(0,0,0));
	for(int i=0;i<RAT_NUM;i++){
		//display_circle(Rats[i].x,Rats[i].y,RIDAUS,RGB(255,0,0));
		bmp_print(Rats[i].x-RIDAUS,Rats[i].y-RIDAUS,"./rat.bmp");
	}
}
char *path;
int main (int argc, char ** argv)
{
	display_init();
	path=argv[1];
	pthread_t thread_id1;
	pthread_t thread_id2;

	pthread_create (&thread_id1, NULL, &getkey, NULL);
	pthread_create (&thread_id2, NULL, &draw, NULL);
	pthread_join (thread_id1, NULL);
	pthread_join (thread_id2, NULL);
	getchar ();
}

	void *
draw ()
{
	int x1, y1, i;
	display_clear(RGB(255,255,255));
	//bmp_print(0,0,"./rat.bmp");
	//display_rect(0,0,100,100,RGB(0,0,255));
	//return;
	while (1)
	{
		manageRat();
		drawRat();
		usleep(200000);
	}

}

	void *
getkey ()
{
	int keys_fd;
	struct input_event t;

	keys_fd = open (path, O_RDONLY);
	/* In Kernel V3.0.8, the touch screen device is /dev/input/event3 */

	if (keys_fd <= 0)
	{
		printf ("Opening Touch Screen Device error!\n");
		return 0;
	}

	while (1)
	{
		if (read (keys_fd, &t, sizeof (t)) == sizeof (t))
		{
			if (t.type == EV_ABS && t.code == ABS_X)
				pos_x = t.value;

			else if (t.type == EV_ABS && t.code == ABS_Y)
				pos_y = t.value;

		}
		int retv=0;
		if((retv=killRat(WIDE-pos_y/5,pos_x*3/25))!=0){
			score_sum+=retv;
			printf("score:%d\n",score_sum);
		}		
	}
	close (keys_fd);
}
