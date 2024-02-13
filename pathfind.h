//basically this whole A* search algorith is copy pasted and slightly tweaked for my game from site bellow
//i am not author of this code
//https://www.geeksforgeeks.org/a-search-algorithm/

struct cell
{
    int parent_i, parent_j;
    double f, g, h;
    
};

class pathFinder
{
public:
    bool isValid(int row, int col);
    bool isUnBlocked(int grid[][COL], int row, int col);
    bool isDestination(int row, int col, Pair dest);
    double calculateHValue(int row, int col, Pair dest);
    void tracePath(cell cellDetails[][COL], Pair dest, int &Y, int &X);
    void aStarSearch(int grid[][COL], Pair src, Pair dest, int &nY, int &nX);
};