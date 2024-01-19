#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include "AVLTree.h"
#include "level.h"
//class level;

class group{
private:
    int group_id;
    int num_of_players;
    AVLTree<level> players_level;

public:
    group(int group_id);
    group();
    ~group() = default;
    group(const group& group);
    group& operator=(const group& group);
    bool operator<(const group& group) const;
    bool operator==(const group& group) const;
    void updatePlayersLevel(const level& new_player_level);
    void setNumOfPlayer();
    void updateNumOfPlayers(int num);
    int getNumOfPlayers();
    void removePlayerFromGroup(const level& player_level);
    AVLTree<level>& getLevelTree();//need to check if this function is needed
    level& getGroupPlayer(const level& player_level) const;
    level& getMaxGroupPlayer() const;
    void mergeLevelTree(const group& group);//need to be const??
    //void changeTree(const AVLTree<level>& players_level);
    level* getLeveTreeToArray() const;
    
};

#endif