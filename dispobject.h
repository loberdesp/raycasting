class dispobject
{
    SDL_Rect srcRectangle;
    SDL_Rect dstRectangle;
    SDL_Texture *texture;
    float distance;

public:
    dispobject(float dist, SDL_Texture *texture, SDL_Rect srcrect, SDL_Rect dstrec);
    float getDistance();
    SDL_Rect *getDstRect();
    SDL_Texture *getTexture();
    SDL_Rect *getSrcRect();
    void check();
    
};