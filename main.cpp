#include "headers.h"

int main(int argc, char *args[])
{

	player P;
	bot B;
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
		M.initPath();					   // load map for pathfinding algorithm
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
				if (G.fpsCalc(&P, &B))
				{ // execute if correct fps
					while (SDL_PollEvent(C.getEvent()))
					{ // event handling
						quit = C.eventSwitch(&M, &P, &B);
					}
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
					SDL_RenderClear(renderer); // clear window with black

					P.checkAngle(); // keep angle in <-180;180>
					B.checkAngle();
					// SC.playsound(0);

					P.updateWobble();  // calculation and update for gun wobble
					P.updatePrevPos(); // save previous position to check if player moved in last frame
					B.updatePrevPos();
					C.mouseHandle(&P, &M); // mouse handling

					DC.updatePlayerPos(P.getX(), P.getY()); // update player position every frame for 2d view
					DC.updateBotPos(B.getX(), B.getY());	// update bot position every frame for 2d view

					float playerToBotAngle = atan2((P.getY() - B.getY()), (B.getX() - P.getX())) * 180 / M_PI;
					float playerToBotDist = sqrt(pow(P.getY() - B.getY(), 2) + pow(B.getX() - P.getX(), 2));

					float Lfov = P.floatAngle() + MAPSIZE / 2;
					float Rfov = P.floatAngle() - MAPSIZE / 2;

					if (B.getFollow())
					{
						B.setAngle(M.findPath(B.getY(), B.getX(), P.getY(), P.getX()));
						// std::cout << B.getAngle() << std::endl;
						B.calcRot(B.getAngle());
						//std::cout << B.getAngle() << " " << B.getVecX() << " " << B.getVecY() << std::endl;
						B.move(B.getVecX(), B.getVecY());
					}

					// fov is little streched and bot will be displayed when players fov is approaching it so it doesn't just pop at the side of the screen

					if (playerToBotAngle > 90 && Rfov < -180)
					{
						Lfov += 360;
						Rfov += 360;
					}

					if (playerToBotAngle < -90 && Lfov > 180)
					{
						Lfov -= 360;
						Rfov -= 360;
					}

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
							G.update(renderer, &P, &M, &DC, i, o, hitVec, playerToBotDist); // calculate and display walls for every wall hit
							hitVec.pop_back();
						}
						o++;
					}

					if (playerToBotAngle > Rfov && playerToBotAngle < Lfov)
					{
						Lfov -= Rfov;
						playerToBotAngle -= Rfov;
						SDL_Texture *txt = DC.getImg(6);
						SDL_Rect rect = DC.getRect(6);
						rect.h = (MAPSIZE * WINY) / playerToBotDist;
						rect.w = (MAPSIZE * WINY) / playerToBotDist;
						rect.x = M.angleDiffFix((1 - playerToBotAngle / Lfov) * WINY) - rect.w / 2;
						rect.y = WINY / 2 - rect.h / 2 + P.getPitch();
						SDL_RenderCopyEx(renderer, txt, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
					}

					DC.displayFurtherObjects(renderer);

					G.drawTwoDim(renderer, &M);					// draw 2D map
					DC.displayPlayerGunCross(renderer, &P, &B); // display gun, 2D player and crosshair
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					P.calcRot(0);
					C.kbHandle(&P, &B, &M, renderer); // keyboard handling
					SDL_RenderPresent(renderer);
				}
			}
		}
	}
	SDL_DestroyWindow(window); // Destroy window
	SDL_Quit();				   // Quit SDL subsystems
	return 0;
}