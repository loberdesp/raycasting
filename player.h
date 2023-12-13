class player {
    float angle;
    float x, y, z;
    float vectorX, vectorY;
    float pitch;
    float handWobble;
    bool par;
    float velocity;


    public:
        player();
        void setX(float i);
        void setY(float i);
        void addAngle(float i);
        void checkAngle();
        float getX();
        float getY();
        int getAngle();
        void calcRot(float i);
        float getVecX();
        float getVecY();
        void setVecX(float i);
        void setVecY(float i);
        void colMove(bool &X, bool &Y);
        void colMoveBack(bool &X, bool &Y);
        void addPitch(float i);
        float getPitch();
        void addHandWobble();
        float getHandWobble();
        void updateGravity();
};