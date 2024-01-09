class player : public entity {
    float pitch;
    float wobble;
    float velocity;
    float handMoveRatio;



    public:
        player();
        void colMove(bool &X, bool &Y);
        void addPitch(float i);
        float getPitch();
        bool checkMove(float& rat);
        void updateWobble();
        float getHandMoveX();
        float getHandMoveY();
};