#include "level.h"

//constructor
level::level(int player_level, int player_id, std::shared_ptr<groupInfo> group_info_ptr):
        player_level(player_level),
        player_id(player_id),
        group_info_ptr(group_info_ptr)
        {}

level::level():
    player_level(0),
    player_id(0),
    group_info_ptr(nullptr)
    {}

//copy constructor
level:: level(const level& level):
    player_level(level.player_level),
    player_id(level.player_id),
    group_info_ptr(level.group_info_ptr)
    {}

//operator= 
level& level::operator=(const level& level)
{
    if(this == &level)
    {
        return *this;
    }
    this->player_level = level.player_level;
    this->player_id = level.player_id;
    this->group_info_ptr = level.group_info_ptr;
    return *this;
}

bool level::operator<(const level& level) const
{
    if (this->player_level < level.player_level)
    {
        return true;
    }
    else if(this->player_level > level.player_level)
    {
        return false;
    }
    else
    {
        return this->player_id > level.player_id;
    }
}

bool level::operator==(const level& level) const
{
    return player_id==level.player_id;
}

/*player* level::getPlayerPtr() const
{
    return this->player_ptr;
}*/

std::shared_ptr<groupInfo> level::getGroupInfoPtr()
{
    return this->group_info_ptr;
}


/*
    T *t_ptr = &(new_node->data);
    return t_ptr;
*/

int level::getPlayerID() const
{
    return this->player_id;
}
