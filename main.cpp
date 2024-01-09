#include "headers.h"

int main(int argc, char *args[])
{

	player P;
	controls C;
	map M;
	dispcontrol DC;
	game G;
	// soundcontrol SC;

	// define win and rend
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		// Create window and renderer
		window = SDL_CreateWindow("RAYCAST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINX, WINY, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		SDL_SetRelativeMouseMode(SDL_TRUE); // Enable relative mouse mode

		M.initMap();					   // load array map
		DC.loadtextures(renderer, window); // load textures
		// SC.loadsounds();

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{

			bool quit = false;

			while (quit == false)
			{
				if (G.fpsCalc(&P))
				{ // execute if correct fps
					while (SDL_PollEvent(C.getEvent()))
					{ // event handling
						quit = C.eventSwitch();
					}

					P.checkAngle(); // keep angle in <-180;180>
					// SC.playsound(0);
					P.updatePrevPos();	   // save previous position to check if player moved in last frame
					C.kbHandle(&P, &M);	   // keyboard handling
					P.updateWobble();	   // calculation and update for gun wobble
					C.mouseHandle(&P, &M); // mouse handling

					DC.updatePlayerPos(P.getX(), P.getY()); // update player position every frame

					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
					SDL_RenderClear(renderer); // clear window with black

					float o = 0;
					float hor = 0;

					for (int i = MAPSIZE * 4; i >= -MAPSIZE * 4; i--)
					{ // fov loop

						float a = P.getX();
						float b = P.getY();

						P.calcRot(float(i) / 8);
						std::vector<std::vector<float>> hitVec; // vector of all wall hits on specific ray path
						std::vector<float> bs(7, 99);
						hitVec.push_back(bs);

						M.getline(a, b, P.getVecX(), P.getVecY(), hor, hitVec); // calculate all hits

						while (hitVec.size() > 1)
						{
							G.update(renderer, &P, &M, &DC, i, o, hitVec); // calculate and display walls for every wall hit
							hitVec.pop_back();
						}
						o++;
					}

					G.drawTwoDim(renderer, &M);				// draw 2D map
					DC.displayPlayerGunCross(renderer, &P); // display gun, 2D player and crosshair
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					M.newCol(&P, renderer);
					SDL_RenderPresent(renderer);
				}
			}
		}
	}
	SDL_DestroyWindow(window); // Destroy window
	SDL_Quit();				   // Quit SDL subsystems
	return 0;
}