void game::update(SDL_Renderer* renderer, player* P, map* M, dispcontrol* DC, float a, float b, int i, float& wallH, int o, float hor) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
	SDL_RenderDrawLine(renderer, P->getX(), P->getY(), a, b);


	float dist = sqrt(pow(a - P->getX(), 2) + pow(b - P->getY(), 2));
	dist = dist * cos(i * M_PI / (180 * 8));
	wallH = (MAPSIZE * WINY) / dist;

	SDL_Rect tmpRect;
	int ratio = M->checkBlock((a + P->getVecX()) * MAPSIZE / WINY, (b - P->getVecY()) * MAPSIZE / WINY) % 10;
	tmpRect = M->rayWall(wallH, P->getPitch(), o, ratio);

						// shades when wall is hit vertically
	if (hor) {
		float diff = (a * MAPSIZE / 8) / WINY - int((a * MAPSIZE / 8) / WINY);
		DC->setRect(2, diff * 2074, ratio);
		SDL_RenderCopyEx(renderer, DC->getImg(2), DC->getRect(2), &tmpRect, 0, NULL, SDL_FLIP_NONE);
	} else {
	    float diff = (b * MAPSIZE / 8) / WINY - int((b * MAPSIZE / 8) / WINY);
		DC->setRect(3, diff * 2074, ratio);
		SDL_RenderCopyEx(renderer, DC->getImg(3), DC->getRect(3), &tmpRect, 0, NULL, SDL_FLIP_NONE);
	}
}

void game::drawFloor(SDL_Renderer* renderer, player* P, float wallH, int o) {
	SDL_Rect rfloor;
	rfloor.x = WINY + o * TILESIZE / 8;
	rfloor.y = (WINY / 2 + wallH / 2) + P->getPitch() - 1;
	rfloor.w = TILESIZE / 8;
	rfloor.h = WINY - rfloor.y;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rfloor);
}