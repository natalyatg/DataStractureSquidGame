#include "player.h"


//constructor function
player::player(int player_id, std::shared_ptr<groupInfo> group_info_ptr, int level): 
    player_id(player_id), 
    group_info_ptr(group_info_ptr), 
    level(level) 
    {}

player::player():
    player_id(0),
    group_info_ptr(nullptr),
    level(0)
    {}

//copy function     
player::player(const player& player): player_id(player.player_id),group_info_ptr(player.group_info_ptr),level(player.level)
 
{}

//= operator
player& player::operator=(const player& player)
{
    if (this == &player) {
		return *this;
	}
    level = player.level;
    group_info_ptr = player.group_info_ptr;
    player_id = player.player_id;
	return *this;
}

bool player::operator<(const player& player) const
{
    return this->player_id < player.player_id;
}

bool player::operator==(const player& player) const
{
    return this->player_id == player.player_id;
}

std::shared_ptr<groupInfo> player::getGroupInfoPtr()
{
    return this->group_info_ptr;
}

int player::getPlayerLevel() const
{
    return this->level;
}

void player::increasePlayerLevel(const int points)
{
    this->level = this->level + points;
}







