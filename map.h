class map {
    std::vector<std::vector<int>> mapVector = std::vector<std::vector<int>>(WIN, std::vector<int> (WIN,0));
    std::vector<SDL_Rect> wallVec;

    
    public:
        map();
        void addWall(int x1, int y1, int x2, int y2);
        int getWallcount();
        SDL_Rect *getRect(int i);
};