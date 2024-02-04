entity::entity()
{
    x = WINY / 2;
    y = WINY / 2;
    z = WINY / 2;
    angle = 90;
}

void entity::setX(float i)
{
    x = i;
}

void entity::setY(float i)
{
    y = i;
}

void entity::addAngle(float i)
{
    angle += i;
}

float entity::getX()
{
    return x;
}

float entity::getY()
{
    return y;
}

float entity::getZ()
{
    return z;
}

int entity::getAngle()
{
    return angle;
}

float entity::floatAngle() {
    return angle;
}

void entity::checkAngle()
{
    if (angle > 180)
    {
        angle -= 360;
    }
    if (angle < -180)
    {
        angle += 360;
    }
    calcRot(0);
}

void entity::calcRot(float i)
{
    vectorX = 1;
    vectorY = tan((angle + i) * M_PI / 180);
    if (abs(vectorX) > abs(vectorY))
    {
        vectorX = vectorX / abs(vectorX);
        vectorY = vectorY / abs(vectorX);
    }
    else
    {
        vectorX = vectorX / abs(vectorY);
        vectorY = vectorY / abs(vectorY);
    }
    if (angle + i > 90 || angle + i < -90)
    {
        vectorX *= -1;
        vectorY *= -1;
    }
}

float entity::getVecX()
{
    return vectorX * WINY / 1000;
}

float entity::getVecY()
{
    return vectorY * WINY / 1000;
}

float entity::getVecZ()
{
    return vectorZ * WINY / 1000;
}

void entity::setVecX(float i)
{
    vectorX = i;
}

void entity::setVecY(float i)
{
    vectorY = i;
}

void entity::setVecZ(float i)
{
    vectorZ = i;
}

void entity::updatePrevPos()
{
    prevX = x;
    prevY = y;
    prevZ = z;
}

void entity::setElapsed(float t)
{
    timeElapsed = t;
}

void entity::updateMoveVectors() {
    moveVectorX = vectorX*timeElapsed*PLAYERSPEEDPERSEC;
    moveVectorY = vectorY*timeElapsed*PLAYERSPEEDPERSEC;
    moveVectorZ = vectorZ*timeElapsed*PLAYERSPEEDPERSEC;
}

float entity::getMoveVectorX() {
    return moveVectorX;
}

float entity::getMoveVectorY() {
    return moveVectorY;
}

float entity::getMoveVectorZ() {
    return moveVectorZ;
}

void entity::move(float a, float b) {
    y -= b;
    x += a;
}