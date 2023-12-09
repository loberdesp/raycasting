#include "headers.h"

int main(int argc, char* args[]) {

	player P;
	controls C;
	map M;
	dispcontrol DC;
	//soundcontrol SC;


	for(int i = 0; i < MAPSIZE; i++) {
		for(int j = 0; j < MAPSIZE; j++) {
			if(i==0 || i == MAPSIZE-1) {
				if(j!= 0 && j!= MAPSIZE-1) {
					M.addWall(i,j);
				}
			}
			if(j==0 || j == MAPSIZE-1) {
				M.addWall(i,j);
			}
		}
	}
	for(int i=20;i<30;i++) {
		for(int j=20;j<30;j++) {
			M.addWall(i,j);
		}

	}
	M.addWall(50,50);

	//define win and rend
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;


	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window and renderer
		window = SDL_CreateWindow( "RAYCAST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINX, WINY, SDL_WINDOW_SHOWN );
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		//Load textures
		DC.loadtextures(renderer);
		//SC.loadsounds();
		




		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		} else {

			bool quit = false;
			
			while( quit == false ) {
				//execute if correct fps
				if (DC.fpsCalc()) {

					//event handling
					while( SDL_PollEvent(C.getEvent())) {
						quit = C.eventSwitch();
					}


					//keeping angle in <-180;180>
					P.checkAngle();
					P.calcRot(0);
					//do working step sounds and gun movement
					//SC.playsound(0);
					SDL_SetRelativeMouseMode(SDL_TRUE);
					//player movement, rotation and collision detection passing player and map as argument by reference
					C.kbHandle(&P, &M);
					C.mouseHandle(&P, &M);

					//update player position every frame
					DC.updatePlayerPos(P.getX(), P.getY());


					//black background display
					SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
					SDL_RenderClear(renderer);

					float a,b,wallH,o = 0;
					bool hor;
					for(int i=MAPSIZE*4;i>=-MAPSIZE*4;i--) {
						a = P.getX();
						b = P.getY();
						P.calcRot(float(i)/float(8));
						M.getline(a,b,P.getVecX(),P.getVecY(), hor);
						SDL_SetRenderDrawColor( renderer, 255, 255, 0, 0 );
						SDL_RenderDrawLine(renderer, P.getX(), P.getY(), a, b);
						float dist = sqrt(pow(a - P.getX(), 2) + pow(b - P.getY(), 2));
						dist = dist*cos(i*M_PI/(180*8));
						if(dist!=0) {
							wallH = (MAPSIZE*WINY)/dist;
						} else {
							wallH = 6*WINY;
						}
						SDL_Rect rwall;
						rwall.x = WINY+o*(TILESIZE/8);
						rwall.y = (WINY/2-wallH/2)+P.getPitch();
						rwall.w = TILESIZE/8;
						rwall.h = wallH;
						//shades when wall is hit vertically
						if(hor) {
							SDL_SetRenderDrawColor( renderer, 0, 255, 255, 0 );
						} else {
							SDL_SetRenderDrawColor( renderer, 0, 180, 180, 0 );
						}
						
						SDL_RenderFillRect( renderer, &rwall );
						
						//floor
						SDL_Rect rfloor;
						rfloor.x = WINY+o*TILESIZE/8;
						rfloor.y = (WINY/2-wallH/2)+P.getPitch()+wallH-1;
						rfloor.w = TILESIZE/8;
						rfloor.h = WINY-rfloor.y;
						SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
						SDL_RenderFillRect( renderer, &rfloor );
						
/*
						//ceiling
						SDL_Rect rceiling;
						rceiling.x = WINY+o*TILESIZE/8;
						rceiling.y = -1;
						rceiling.w = TILESIZE/8;
						rceiling.h = (WINY/2-wallH/2)+P.getPitch()+1;
						SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
						SDL_RenderFillRect( renderer, &rceiling );*/
						o++;
					}
					
					//white walls display
					for(int i=0; i < MAPSIZE;i++) {
						SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
						SDL_RenderDrawLine(renderer, i*TILESIZE, 0, i*TILESIZE, WINY-TILESIZE);
						SDL_RenderDrawLine(renderer, 0, i*TILESIZE, WINY-TILESIZE, i*TILESIZE);
					}
					
					for(int i=0; i < MAPSIZE;i++) {
						SDL_Rect r;
						r.w = TILESIZE;
						r.h = TILESIZE;
						
						for(int j=0; j < MAPSIZE;j++) {
							if(M.checkWall(i,j)==1) {
								r.x = i*TILESIZE;
								r.y = j*TILESIZE;
								SDL_SetRenderDrawColor( renderer, 0, 255, 0, 0 );
								SDL_RenderFillRect( renderer, &r );
							}
						}
					}
					//player display
					SDL_RenderCopyEx(renderer, DC.getImg(0), NULL, DC.getRect(0), -P.getAngle(), NULL, SDL_FLIP_NONE);
					SDL_RenderCopyEx(renderer, DC.getImg(1), NULL, DC.getRect(1), 0, NULL, SDL_FLIP_NONE);
					SDL_RenderPresent(renderer);
				}
			}
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}