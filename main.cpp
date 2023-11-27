#include "headers.h"

int main(int argc, char* args[])
{

	player P;
	controls C;
	map M;
	dispcontrol DC;

	//tmp wall


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
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINX, WINY, SDL_WINDOW_SHOWN );
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		//Load textures
		DC.loadtextures(renderer);




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

					//player movement, rotation and collision detection passing player and map as argument by reference
					C.kbHandle(&P, &M);

					//update player position every frame
					DC.updatePlayerPos(P.getX(), P.getY());


					//black background display
					SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
					SDL_RenderClear(renderer);

					float a,b,wallH,o = 0;
					int val = MAPSIZE/64;
					for(int i=MAPSIZE/2;i>=-MAPSIZE/2;i--) {
						a = P.getX();
						b = P.getY();
						P.calcRot(i/val);
						M.getline(a,b,P.getVecX(),P.getVecY());
						SDL_SetRenderDrawColor( renderer, 255, 255, 0, 0 );
						SDL_RenderDrawLine(renderer, P.getX(), P.getY(), a, b);
						float dist = sqrt(pow(a - P.getX(), 2) + pow(b - P.getY(), 2));
						dist = dist*cos(i*M_PI/180);
						if(dist!=0) {
							wallH = (MAPSIZE/val*WINY)/dist;
							// if(wallH>WINY) {
							// 	wallH = WINY;
							// }
						} else {
							wallH = 6*WINY;
						}
						SDL_Rect r;
						r.x = WINY+o*TILESIZE;
						r.y = (WINY/2-wallH/2)+P.getPitch();
						r.w = TILESIZE;
						r.h = wallH;
						SDL_SetRenderDrawColor( renderer, 0, 255, 255, 0 );
						SDL_RenderFillRect( renderer, &r );
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
								r.x = j*TILESIZE;
								r.y = i*TILESIZE;
								SDL_SetRenderDrawColor( renderer, 0, 255, 0, 0 );
								SDL_RenderFillRect( renderer, &r );
							}
						}
					}
					//player display
					SDL_RenderCopyEx(renderer, DC.getImg(0), NULL, DC.getRect(0), -P.getAngle(), NULL, SDL_FLIP_NONE);
					
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