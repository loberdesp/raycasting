#include "headers.h"

int main(int argc, char *args[])
{

	player P;
	controls C;
	map M;
	dispcontrol DC;
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
					bool hor;
					for (int i = MAPSIZE * 4; i >= -MAPSIZE * 4; i--)
					{
						a = P.getX();
						b = P.getY();
						P.calcRot(float(i) / 8);
						M.getline(a, b, P.getVecX(), P.getVecY(), hor);

						// jeśli ściana%10 != 0 to wtedy promień przechodzi dalej, w funkcji odpala się kolejna iteracja aż nie trafi na ściana%10==0

						SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
						SDL_RenderDrawLine(renderer, P.getX(), P.getY(), a, b);

						float dist = sqrt(pow(a - P.getX(), 2) + pow(b - P.getY(), 2));
						dist = dist * cos(i * M_PI / (180 * 8));
						wallH = (MAPSIZE * WINY) / dist;

						SDL_Rect tmpRect;
						int ratio = M.checkBlock((a + P.getVecX()) * MAPSIZE / WINY, (b - P.getVecY()) * MAPSIZE / WINY) % 10;
						tmpRect = M.rayWall(wallH, P.getPitch(), o, ratio);

						// shades when wall is hit vertically
						if (hor)
						{
							float diff = (a * MAPSIZE / 8) / WINY - int((a * MAPSIZE / 8) / WINY);
							DC.setRect(2, diff * 2074, ratio);
							SDL_RenderCopyEx(renderer, DC.getImg(2), DC.getRect(2), &tmpRect, 0, NULL, SDL_FLIP_NONE);
						}
						else
						{
							float diff = (b * MAPSIZE / 8) / WINY - int((b * MAPSIZE / 8) / WINY);
							DC.setRect(3, diff * 2074, ratio);
							SDL_RenderCopyEx(renderer, DC.getImg(3), DC.getRect(3), &tmpRect, 0, NULL, SDL_FLIP_NONE);
						}

						// floor
						SDL_Rect rfloor;
						rfloor.x = WINY + o * TILESIZE / 8;
						rfloor.y = (WINY / 2 + wallH / 2) + P.getPitch() - 1;
						rfloor.w = TILESIZE / 8;
						rfloor.h = WINY - rfloor.y;
						SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
						SDL_RenderFillRect(renderer, &rfloor);

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
								SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
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