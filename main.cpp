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

		M.initMap();			   // load array map
		DC.loadtextures(renderer); // load textures
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
				// execute if correct fps
				if (DC.fpsCalc())
				{

					// event handling
					while (SDL_PollEvent(C.getEvent()))
					{
						quit = C.eventSwitch(); 
					}

					P.checkAngle(); // keep angle in <-180;180>
					P.calcRot(0);	// forward movement reset
					// SC.playsound(0);

					P.updatePrevPos();	   // save previous position to check if player moved in last frame
					C.kbHandle(&P, &M);	   // keyboard handling
					P.updateWobble();	   // calculation and update for gun wobble
					C.mouseHandle(&P, &M); // mouse handling

					DC.updatePlayerPos(P.getX(), P.getY()); // update player position every frame

					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
					SDL_RenderClear(renderer); // clear window with black

					float a, b, wallH, o = 0;
					float hor;
					for (int i = MAPSIZE * 4; i >= -MAPSIZE * 4; i--) {  	// fov loop
						a = P.getX();
						b = P.getY();
						P.calcRot(float(i) / 8);
						std::vector<std::vector<float>> hitVec;
						std::vector<float> tmp(5, 99);
						hitVec.push_back(tmp);

						if (M.getline(a, b, P.getVecX(), P.getVecY(), hor, hitVec)) {
							G.update(renderer, &P, &M, &DC, hitVec.back()[0], hitVec.back()[1], i, wallH, o, hitVec.back()[2]);
							hitVec.pop_back();

							G.drawFloor(renderer, &P, wallH, o);
							G.drawCeiling(renderer, &P, wallH, o);

							if (hitVec.size() != 1)
							{
								while (hitVec.size() > 1)
								{
									G.update(renderer, &P, &M, &DC, hitVec.back()[0], hitVec.back()[1], i, wallH, o, hitVec.back()[2]);
									hitVec.pop_back();
								}
							}
						} else {
							G.update(renderer, &P, &M, &DC, a, b, i, wallH, o, hor);
							G.drawFloor(renderer, &P, wallH, o);
							G.drawCeiling(renderer, &P, wallH, o);
						}
						o++;
					}

					G.drawTwoDim(renderer, &M);

					// player display
					SDL_RenderCopyEx(renderer, DC.getImg(0), NULL, DC.getRect(0), -P.getAngle(), NULL, SDL_FLIP_NONE);

					// gun display
					SDL_RenderCopyEx(renderer, DC.getImg(1), NULL, DC.setGunPos(P.getHandMoveX(), P.getHandMoveY()), 0, NULL, SDL_FLIP_NONE);

					// crosshair display
					SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
					SDL_RenderDrawLine(renderer, 3 * WINY / 2 - 5, WINY / 2 - 5, 3 * WINY / 2 + 5, WINY / 2 + 5);
					SDL_RenderDrawLine(renderer, 3 * WINY / 2 - 5, WINY / 2 + 5, 3 * WINY / 2 + 5, WINY / 2 - 5);

					SDL_RenderPresent(renderer);
				}
			}
		}
	}

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}