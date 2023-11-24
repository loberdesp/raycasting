#include "headers.h"

int main(int argc, char* args[])
{

	player P;
	controls C;
	map M;
	dispcontrol DC;

	//tmp wall
	
	M.addWall(0,0,WIN,WIN/25);
	M.addWall(0,WIN-WIN/25,WIN,WIN);
	M.addWall(0,WIN/25,WIN/25,WIN-WIN/25);
	M.addWall(WIN-WIN/25,WIN/25,WIN,WIN-WIN/25);
	M.addWall(WIN*5/10,WIN*7/10,WIN*6/10,WIN*8/10);
	
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
				//execute if correct fps
				if (DC.fpsCalc()) {

					//event handling
					while( SDL_PollEvent(C.getEvent())) {
						quit = C.eventSwitch();
					}
/*
					const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
					if(keyboard[SDL_SCANCODE_LSHIFT]) {
						SDL_WarpMouseInWindow(window, WIN / 2, WIN / 2);
					}
					int p = 0;
					int o = 0;
					SDL_GetRelativeMouseState(&p, &o);
					std::cout << p << " relative " << o << std::endl;
					SDL_GetGlobalMouseState(&p, &o);
					std::cout << p << " normal " << o << std::endl;
*/

					//keeping angle in <-180;180>
					P.checkAngle();
					P.calcRot(0);

					//player movement, rotation and collision detection passing player and map as argument by reference
					C.kbHandle(&P, &M);

					//add wall robi problemy bo tam jest int i jak jest male okno to cos sie psuje, naprawic to porzadnie
					//std::cout << M.isinWall(P.getX(), P.getY()) << std::endl;

					//update player position every frame
					DC.updatePlayerPos(P.getX(), P.getY());


					//black background display
					SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
					SDL_RenderClear(renderer);

					//lines display
					SDL_SetRenderDrawColor( renderer, 0, 255, 0, 0 );
					float a = 0;
					float b = 0;
					float wallH = 0;
					int o = 0;
					for(int i=500;i>=-500;i--) {
						a = P.getX();
						b = P.getY();
						P.calcRot(float(i)/10);
						M.getline(a,b,P.getVecX(),P.getVecY());
						if(i%100==0) {
							SDL_RenderDrawLine(renderer, P.getX(), WIN/2+P.getY()/2, a, WIN/2+b/2);
							std::cout << WIN/2+P.getY()/2 << std::endl;
						}
						//fix reverse fisheye
						float dist = sqrt(pow(a - P.getX(), 2) + pow(b - P.getY(), 2));
						dist = dist*cos(float(i)/10*M_PI/180);


						if(dist!=0) {
							wallH = (50*WIN)/dist;
							if(wallH>WIN) {
								wallH = WIN;
							}
						} else {
							wallH = WIN;
						}

						
						SDL_Rect r;
						r.x = o;
						r.y = (WIN/2-wallH/2)/2;
						r.w = 1;
						r.h = wallH/2;
						SDL_RenderFillRect( renderer, &r );
						o++;
						
					}
					
					//white walls display
					SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
					for(int i=0; i < M.getWallcount();i++) {
						SDL_RenderFillRect( renderer, M.getRect(i));
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