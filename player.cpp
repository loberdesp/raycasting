player::player() {
    x = WINY/2;
    y = WINY/2;
    z = 0;
    angle = 90;
    pitch = 0;
    wobble = 0.5;
    par = 0;
    handMoveRatio = 0;

    std::cout << "Created Player!" << std::endl;
}

void player::setX(float i) {
    x = i;
}

void player::setY(float i) {
    y = i;
}

void player::addAngle(float i) {
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
    calcRot(0);
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


void player::updateGravity() {
    
}

void player::updatePrevPos() {
    prevX = x;
    prevY = y;
}

bool player::checkMove(float& rat) {
    if(prevX == x && prevY == y) {
        return false;
    } else {
        rat = sqrt(pow(prevX-x,2)+pow(prevY-y,2));
        rat *= 5;
        rat /= 7;
        return true;
    }
}

void player::updateWobble() {
    if (wobble > 1) {
            wobble = -1;
        }
    if(prevX!= x || prevY!= y) {
        handMoveRatio = sqrt(pow(prevX-x,2)+pow(prevY-y,2));
        handMoveRatio *= 5;
        handMoveRatio /= 7;
        wobble += 0.015*handMoveRatio;
    } else {
        if((wobble>-1 && wobble < -0.5) || (wobble > 0 && wobble < 0.5)) {
            wobble+=0.015;
        }
        if((wobble > -0.5 && wobble < 0) || (wobble > 0.5 && wobble < 1)) {
            wobble -=0.015;
        }
    }   
}

float player::getHandMoveX() {
    return 30 * cos(M_PI * wobble);
}

float player::getHandMoveY() {
    return 50 * sin(-abs(wobble) * M_PI) / 2;
}