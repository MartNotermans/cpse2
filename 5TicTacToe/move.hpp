class move{
public:
    
    bool owner; //false = O, true = X

    // 123
    // 456
    // 789
    int place;

    move(bool owner, int place):
    owner(owner), place(place)
    {}
};