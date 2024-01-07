class entity {
    protected:
        float angle;
        float x, y, z;                          // position
        float vectorX, vectorY, vectorZ;        // vector is basically speed in axis
        float prevX, prevY, prevZ;              // position in previous frame

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
        void addAngle(float i);
        void checkAngle();
        void calcRot(float i);

        float getVecX();
        float getVecY();
        float getVecZ();

        void setVecX(float i);
        void setVecY(float i);
        void setVecZ(float i);

};