#include "../include/Player.h"

Player::Player(std::string playerName) : name(std::move(playerName)), final_score(0) {}