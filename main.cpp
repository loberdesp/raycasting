#include "headers.h"

int main(int argc, char* args[])
{

	player P;
	controls C;
	dispcontrol DC;

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
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN, WIN, SDL_WINDOW_SHOWN );
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		//Load textures
		DC.loadtextures(renderer);


		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		} else {

			bool quit = false;
			
			while( quit == false ) {
				//exectue if correct fps
				if (DC.fpsCalc()) {

					//event handling
					while( SDL_PollEvent(C.getEvent())) {
						quit = C.eventSwitch();
					}

					//keeping angle in <-180;180>
					P.checkAngle();
					P.calcRot(0);

					//player movement and rotate, passing player as argument by reference
					C.kbHandle(&P);

					//update player position every frame
					DC.updatePlayerPos(P.getX(), P.getY());


					//display player to screen
					SDL_RenderClear(renderer);
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