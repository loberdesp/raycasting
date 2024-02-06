class pathCell {
    public:
        float g;
        float h;
        float f;
        int x,y;
        bool wall;
        int parentX;
        int parentY;

        pathCell();
};