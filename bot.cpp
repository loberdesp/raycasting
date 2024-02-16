bot::bot() {
    x = WINY/2;
    y = WINY/4;

    vectorX = 0.7;
    vectorY = 0.7;

    follow = false;
    
}

void bot::toggleFollow() {
    if(follow) {
        follow = false;
    } else {
        follow = true;
    }
}

bool bot::getFollow() {
    return follow;
}