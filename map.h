class map
{
    std::vector<std::vector<int>> mapVector = std::vector<std::vector<int>>(MAPSIZE, std::vector<int>(MAPSIZE));
    std::vector<SDL_Rect> wallVec;
    std::vector<std::vector<pathCell>> pathMap = std::vector<std::vector<pathCell>>(MAPSIZE, std::vector<pathCell>(MAPSIZE));

public:
    map();
    void initMap();
    void initPath();
    bool isDestination(int y, int x, int dy, int dx);
    bool isValid(int row, int col);
    void updatePath(int sX, int sY, int dX, int dY);
    float calculateHValue(int row, int col, int destX, int destY);
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