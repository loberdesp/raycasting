player::player() {
    x = WIN/2;
    y = WIN/2;
    angle = 90;
    sprint = 1;

    std::cout << "Created Player!" << std::endl;
}

void player::setX(float i) {
    x = i;
}

void player::setY(float i) {
    y = i;
}

void player::addAngle(int i) {
    angle += i;
}

float player::getX() {
    return x;
}

float player::getY() {
    return y;
}

int player::getAngle() {
    return angle;
}

void player::checkAngle() {
    if(angle > 180) {
        angle-=360;
    }
    if(angle < -180) {
        angle +=360;
    }
}

void player::calcRot(int i) {
    vectorX = 1;
    
    vectorY = tan((angle+i)*M_PI/180);
    if(abs(vectorX) > abs(vectorY)) {
        vectorX = vectorX/abs(vectorX);
        vectorY = vectorY/abs(vectorX);
    } else {
        vectorX = vectorX/abs(vectorY);
        vectorY = vectorY/abs(vectorY);
    }
    if(angle+i > 90 || angle+i <-90) {
        vectorX *= -1;
        vectorY *= -1;
    }
}

float player::getVecX() {
    return vectorX;
}

float player::getVecY() {
    return vectorY;
}

void player::setVecX(float i) {
    vectorX=i;
}

void player::setVecY(float i) {
    vectorY=i;
}