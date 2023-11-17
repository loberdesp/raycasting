class player {
    int angle;
    float x, y;
    float vectorX, vectorY;
    int sprint;


    public:
        player();
        void setX(float i);
        void setY(float i);
        void addAngle(int i);
        void checkAngle();
        float getX();
        float getY();
        int getAngle();
        void calcRot(int i);
        float getVecX();
        float getVecY();
        void setVecX(float i);
        void setVecY(float i);
        void colMove(bool &X, bool &Y);
        void colMoveBack(bool &X, bool &Y);
};