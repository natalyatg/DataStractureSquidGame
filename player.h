#ifndef PLAYER_H
#define PLAYER_H

//#include "group.h"
#include <memory>
#include "groupInfo.h"

class player{
private:
    int player_id;
    std::shared_ptr<groupInfo> group_info_ptr;
    int level;

public:
    player(int player_id, std::shared_ptr<groupInfo> group_info_ptr, int level);
    player(const player& player);
    player();
    player& operator=(const player& player);
    ~player() = default;
    bool operator<(const player& player) const;
    bool operator==(const player& player) const;
    // group* getGroupPtr() const;
    std::shared_ptr<groupInfo> getGroupInfoPtr();
    int getPlayerLevel() const;
    void increasePlayerLevel(const int points);
    //void updateGroupPtr(group* new_group_ptr);
};

#endif