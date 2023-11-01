class dispcontrol {

    SDL_Texture *images[10];
    SDL_Rect rects[10];


    public:
        dispcontrol();
        void loadtextures(SDL_Renderer *render);
        SDL_Texture *getImg(int i);
        SDL_Rect* getRect(int i);
        void updatePlayerPos(int x, int y);
};