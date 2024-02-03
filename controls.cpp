controls::controls()
{
	std::cout << "Created Controls!" << std::endl;
}

bool controls::eventSwitch()
{
	switch (e.type)
	{
	case SDL_QUIT:
	{
		return true;
		break;
	}
	case SDL_KEYDOWN:
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
		{
			return true;
			break;
		}
		case SDLK_SPACE:
		{
			std::cout << "jump" << std::endl;
		}
		}
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "shoot" << std::endl;
		}
	}
	default:
	{
		break;
	}
	}
	return false;
}

SDL_Event *controls::getEvent()
{
	return &e;
}

void controls::kbHandle(player *P, bot *B, map *M, SDL_Renderer *renderer)
{
	bool move = false;
	if (keyboardState[SDL_SCANCODE_LEFT])
	{
		P->addAngle(1);
	}
	if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		P->addAngle(-1);
	}
	if (keyboardState[SDL_SCANCODE_UP])
	{
		if (P->getPitch() <= WINY)
		{
			P->addPitch(5);
		}
	}
	if (keyboardState[SDL_SCANCODE_DOWN])
	{
		if (P->getPitch() > -WINY)
		{
			P->addPitch(-5);
		}
	}

	if (keyboardState[SDL_SCANCODE_LSHIFT])
	{
		std::cout << "sprint" << std::endl;
	}
	if (keyboardState[SDL_SCANCODE_LCTRL])
	{
		std::cout << "crouch" << std::endl;
	}

	if (keyboardState[SDL_SCANCODE_W])
	{
		P->updateMoveVectors();
		
		// bool X, Y;
		// M->checkCol(P->getX(), P->getY(), P->getVecX(), P->getVecY(), X, Y);
		// P->colMove(X, Y);
		M->newCol(P, renderer, P->getAngle() + 90);
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		if(P->getAngle()>=90) {
			P->calcRot(-180);
		} else {
			P->calcRot(180);
		}
		P->updateMoveVectors();
		M->newCol(P, renderer, P->getAngle() - 90);
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
		P->calcRot(90);
		P->updateMoveVectors();
		bool X, Y;
		M->checkCol(P->getX(), P->getY(), P->getVecX(), P->getVecY(), X, Y);
		P->colMove(X, Y);
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		P->calcRot(-90);
		P->updateMoveVectors();
		bool X, Y;
		M->checkCol(P->getX(), P->getY(), P->getVecX(), P->getVecY(), X, Y);
		P->colMove(X, Y);
	}




	//bot movement with numpad


	if (keyboardState[SDL_SCANCODE_KP_8])
	{
		B->move(0, 1);
	}
	if (keyboardState[SDL_SCANCODE_KP_5])
	{
		B->move(0, -1);
	}
	if (keyboardState[SDL_SCANCODE_KP_4])
	{
		B->move(-1, 0);
	}
	if (keyboardState[SDL_SCANCODE_KP_6])
	{
		B->move(1, 0);
	}

}

void controls::mouseHandle(player *P, map *M)
{
	int k, u;
	SDL_GetRelativeMouseState(&u, &k);
	if (P->getPitch() > -2 * WINY)
	{
		P->addPitch(float(-k) * SENSITIVITY / 2);
	}
	else
	{
		P->addPitch(-2 * WINY - P->getPitch());
		if (-k < 0)
		{
			P->addPitch(float(-k) * SENSITIVITY / 2);
		}
	}
	if (P->getPitch() <= 2 * WINY)
	{
		P->addPitch(float(-k) * SENSITIVITY / 2);
	}
	else
	{
		P->addPitch(2 * WINY - P->getPitch());
		if (-k > 0)
		{
			P->addPitch(float(-k) * SENSITIVITY / 2);
		}
	}
	P->addAngle(float(-u) * 180 / (3 * WINY) * SENSITIVITY);
}
