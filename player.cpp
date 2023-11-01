player::player() {
    x = WIN/2;
    y = WIN/2;

    std::cout << "Created Player!" << std::endl;
}

void player::setX(int i) {
    x = i;
}

void player::setY(int i) {
    y = i;
}

int player::getX() {
    return x;
}

int player::getY() {
    return y;
}