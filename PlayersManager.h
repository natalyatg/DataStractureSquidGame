#ifndef PLAYERSMANAGER_H
#define PLAYERSMANAGER_H

#include "group.h"
#include "level.h"
#include "player.h"
#include "AVLTree.h"
#include "library1.h"
#include <memory>

class PlayersManager{
private:
    AVLTree<group> AVL_groups;
    AVLTree<player> AVL_all_players_id;
    AVLTree<level> AVL_all_levels;
    int num_of_players;    

public:
    PlayersManager();
    ~PlayersManager() = default;
    PlayersManager(const PlayersManager& PlayersManager);
    PlayersManager& operator=(const PlayersManager& PlayersManager);

    //given functions
    StatusType AddGroup(int GroupID);
    StatusType AddPlayer(int PlayerID, int GroupID, int Level);
    StatusType RemovePlayer(int PlayerID);
    StatusType ReplaceGroup(int GroupID, int ReplacementID);
    StatusType IncreaseLevel(int PlayerID, int LevelIncrease);
    StatusType GetHighestLevel(int GroupID, int *PlayerID);
    StatusType GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);
    StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);
    void Quit();
};

#endif



