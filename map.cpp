map::map() {
    std::cout << "Created Map!" << std::endl;
}

void map::addWall(int x1, int y1) {
    if(mapVector[x1][y1] == 0) {
        mapVector[x1][y1] = 1;
    }
}

int map::getWallcount() {
    return wallVec.size();
}

SDL_Rect *map::getRect(int i) {
    return &wallVec[i];
}

bool map::isinWall(float x, float y) {
    int xint = x/float(TILESIZE);
    int yint = y/float(TILESIZE);
    if(mapVector[xint][yint] == 1) {
        return true;
    } else {
        return false;
    }
}


void map::checkCol(float x, float y, float vx, float vy, bool &colX, bool &colY) {
    if(abs(vx) > abs(vy)) {
        if(vx*vy>0) {
            vy = vx;
        } else {
            vy = -vx;
        }
    } else {
        if(vx*vy>0) {
            vx = vy;
        } else {
            vx = -vy;
        }
    }
    colX = isinWall(x + 50*vx, y);
    colY = isinWall(x, y - 50*vy);
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

bool map::checkWall(int x, int y) {
    if(mapVector[x][y] == 1) {
        return true;
    } else {
        return false;
    }
}