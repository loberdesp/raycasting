class dispcontrol
{

    SDL_Texture *images[10];
    SDL_Rect rects[10];
    SDL_Rect gunPos;
    SDL_Surface *icon;
    std::vector<dispobject> dispObjects;

public:
    dispcontrol();
    void loadtextures(SDL_Renderer *render, SDL_Window *window);
    SDL_Texture *getImg(int i);
    SDL_Rect getRect(int i);
    void updatePlayerPos(int x, int y);
    void updateBotPos(int x, int y);
    void updateGun(float a);
    void setRect(int i, int x, int ratio);
    SDL_Rect *setGunPos(int x, int y);
    void darkenTexture(int i, int r, int g, int b);
    void wallImgCalc(int ratio, int txtVal, std::vector<std::vector<float>> &vec);
    void fog(float d, bool hor, int txtVal);
    void displayPlayerGunCross(SDL_Renderer *render, player *P, bot *B);
    void pushDispObj(dispobject ob);
    void displayFurtherObjects(SDL_Renderer* render);
};