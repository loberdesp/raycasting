class controls {
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    SDL_Event e;


    public:
        controls();
        bool eventSwitch(map *M, player *P, bot *B);
        SDL_Event* getEvent();
        void kbHandle(player* P, bot* B, map* M, SDL_Renderer *renderer);
        void mouseHandle(player* P, map* M);
};