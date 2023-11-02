controls::controls() {
    std::cout << "Created Controls!" << std::endl;
}

bool controls::eventSwitch() {
    switch (e.type) {
		case SDL_QUIT: {
			return true;
			break;
		}
		case SDL_KEYDOWN: {
			switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: {
					return true;
				}
				case SDLK_SPACE: {
					std::cout << "toggle relative" << std::endl;
					if(SDL_GetRelativeMouseMode() == SDL_TRUE) {
						SDL_SetRelativeMouseMode(SDL_FALSE);
					} else {
						SDL_SetRelativeMouseMode(SDL_TRUE);
					}
										
				}
			}
		}
		default: {
			break;
		}
	}
    return false;
}

SDL_Event* controls::getEvent() {
    return &e;
}

void controls::kbHandle(player* P) {
    if(keyboardState[SDL_SCANCODE_LEFT]) {
		P->addAngle(1);
	}
    if(keyboardState[SDL_SCANCODE_RIGHT]) {
		P->addAngle(-1);
	}


	if(keyboardState[SDL_SCANCODE_LSHIFT]) {
	}


	if(keyboardState[SDL_SCANCODE_W]) {
		P->setX(P->getX()+P->getVecX());
		P->setY(P->getY()-P->getVecY());
	}
	if(keyboardState[SDL_SCANCODE_S]) {
		P->setX(P->getX()-P->getVecX());
		P->setY(P->getY()+P->getVecY());
	}
	if(keyboardState[SDL_SCANCODE_A]) {
		P->calcRot(90);
		P->setX(P->getX()+P->getVecX());
		P->setY(P->getY()-P->getVecY());
	}
	if(keyboardState[SDL_SCANCODE_D]) {
		P->calcRot(-90);
		P->setX(P->getX()+P->getVecX());
		P->setY(P->getY()-P->getVecY());
	}
}