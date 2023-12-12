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

		// hidden mouse and relative movement
		SDL_SetRelativeMouseMode(SDL_TRUE);

		// Load stuff
		M.initMap();
		DC.loadtextures(renderer);
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

					// keeping angle in <-180;180> and calculation for straight movement
					P.checkAngle();
					P.calcRot(0);

					// do working step sounds and gun movement
					// SC.playsound(0);

					// player movement, rotation and collision detection passing player and map as argument by reference
					C.kbHandle(&P, &M);
					C.mouseHandle(&P, &M);

					// update player position every frame
					DC.updatePlayerPos(P.getX(), P.getY());

					// black background display
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
					SDL_RenderClear(renderer);

					float a, b, wallH, o = 0;
					float hor;
					for (int i = MAPSIZE * 4; i >= -MAPSIZE * 4; i--)
					{
						a = P.getX();
						b = P.getY();
						P.calcRot(float(i) / 8);
						std::vector<std::vector<float>> hitVec;
						std::vector<float> tmp(5, 99);
						hitVec.push_back(tmp);

						// jeśli ściana%10 != 0 to wtedy promień przechodzi dalej, w funkcji odpala się kolejna iteracja aż nie trafi na ściana%10==0

						// while(M.getline(a, b, P.getVecX(), P.getVecY(), hor, hitVec)) {
						// 	G.update(renderer, &P, &M, &DC, a, b, i, wallH, o, hor);
						// }

						if (M.getline(a, b, P.getVecX(), P.getVecY(), hor, hitVec)) {

							G.update(renderer, &P, &M, &DC, hitVec.back()[0], hitVec.back()[1], i, wallH, o, hitVec.back()[2]);
							hitVec.pop_back();

							G.drawFloor(renderer, &P, wallH, o);

							if (hitVec.size() != 1)
							{
								while (hitVec.size() > 1)
								{
									G.update(renderer, &P, &M, &DC, hitVec.back()[0], hitVec.back()[1], i, wallH, o, hitVec.back()[2]);
									hitVec.pop_back();
								}
							}
						}
						else
						{
							G.update(renderer, &P, &M, &DC, a, b, i, wallH, o, hor);
							G.drawFloor(renderer, &P, wallH, o);
						}

						// ceiling
						SDL_Rect rceiling;
						rceiling.x = WINY + o * TILESIZE / 8;
						rceiling.y = -1;
						rceiling.w = TILESIZE / 8;
						rceiling.h = (WINY / 2 - wallH / 2) + P.getPitch() + 1;
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
						SDL_RenderFillRect(renderer, &rceiling);
						o++;
					}

					// grid display
					for (int i = 0; i < MAPSIZE; i++)
					{
						SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
						SDL_RenderDrawLine(renderer, i * TILESIZE, 0, i * TILESIZE, WINY - TILESIZE);
						SDL_RenderDrawLine(renderer, 0, i * TILESIZE, WINY - TILESIZE, i * TILESIZE);
					}

					for (int i = 0; i < MAPSIZE; i++)
					{
						SDL_Rect r;
						r.w = TILESIZE;
						r.h = TILESIZE;

						for (int j = 0; j < MAPSIZE; j++)
						{
							if (M.checkBlock(i, j) != 0)
							{
								r.x = i * TILESIZE;
								r.y = j * TILESIZE;

								if(M.checkBlock(i, j) % 10 == 0) {
									SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
								} else {
									SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
								}
								SDL_RenderFillRect(renderer, &r);
							}
						}
					}
					// player display
					SDL_RenderCopyEx(renderer, DC.getImg(0), NULL, DC.getRect(0), -P.getAngle(), NULL, SDL_FLIP_NONE);
					SDL_RenderCopyEx(renderer, DC.getImg(1), NULL, DC.getRect(1), 0, NULL, SDL_FLIP_NONE);
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