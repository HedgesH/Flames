//flames.c
#include "graphics.h"

#define pixel_size 6
#define width 640
#define height 480
#define frames_per_second 60
#define decay_prop 0.05
#define left_prop 0.03

typedef struct {
	float x,y;
	int ix,iy;
	int strength;
} flame;

flame ***flamePoints;
int flamePointSize;
int rand1;
int rand2;

void generateFlameLine(){
	int counter = 0;
	flamePoints = malloc(	((width/pixel_size) + 1) * sizeof(flame**) );
	for (int i = 0; i < (width/pixel_size); ++i)
	{
		*(flamePoints + i) = malloc(	((height/pixel_size) + 1) * sizeof(flame*) );
		for (int j = 0; j < (height/pixel_size) - 1; ++j)
		{
			flame *f = malloc(sizeof(flame));
			f->x = i * pixel_size;
			f->y = j * pixel_size;
			f->ix = i;
			f->iy = j;
			f->strength = 0;
			*(*(flamePoints + i) + j) = f;
		}
	}

	for (int i = 0; i < (width/pixel_size); ++i)
	{
		flame *f = malloc(sizeof(flame));
		f->x = i * pixel_size;
		f->y = height - pixel_size;
		f->ix = i;
		f->iy = (height/pixel_size) - 1;
		f->strength = (height/pixel_size);
		*(*(flamePoints + i) + (height/pixel_size) - 1) = f;
	}

}

void refresh(flame *f, float delta){
	int x = f->ix;
	int y = f->iy;
	flame *ff = *(*(flamePoints + x) + y + 1 );

	if (ff->strength != 0)
	{
		int a = ff->strength - (rand() % rand1);
		int b = rand() % rand2;
		flame *fff;
		if (x > b)
		{
		
			fff = *(*(flamePoints + x - b) + y );
			if(a < 0) fff->strength = 0;
			else fff->strength = a;
		
		}
		// fff = *(*(flamePoints + x) + y );
		// if(a <= 0) fff->strength = 0;
		// else fff->strength = a/1.05;


	}


}

void removeWhite(){

	for (int i = 0; i < (width/pixel_size); ++i)
	{
		flame *f = malloc(sizeof(flame));
		f = *(*(flamePoints + i) + (height/pixel_size) - 1);
		f->strength = 0;
	}
}

void drawFlame(flame *f,display *d){

	for (int x = f->x - (pixel_size/2); x <= f->x + (pixel_size/2); ++x)
	{
		for (int y = f->y - (pixel_size/2); y <= f->y + (pixel_size/2); ++y)
		{
			colour(d,f->strength,pixel_size,height);
			point(d,x,y);	
		}
	}
}

void drawFlame2(flame *f,display *d){

	colour(d,f->strength,pixel_size,height);
	circle(d,f->x,f->y,pixel_size/2);
}


void doFlame(flame *f, display *d, int delta){
		refresh(f,delta);
		if (f->strength != 0) drawFlame(f,d);
		
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	float delta = 1000 / frames_per_second;
	rand1 = (height/pixel_size)*decay_prop;
	rand2 = (height/pixel_size)*left_prop;
	printf("%d.   %d\n",rand1,rand2 );
	display *d = newDisplay("Flames", width, height);
	bool running = true;
	int timer = 0;
	SDL_Event *event;
	event = malloc(sizeof(SDL_Event));
	generateFlameLine();
    




	while(running){
		clear(d);


		for (int i = 0; i < (width/pixel_size); ++i)
		{

			for (int j = 0; j  < (height/pixel_size) - 1; ++j)
			{
				doFlame((*(*(flamePoints + i) + j ) ), d,delta);
			}

		}

		show(d);

		if(timer > 10000) running = false;
		timer += delta;
		pause(d,delta);

		if (SDL_PollEvent(event)) {
	    	if (event->type == SDL_QUIT) {
	        	running = false;
	        	break;
	    	}
	    	if(event->type == SDL_KEYDOWN){
	    		removeWhite();
	    	}
    	}

		// bool running2 = true;
		// while(running2){
		// 	if (SDL_PollEvent(event)) {

	 //    		if (event->type == SDL_QUIT) {
	 //        		running2 = false;
	 //        		running = false;
	 //        		printf("next\n");
	 //    		}
    		
		//     	if (event->type == SDL_KEYDOWN) {
		//         	running2 = false;
		//         	printf("next\n");
	 //    		}
  //   		}
  //   		else pause(d,delta);
		// }
		
	}
	end(d);
	return 0;
}

