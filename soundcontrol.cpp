soundcontrol::soundcontrol() {
    SDL_Init(SDL_INIT_AUDIO);

    if(Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096)!=0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open audio: %s\n", Mix_GetError());
        exit(-1);
    }
}

void soundcontrol::addsound(const char* filename) {
    Mix_Chunk* chunk = Mix_LoadWAV(filename);
    if(chunk == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load audio: %s\n", Mix_GetError());
        exit(-1);
    }
    sounds.push_back(chunk);
    volumes.push_back(1);
}

void soundcontrol::playsound(int index) {
    Mix_Volume(-1, volumes[index]);
    Mix_PlayChannel(-1, sounds[index], 0);
}

void soundcontrol::loadsounds() {
    addsound("../assets/sounds/s.wav");
}