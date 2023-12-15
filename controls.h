class controls {
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    SDL_Event e;


    public:
        controls();
        bool eventSwitch();
        SDL_Event* getEvent();
        void kbHandle(player* P, map* M);
        void mouseHandle(player* P, map* M);
};