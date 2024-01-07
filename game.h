class game {

    int fps;
    std::chrono::steady_clock::time_point fpsA, fpsB;
    std::chrono::duration<double> fpsDelta, desiredFpsDelta;



    public:
        game();
        void update(SDL_Renderer* renderer, player* P, map* M, dispcontrol* DC, int i, int o, std::vector<std::vector<float>> &vec);
        void drawFloor(SDL_Renderer* renderer, player* P, float wallH, int o);
        void drawCeiling(SDL_Renderer* renderer, player* P, float wallH, int o);
        void drawTwoDim(SDL_Renderer* renderer, map* M);
        bool fpsCalc(player *P);
};