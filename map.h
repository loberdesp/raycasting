class map
{
    std::vector<std::vector<int>> mapVector = std::vector<std::vector<int>>(MAPSIZE, std::vector<int>(MAPSIZE));
    std::vector<SDL_Rect> wallVec;
    pathFinder pf;
    int grid[ROW][COL];

public:
    map();
    void initMap();
    void initPath();
    void findPath(int srcY, int srcX, int destY, int destX);
    void addWall(int x1, int y1);
    int getWallcount();
    SDL_Rect *getRect(int i);
    bool isinWall(float x, float y);
    void checkCol(float x, float y, float vx, float vy, bool &colX, bool &colY);
    bool getline(float &x, float &y, float vx, float vy, float &horizontal, std::vector<std::vector<float>> &vec);
    int checkBlock(int x, int y);
    SDL_Rect rayWall(float pitch, int k, int ratio, std::vector<std::vector<float>> &vec);
    short angleDiffFix(int o);
    void newCol(player *P, SDL_Renderer *renderer, float angle);
};