dispcontrol::dispcontrol()
{
    std::cout << "Created Display Controller!" << std::endl;
}

void dispcontrol::loadtextures(SDL_Renderer *render)
{

    int w, h, i; // texture width & height
    i = 0;
    // player txt
    images[i] = IMG_LoadTexture(render, "../assets/img/player.png");
    SDL_QueryTexture(images[0], NULL, NULL, &w, &h);
    rects[i].x = WINY / 2 - PSIZE / 2;
    rects[i].y = WINY / 2 - PSIZE / 2;
    rects[i].w = PSIZE;
    rects[i].h = PSIZE;
    i++; 



    images[i] = IMG_LoadTexture(render, "../assets/img/duke.png");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    w *= 2;
    h *= 2;
    rects[i].x = WINX - w * 1.25;
    rects[i].y = WINY - h + 1;
    rects[i].w = w;
    rects[i].h = h;

    gunPos.x = WINX - w * 1.25;
    gunPos.y = WINY - h + 1;
    gunPos.w = w;
    gunPos.h = h;
    i++;



    images[i] = IMG_LoadTexture(render, "../assets/img/wallbright.jpg");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    rects[i].x = 0;
    rects[i].y = 0;
    rects[i].w = TILESIZE / 8;
    rects[i].h = h;
    i++;

}

SDL_Texture *dispcontrol::getImg(int i)
{
    return images[i];
}

SDL_Rect *dispcontrol::getRect(int i)
{
    return &rects[i];
}

void dispcontrol::updatePlayerPos(int x, int y)
{
    rects[0].x = x - PSIZE / 2;
    rects[0].y = y - PSIZE / 2;
}

bool dispcontrol::fpsCalc()
{
    a = SDL_GetTicks();
    delta = a - b;
    // fps value
    if (delta > 1000 / 150.0)
    {
        b = a;
        return true;
    }
    else
    {
        return false;
    }
}

void dispcontrol::setRect(int i, int x, int ratio)
{
    rects[i].x = x;
    rects[i].y = 0;

    if (ratio != 0) {
        rects[i].y = rects[i].h - rects[i].h*ratio/10;
    }
}

SDL_Rect* dispcontrol::setGunPos(int x, int y) {
    gunPos.x = rects[1].x + x;
    gunPos.y = rects[1].y - y;
    gunPos.w = rects[1].w;
    gunPos.h = rects[1].h;
    return &gunPos;
}


void dispcontrol::darkenTexture(int i, int r, int g, int b) {
    SDL_SetTextureColorMod(images[i], r, g, b);
}


void dispcontrol::wallImgCalc(bool hor, float a, float b, int ratio) {
    float diff = 0;
    if (hor) {
		diff = (a * MAPSIZE / 8) / WINY - int((a * MAPSIZE / 8) / WINY);
	} else {
		diff = (b * MAPSIZE / 8) / WINY - int((b * MAPSIZE / 8) / WINY);
	}

    rects[2].x = diff*rects[2].h;
    rects[2].y = 0;

    if (ratio != 0) {
        rects[2].y = rects[2].h - rects[2].h*ratio/10;
    }
}

void dispcontrol::fog(float d) {
    if (d > WINY/5) 
	{
		int dim = WINY/5 - d;

		dim += 255;
		if(dim <= 0) {
			dim = 0;
		}
        SDL_SetTextureColorMod(images[2], dim, dim, dim);
	} else {
		SDL_SetTextureColorMod(images[2], 255, 255, 255);
	}
}