pathCell::pathCell() {
    f = FLT_MAX;
    g = FLT_MAX;
    h = FLT_MAX;
    parentX = -1;
    parentY = -1;
    wall = false;
    isIncluded = false;
}