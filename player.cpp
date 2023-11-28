player::player() {
    x = WINY/2;
    y = WINY/2;
    angle = 90;
    pitch = 0;
    handWobble = 0;
    par = 0;

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

void player::calcRot(float i) {
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
    return vectorX*WINY/1000;
}

float player::getVecY() {
    return vectorY*WINY/1000;
}

void player::setVecX(float i) {
    vectorX=i;
}

void player::setVecY(float i) {
    vectorY=i;
}

void player::colMove(bool &X, bool &Y) {
    if(X) {
	    if(!Y) {
			y -= vectorY;
		}
	}
	if(Y) {
		if(!X) {
            x += vectorX;
		}
	}
	if(!X &&!Y) {
        y -= vectorY;
        x += vectorX;
    }
}

void player::colMoveBack(bool &X, bool &Y) {
    if(X) {
	    if(!Y) {
			y += vectorY;
		}
	}
	if(Y) {
		if(!X) {
            x -= vectorX;
		}
	}
	if(!X &&!Y) {
        y += vectorY;
        x -= vectorX;
    }
}

void player::addPitch(float i) {
    pitch += i;
}

float player::getPitch() {
    return pitch;
}

void player::addHandWobble() {
    if(handWobble >= 0.99) {
        par = 1;
    } else if(handWobble <= -0.99) {
        par = 0;
    }
    if(par == 0) {
        handWobble += 0.01;
    } else {
        handWobble -= 0.01;
    }
}

float player::getHandWobble() {
    return handWobble;
}