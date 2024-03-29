player::player() {
    wobble = 0.5;


    std::cout << "Created Player!" << std::endl;
}

void player::colMove(bool &X, bool &Y) {
    if(X) {
	    if(!Y) {
			y -= moveVectorY;
		}
	}
	if(Y) {
		if(!X) {
            x += moveVectorX;
		}
	}
	if(!X &&!Y) {
        y -= moveVectorY;
        x += moveVectorX;
    }
}

void player::addPitch(float i) {
    pitch += i;
}

float player::getPitch() {
    return pitch;
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