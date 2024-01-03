void game::update(SDL_Renderer *renderer, player *P, map *M, dispcontrol *DC, int i, int o, std::vector<std::vector<float>> &vec)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
	SDL_RenderDrawLine(renderer, P->getX(), P->getY(), vec.back()[0], vec.back()[1]);

	float dist = sqrt(pow(vec.back()[0] - P->getX(), 2) + pow(vec.back()[1] - P->getY(), 2));
	dist *= cos(i * M_PI / (180 * 8));
	vec.back()[5] = (MAPSIZE * WINY) / dist;

	SDL_Rect tmpRect;
	int blockVal = M->checkBlock((vec.back()[0] + P->getVecX()) * MAPSIZE / WINY, (vec.back()[1] - P->getVecY()) * MAPSIZE / WINY);
	int ratio = blockVal % 10;
	int txtVal = 1+blockVal/10;
	tmpRect = M->rayWall(vec.back()[5], P->getPitch(), o, ratio);

	if (o < FOV * 8) {
		tmpRect.w = std::max(1, M->angleDiffFix(o+1) - M->angleDiffFix(o));
	}

	DC->wallImgCalc(ratio, txtVal, vec);
	DC->fog(dist, vec.back()[2], txtVal);

	SDL_RenderCopyEx(renderer, DC->getImg(txtVal), DC->getRect(txtVal), &tmpRect, 0, NULL, SDL_FLIP_NONE);
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