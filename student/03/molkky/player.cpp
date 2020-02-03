#include "player.hh"
#include <iostream>


Player::Player(std::string name)

{
    this->name = name;
    this->points = 0;
}

int Player::get_points() {
    return this->points;
}

std::string Player::get_name() {
    return this->name;
}

bool Player::has_won() {
    return this->points == 50;
}

void Player::add_points(int to_be_added) {
    this->points += to_be_added;
    if (this->points > 50) {
        std::cout << this->name << " gets penalty points!" << std::endl;
        this->points = 25;
        }
}

