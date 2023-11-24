map::map() {
    std::cout << "Created Map!" << std::endl;
}

void map::addWall(int x1, int y1, int x2, int y2) {
    for(float i=x1;i<x2;i++) {
        for(float j=y1;j<y2;j++) {
            //chodzi o to ze kiedy mamy np win = 200 i potem to pomnozymy to mamy skok co np 5, bo jest mniej iteracji niz trzeba
            //mozliwe ze trzeba bedzie zrobic druga petle, roznica pomnozonych liczb i bedzie tylko dodawac do vectora mapy
            if(mapVector[i*1000/WIN][j*1000/WIN]==0) {
                mapVector[i*1000/WIN][j*1000/WIN]=1;
            }
        }
    }
    SDL_Rect tmpWall;
    tmpWall.x = x1;
    tmpWall.y = WIN/2+y1/2;
    tmpWall.w = x2-x1;
    tmpWall.h = (y2-y1)/2;
    wallVec.push_back(tmpWall);
}

int map::getWallcount() {
    return wallVec.size();
}

SDL_Rect *map::getRect(int i) {
    return &wallVec[i];
}

bool map::isinWall(float x, float y) {
    int xint = x*1000/WIN;
    int yint = y*1000/WIN;
    if(mapVector[xint][yint] == 1) {
        return true;
    } else {
        return false;
    }
}


void map::checkCol(float x, float y, float vx, float vy, bool &colX, bool &colY) {
    colX = isinWall(x + vx, y);
    colY = isinWall(x, y - vy);
}


void map::getline(float &x, float &y, float vx, float vy) {
    bool touch = true;
    while(touch) {
        if(isinWall(x+vx,y-vy)) {
            touch = false;
        } else {
            x += vx;
            y -= vy;
        }
    }
}