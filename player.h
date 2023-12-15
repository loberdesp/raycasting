class player {
    float angle;
    float x, y, z;
    float vectorX, vectorY;
    float pitch;
    float wobble;
    bool par;
    float velocity;
    float prevX, prevY;
    float handMoveRatio;


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
        void updateGravity();
        void updatePrevPos();
        bool checkMove(float& rat);
        void updateWobble();
        float getHandMoveX();
        float getHandMoveY();
};