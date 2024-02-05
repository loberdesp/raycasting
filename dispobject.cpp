dispobject::dispobject(float dist, SDL_Texture *txt, SDL_Rect srcRect, SDL_Rect dstRect)
{

    distance = dist;
    srcRectangle = srcRect;
    texture = txt;
    dstRectangle = dstRect;
}

float dispobject::getDistance()
{
    return distance;
}

SDL_Rect *dispobject::getDstRect()
{
    return &dstRectangle;
}

SDL_Rect *dispobject::getSrcRect()
{
    return &srcRectangle;
}

SDL_Texture *dispobject::getTexture()
{
    return texture;
}

void dispobject::check()
{
    // std::cout << dstRectangle->y << std::endl;
}