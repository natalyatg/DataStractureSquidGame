#include "group.h"

//constructor
group::group(int group_id):
        group_id(group_id),
        num_of_players(0),
        players_level()
        {}
group::group():
        group_id(0),
        num_of_players(0),
        players_level()
        {}

//copy constructor
group::group(const group& group):
    group_id(group.group_id),
    num_of_players(group.num_of_players),
    players_level(group.players_level)
    {}

//operator= 
group& group::operator=(const group& group)
{
    if(this == &group)
    {
        return *this;
    }
    this->group_id = group.group_id;
    this->num_of_players = group.num_of_players;
    this->players_level = group.players_level;
    return *this;
}

bool group::operator<(const group& group) const
{
    return this->group_id < group.group_id;

}

bool group::operator==(const group& group) const
{
    return group_id==group.group_id;
}

void group::setNumOfPlayer()
{
    this->num_of_players++;
}

void group::updatePlayersLevel(const level& new_player_level)
{
    this->players_level.insert(new_player_level);
}

void group::updateNumOfPlayers(int num)
{
    this->num_of_players = this->num_of_players+num;
}

void group::removePlayerFromGroup(const level& player_level)
{
    this->players_level.remove(player_level);
    this->num_of_players--;
}

AVLTree<level>& group::getLevelTree()
{
    return this->players_level;
}

level& group::getGroupPlayer(const level& player_level) const
{
    return this->players_level.findData(player_level);
}

void group::mergeLevelTree(const group& group)
{
    AVLTree<level> new_tree;
    new_tree = this->players_level;
    new_tree.mergeTrees(group.players_level);
    this->players_level.delete_tree();
    this->players_level= new_tree;
    new_tree.delete_tree();
}

int group::getNumOfPlayers()
{
    return this->num_of_players;
}

level& group::getMaxGroupPlayer() const
{
    return this->players_level.getMaxData();
}

level* group::getLeveTreeToArray() const
{
    level *levelTree = new level[this->num_of_players];
    this->players_level.treeToArrayInorder(levelTree);
    return levelTree;
}




