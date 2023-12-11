class map {
    std::vector<std::vector<int>> mapVector = std::vector<std::vector<int>>(MAPSIZE, std::vector<int> (MAPSIZE,0));
    std::vector<SDL_Rect> wallVec;

    
    public:
        map();
        void initMap();
        void addWall(int x1, int y1);
        int getWallcount();
        SDL_Rect *getRect(int i);
        bool isinWall(float x, float y);
        void checkCol(float x, float y, float vx, float vy, bool &colX, bool &colY);
        void getline(float &x, float &y, float vx, float vy, bool &horizontal);
        int checkBlock(int x, int y);
        SDL_Rect rayWall(int h, float pitch, int k, int ratio);
};