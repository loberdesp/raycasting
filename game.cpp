void game::update(SDL_Renderer *renderer, player *P, map *M, dispcontrol *DC, float a, float b, int i, float &wallH, int o, float hor)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
	SDL_RenderDrawLine(renderer, P->getX(), P->getY(), a, b);

	float dist = sqrt(pow(a - P->getX(), 2) + pow(b - P->getY(), 2));
	dist = dist * cos(i * M_PI / (180 * 8));
	wallH = (MAPSIZE * WINY) / dist;

	SDL_Rect tmpRect;
	int ratio = M->checkBlock((a + P->getVecX()) * MAPSIZE / WINY, (b - P->getVecY()) * MAPSIZE / WINY) % 10;
	tmpRect = M->rayWall(wallH, P->getPitch(), o, ratio);






	float ray = FOV * (floor(0.5f * WINY) - o) / (WINY - 1);
	float rayidk = 0.5f * tan(ray * (M_PI / 180)) / tan(0.5f * FOV * M_PI / 180);
	short posit = static_cast<short>(round(WINY * (0.5f - rayidk)));
	tmpRect.x = posit + WINY;

	if (o < FOV * 8)
	{
		float raynext = FOV * (floor(0.5f * WINY) - o + 1) / (WINY - 1);
		float rayidknext = 0.5f * tan(raynext * (M_PI / 180)) / tan(0.5f * FOV * M_PI / 180);
		short positnext = static_cast<short>(round(WINY * (0.5f - rayidknext)));
		// tmpRect.w = std::max(1, positnext - posit);
		if (posit - positnext > 1)
		{


		}
	}

	// uber dirty fix for my problem
	// tmpRect.w = 2;







	DC->wallImgCalc(hor, a, b, ratio);
	// DC->fog(dist, hor);

	SDL_RenderCopyEx(renderer, DC->getImg(2), DC->getRect(2), &tmpRect, 0, NULL, SDL_FLIP_NONE);
}










void game::drawFloor(SDL_Renderer *renderer, player *P, float wallH, int o)
{
	SDL_Rect rfloor;
	rfloor.x = WINY + o * TILESIZE / 8;
	rfloor.y = (WINY / 2 + wallH / 2) + P->getPitch() - 1;
	rfloor.w = TILESIZE / 8;
	rfloor.h = WINY - rfloor.y;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rfloor);
}

void game::drawCeiling(SDL_Renderer *renderer, player *P, float wallH, int o)
{
	SDL_Rect rceiling;
	rceiling.x = WINY + o * TILESIZE / 8;
	rceiling.y = 0;
	rceiling.w = TILESIZE / 8;
	rceiling.h = (WINY / 2 - wallH / 2) + P->getPitch() + 1;
	SDL_SetRenderDrawColor(renderer, 0, 123, 143, 255);
	SDL_RenderFillRect(renderer, &rceiling);
}

void game::drawTwoDim(SDL_Renderer *renderer, map *M)
{
	for (int i = 0; i < MAPSIZE; i++)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, i * TILESIZE, 0, i * TILESIZE, WINY - TILESIZE);
		SDL_RenderDrawLine(renderer, 0, i * TILESIZE, WINY - TILESIZE, i * TILESIZE);

		SDL_Rect r;
		r.w = TILESIZE;
		r.h = TILESIZE;

		for (int j = 0; j < MAPSIZE; j++)
		{
			if (M->checkBlock(i, j) != 0)
			{
				r.x = i * TILESIZE;
				r.y = j * TILESIZE;

				if (M->checkBlock(i, j) % 10 == 0)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
				}
				SDL_RenderFillRect(renderer, &r);
			}
		}
	}
}