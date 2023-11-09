map::map() {
    std::cout << "Created Map!" << std::endl;
}

void map::addWall(int x1, int y1, int x2, int y2) {
    for(int i=x1;i<x2;i++) {
        for(int j=y1;j<y2;j++) {
            if(mapVector[i][j]==0) {
                mapVector[i][j]=1;
            }
        }
    }
    SDL_Rect tmpWall;
    tmpWall.x = x1;
    tmpWall.y = y1;
    tmpWall.w = x2-x1;
    tmpWall.h = y2-y1;
    wallVec.push_back(tmpWall);
}

int map::getWallcount() {
    return wallVec.size();
}

SDL_Rect *map::getRect(int i) {
    return &wallVec[i];
}
