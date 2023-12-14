dispcontrol::dispcontrol()
{
    std::cout << "Created Display Controller!" << std::endl;
}

void dispcontrol::loadtextures(SDL_Renderer *render)
{

    int w, h, i; // texture width & height
    i = 0;
    // player txt
    images[i] = IMG_LoadTexture(render, "assets/img/player.png");
    SDL_QueryTexture(images[0], NULL, NULL, &w, &h);
    rects[i].x = WINY / 2 - PSIZE / 2;
    rects[i].y = WINY / 2 - PSIZE / 2;
    rects[i].w = PSIZE;
    rects[i].h = PSIZE;
    i++;



    images[i] = IMG_LoadTexture(render, "assets/img/duke.png");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    w *= 2;
    h *= 2;
    rects[i].x = WINX - w * 1.25;
    rects[i].y = WINY - h + 1;
    rects[i].w = w;
    rects[i].h = h;
    i++;



    images[i] = IMG_LoadTexture(render, "assets/img/wallbright.jpg");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    rects[i].x = 0;
    rects[i].y = 0;
    rects[i].w = TILESIZE / 8;
    rects[i].h = h;
    i++;



    images[i] = IMG_LoadTexture(render, "assets/img/wallshade.png");
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

void dispcontrol::handwobblesetrect(SDL_Rect& rect) {
    rect.x = rects[1].x;
    rect.y = rects[1].y;
    rect.w = rects[1].w;
    rect.h = rects[1].h;
}