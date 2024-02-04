dispcontrol::dispcontrol()
{
    std::cout << "Created Display Controller!" << std::endl;
}

void dispcontrol::loadtextures(SDL_Renderer *render, SDL_Window *window)
{
    //load window icon
    icon = SDL_LoadBMP("../assets/img/icon.bmp");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    int w, h, i; // texture width & height
    i = 0;
    // player txt
    images[i] = IMG_LoadTexture(render, "../assets/img/player.png");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    rects[i].x = WINY / 2 - PSIZE / 2;
    rects[i].y = WINY / 2 - PSIZE / 2;
    rects[i].w = PSIZE;
    rects[i].h = PSIZE;
    i++;

    images[i] = IMG_LoadTexture(render, "../assets/img/shotgun.png");
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

    images[i] = IMG_LoadTexture(render, "../assets/img/brickwall.jpg");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    rects[i].x = 0;
    rects[i].y = 0;
    rects[i].w = TILESIZE / 8;
    rects[i].h = h;
    i++;

    images[i] = IMG_LoadTexture(render, "../assets/img/dawidos.jpg");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    rects[i].x = 0;
    rects[i].y = 0;
    rects[i].w = TILESIZE / 8;
    rects[i].h = h;
    i++;

    images[i] = IMG_LoadTexture(render, "../assets/img/plantwall.jpg");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    rects[i].x = 0;
    rects[i].y = 0;
    rects[i].w = TILESIZE / 8;
    rects[i].h = h;
    i++;

    images[i] = IMG_LoadTexture(render, "../assets/img/bot.png");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    rects[i].x = WINY / 2 - PSIZE / 2;
    rects[i].y = WINY / 2 - PSIZE / 2;
    rects[i].w = PSIZE;
    rects[i].h = PSIZE;
    i++;

    images[i] = IMG_LoadTexture(render, "../assets/img/botskin.png");
    SDL_QueryTexture(images[i], NULL, NULL, &w, &h);
    rects[i].x = 0;
    rects[i].y = WINY/2 - h/2;
    rects[i].w = w;
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

void dispcontrol::updateBotPos(int x, int y)
{
    rects[5].x = x - PSIZE / 2;
    rects[5].y = y - PSIZE / 2;
}


void dispcontrol::setRect(int i, int x, int ratio)
{
    rects[i].x = x;
    rects[i].y = 0;

    if (ratio != 0)
    {
        rects[i].y = rects[i].h - rects[i].h * ratio / 10;
    }
}

SDL_Rect *dispcontrol::setGunPos(int x, int y)
{
    gunPos.x = rects[1].x + x;
    gunPos.y = rects[1].y - y;
    gunPos.w = rects[1].w;
    gunPos.h = rects[1].h;
    return &gunPos;
}

void dispcontrol::darkenTexture(int i, int r, int g, int b)
{
    SDL_SetTextureColorMod(images[i], r, g, b);
}

void dispcontrol::wallImgCalc(int ratio, int txtVal, std::vector<std::vector<float>> &vec)
{
    float diff = 0;
    if (vec.back()[2])
    {
        diff = (vec.back()[0] * MAPSIZE / 8) / WINY - int((vec.back()[0] * MAPSIZE / 8) / WINY);
    }
    else
    {
        diff = (vec.back()[1] * MAPSIZE / 8) / WINY - int((vec.back()[1] * MAPSIZE / 8) / WINY);
    }

    rects[txtVal].x = diff * rects[txtVal].h;
    rects[txtVal].y = 0;

    if (ratio != 0)
    {
        rects[txtVal].y = rects[txtVal].h - rects[txtVal].h * ratio / 10;
    }
}

void dispcontrol::fog(float d, bool hor, int txtVal)
{
    if (d > WINY / 2)
    {
        int dim = WINY / 2 - d;

        dim += 255;

        if (dim <= 0)
        {
            dim = 0;
        }
        if (!hor && dim >= 155)
        {
            SDL_SetTextureColorMod(images[txtVal], 155, 155, 155);
        }
        else
        {
            SDL_SetTextureColorMod(images[txtVal], dim, dim, dim);
        }
    }
    else
    {
        if (hor)
        {
            SDL_SetTextureColorMod(images[txtVal], 255, 255, 255);
        }
        else
        {
            SDL_SetTextureColorMod(images[txtVal], 155, 155, 155);
        }
    }
}

void dispcontrol::displayPlayerGunCross(SDL_Renderer *render, player *P, bot *B)
{
    // entities display
    SDL_RenderCopyEx(render, images[0], NULL, &rects[0], -P->getAngle(), NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(render, images[5], NULL, &rects[5], -B->getAngle() + 90, NULL, SDL_FLIP_NONE);
    

    // gun display

    SDL_RenderCopyEx(render, images[1], NULL, setGunPos(P->getHandMoveX(), P->getHandMoveY()), 0, NULL, SDL_FLIP_NONE);

    // crosshair display
    SDL_SetRenderDrawColor(render, 0, 255, 255, 255);
    SDL_RenderDrawLine(render, 3 * WINY / 2 - 5, WINY / 2 - 5, 3 * WINY / 2 + 5, WINY / 2 + 5);
    SDL_RenderDrawLine(render, 3 * WINY / 2 - 5, WINY / 2 + 5, 3 * WINY / 2 + 5, WINY / 2 - 5);
}