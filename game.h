class game {



    public:
        void update(SDL_Renderer* renderer, player* P, map* M, dispcontrol* DC, float a, float b, int i, float& wallH, int o, float hor);
        void drawFloor(SDL_Renderer* renderer, player* P, float wallH, int o);
};