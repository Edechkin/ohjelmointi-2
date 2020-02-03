#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

class Player
{
public:
    Player(std::string name);
    std::string get_name();
        int get_points();
        void add_points(int to_be_added);
        bool has_won();

private:
    std::string name;
    int points;
};
#endif // PLAYER_HH
