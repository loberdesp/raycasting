#include "headers.h"

int main( int argc, char* args[] )
{

	player P;
	dispcontrol DC;


	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	int angle = 0;

	//mouse rotating
	SDL_SetRelativeMouseMode(SDL_TRUE);

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

		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{

            //Hack to get window to stay up
            SDL_Event e;
			bool quit = false;

			//fps tools
			unsigned int a = SDL_GetTicks();
			unsigned int b = SDL_GetTicks();
			double delta = 0;


			const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

			while( quit == false ) {

				//FPS calculation and framerate cap
				a = SDL_GetTicks();
				delta = a - b;

				if (delta > 1000/150) {
					b = a;    
				
					while( SDL_PollEvent( &e )) {
						switch (e.type) {
							case SDL_QUIT: {
								quit = true;
								break;
							}
							case SDL_KEYDOWN: {
								switch (e.key.keysym.sym) {
									case SDLK_ESCAPE: {
										quit = true;
									}
									case SDLK_SPACE: {
										std::cout << "warp" << std::endl;
										SDL_WarpMouseInWindow(window, WIN/2, WIN/2);
									}
								}
							}
							/*
							case SDL_MOUSEBUTTONDOWN: {
								int a,b;
								SDL_GetMouseState(&a, &b);
								P.setX(a);
								P.setY(b);
								break;
							}*/
							default: {
								break;
							}
						}
					}
					
					if(angle >180) {
						angle-=360;
					}

					if(angle<-180) {
						angle+=360;
					}

					//std::cout << angle << std::endl;

					//movement and rotate
					if(keyboardState[SDL_SCANCODE_LEFT]) {
							angle -= 1;
					}
					if(keyboardState[SDL_SCANCODE_RIGHT]) {
							angle += 1;
					}
					if(keyboardState[SDL_SCANCODE_W]) {
						P.setY(P.getY()-1);
					}
					if(keyboardState[SDL_SCANCODE_S]) {
						P.setY(P.getY()+1);
					}
					if(keyboardState[SDL_SCANCODE_A]) {
						P.setX(P.getX()-1);
					}
					if(keyboardState[SDL_SCANCODE_D]) {
						P.setX(P.getX()+1);
					}

					//update player position
					DC.updatePlayerPos(P.getX(), P.getY());

					//display player
					SDL_RenderClear(renderer);
					SDL_RenderCopyEx(renderer, DC.getImg(0), NULL, DC.getRect(0), angle, NULL, SDL_FLIP_NONE);
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