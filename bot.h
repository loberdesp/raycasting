class bot : public entity {
    bool follow;




    public:
        bot();
        void toggleFollow();
        bool getFollow();
};