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
				
				// execute if correct fps
				if (G.fpsCalc())
				{
					

					// event handling
					while (SDL_PollEvent(C.getEvent()))
					{
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

					// poor textured floor attempt

					// float vertical_fov_ratio = tan(M_PI * 0.5f * FOV / 180);
					// float floor_start = (WINY / 2 + wallH / 2) + P.getPitch();
					// float start_stripe_x = -tan(0.5f * FOV * M_PI / 180);
					// float end_stripe_x = vertical_fov_ratio * (1 - 2.f / WINY);

					// float ray_direction_end_x = cos(P.getVecX() * M_PI / 180) + end_stripe_x * cos(M_PI / 180 * (P.getVecX() - 90));
					// float ray_direction_end_y = -sin(P.getVecX() * M_PI / 180) - end_stripe_x * sin(M_PI / 180 * (P.getVecX() - 90));
					// float ray_direction_start_x = cos(P.getVecX() * M_PI / 180) + start_stripe_x * cos(M_PI / 180 * (P.getVecX() - 90));
					// float ray_direction_start_y = -sin(P.getVecX() * M_PI / 180) - start_stripe_x * sin(M_PI / 180 * (P.getVecX() - 90));

					// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

					// for(int af = floor_start; af < WINY; af++) {

					// 	float floor_step_x;
					// 	float floor_step_y;
					// 	float floor_x;
					// 	float floor_y;
					// 	float row_distance;

					// 	int row_y = af - floor_start;

					// 	row_distance = (0 == row_y) ? FLT_MAX : (WINY/2) / (row_y * vertical_fov_ratio);
					// 	//std::cout << row_distance << std::endl;

					// 	floor_step_x = row_distance * (ray_direction_end_x - ray_direction_start_x) / WINY;
					// 	floor_step_y = row_distance * (ray_direction_end_y - ray_direction_start_y) / WINY;
					// 	floor_x = 0.5f + P.getX() + ray_direction_start_x * row_distance;
					// 	floor_y = 0.5f + P.getY() + ray_direction_start_y * row_distance;

					// }

					float o = 0;
					float hor = 0;

					for (int i = MAPSIZE*4; i >= -MAPSIZE*4; i--) {
					float a = P.getX();
					float b = P.getY();
					P.calcRot(float(i) / 8);
					std::vector<std::vector<float>> hitVec;
					std::vector<float> bs(7, 99);
					hitVec.push_back(bs);
					M.getline(a, b, P.getVecX(), P.getVecY(), hor, hitVec);
					SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
					while (hitVec.size() > 1)
					{
						// if (hitVec.size() > 2 && hitVec.size() % 2 == 1)
						// {
							// G.update(renderer, &P, &M, &DC, i, o, hitVec);
							// int yTop = hitVec.back()[6];
							// hitVec.pop_back();
							// G.update(renderer, &P, &M, &DC, i, o, hitVec);
							// int yBot = hitVec.back()[6];
							// hitVec.pop_back();
							// SDL_RenderDrawLine(renderer, o+WINY, yTop, o+WINY, yBot);
						// }
						// else
						// {
							G.update(renderer, &P, &M, &DC, i, o, hitVec);
							hitVec.pop_back();
						// }
					}
					o++;
					}

					G.drawTwoDim(renderer, &M);
					DC.displayPlayerGunCross(renderer, &P);
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