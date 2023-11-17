dispcontrol::dispcontrol() {
    std::cout << "Created Display Controller!" << std::endl;
}

void dispcontrol::loadtextures(SDL_Renderer *render) {

    int w, h; // texture width & height

    //player txt
    images[0] = IMG_LoadTexture(render, "../assets/player.png");
    SDL_QueryTexture(images[0], NULL, NULL, &w, &h);
    rects[0].x = WIN/2 - PSIZE/2;
    rects[0].y = WIN/2 - PSIZE/2;
    rects[0].w = PSIZE;
    rects[0].h = PSIZE;
}




SDL_Texture* dispcontrol::getImg(int i) {
    return images[i];
}




SDL_Rect* dispcontrol::getRect(int i) {
    return &rects[i];
}

void dispcontrol::updatePlayerPos(int x, int y) {
    rects[0].x = x - PSIZE/2;
    rects[0].y = y - PSIZE/2;
}


bool dispcontrol::fpsCalc() {
    a = SDL_GetTicks();
	delta = a - b;
    //fps value
    if(delta > 1000/150.0) {
        b = a;
        return true;
    } else {
        return false;
    }
}