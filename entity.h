class entity {
    protected:
        float angle;
        float x, y, z;                          // position
        float vectorX, vectorY, vectorZ;        // vector is basically direction in axis
        float moveVectorX, moveVectorY, moveVectorZ; //move vector is location change per frame
        float prevX, prevY, prevZ;              // position in previous frame
        float timeElapsed;                      // time elapsed since last frame for non-frame dependent movement

    public:
        entity();

        void updatePrevPos();
        
        void setX(float i);
        void setY(float i);
        void setZ(float i);
        
        float getX();
        float getY();
        float getZ();

        int getAngle();
        float floatAngle();
        void addAngle(float i);
        void checkAngle();
        void calcRot(float i);

        float getVecX();
        float getVecY();
        float getVecZ();

        void setVecX(float i);
        void setVecY(float i);
        void setVecZ(float i);

        void setElapsed(float t);
        void updateMoveVectors();

        float getMoveVectorX();
        float getMoveVectorY();
        float getMoveVectorZ();

        void move(float a, float b);
};