#include "PlayersManager.h"
#include "exceptions.h"


PlayersManager::PlayersManager():
    AVL_groups(), AVL_all_players_id(), AVL_all_levels(), num_of_players(0)
    {}

PlayersManager::PlayersManager(const PlayersManager& PlayersManager): AVL_groups(PlayersManager.AVL_groups),
    AVL_all_players_id(PlayersManager.AVL_all_players_id), AVL_all_levels(PlayersManager.AVL_all_levels), 
    num_of_players(PlayersManager.num_of_players)
    {}


PlayersManager& PlayersManager::operator=(const PlayersManager& PlayersManager)
{
    if(this == &PlayersManager)
    {
        return *this;
    }
    this->AVL_groups = PlayersManager.AVL_groups;
    this->AVL_all_players_id = PlayersManager.AVL_all_players_id;
    this->AVL_all_levels = PlayersManager.AVL_all_levels;
    this->num_of_players = PlayersManager.num_of_players;
    return *this;
}

StatusType PlayersManager::AddGroup(int GroupID)
{
    try
    {
        group new_group(GroupID);
        this->AVL_groups.insert(new_group);
    }
    catch(DataAlreadyExists &e)
    {
        return FAILURE;
    }
    catch (std::bad_alloc &e) 
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PlayersManager::AddPlayer(int PlayerID, int GroupID, int Level)
{
    try
    {
       group tmp_group(GroupID);
       if (!(this->AVL_groups.IsExists(tmp_group)))
        {
            return FAILURE;
        }
    
        group* group_new_ptr = this->AVL_groups.getDataPtr(tmp_group);
        std::shared_ptr<groupInfo> g_shared_ptr = std::shared_ptr<groupInfo>(new groupInfo(group_new_ptr));
        
        player new_player(PlayerID,g_shared_ptr,Level);
        this->AVL_all_players_id.insert(new_player);
        level new_player_level(Level, PlayerID, nullptr);
        //change the mazbia
        level new_group_level(Level, PlayerID, g_shared_ptr);
        try
        {
            this->AVL_all_levels.insert(new_player_level);
            group_new_ptr->updatePlayersLevel(new_group_level);
        }
        catch (std::bad_alloc &e)
        {
            return ALLOCATION_ERROR;
        }
        group_new_ptr->setNumOfPlayer();
    }
    catch (std::bad_alloc &e) 
    {
        return ALLOCATION_ERROR;
    }
    catch (DataAlreadyExists &e)
    {
        return FAILURE;
    }
    this->num_of_players++;
    return SUCCESS;
}

StatusType PlayersManager::RemovePlayer(int PlayerID)
{
    player tmp_player(PlayerID,nullptr,0);
    if (!this->AVL_all_players_id.IsExists(tmp_player))
    {
        return FAILURE;
    }
    tmp_player = AVL_all_players_id.findData(tmp_player);
    //add here get player info
    group* group_new_ptr = tmp_player.getGroupInfoPtr()->getGroupPtr();
    
    level tmp_player_level(tmp_player.getPlayerLevel(),PlayerID,nullptr);
    this->AVL_all_levels.remove(tmp_player_level);
    this->AVL_all_players_id.remove(tmp_player);
    group_new_ptr->removePlayerFromGroup(tmp_player_level);
    this->num_of_players--;
    return SUCCESS;
}

StatusType PlayersManager::ReplaceGroup(int GroupID, int ReplacementID)
{
    group old_group(GroupID);
    group new_group(ReplacementID);
    if((!this->AVL_groups.IsExists(old_group)) ||  (!this->AVL_groups.IsExists(new_group)))
    {
        return FAILURE;
    }    
    try
    {
        group* group_old_ptr = this->AVL_groups.getDataPtr(old_group);
        group* group_new_ptr = this->AVL_groups.getDataPtr(new_group);
        group_new_ptr->mergeLevelTree(*group_old_ptr);
        group_new_ptr->updateNumOfPlayers(group_old_ptr->getNumOfPlayers());
        this->AVL_groups.remove(old_group);  
        group_new_ptr = this->AVL_groups.getDataPtr(new_group);
        level * levelTree = group_new_ptr->getLeveTreeToArray();
        for(int i=0;i<group_new_ptr->getNumOfPlayers();i++)
        {
            levelTree[i].getGroupInfoPtr()->updateGroupPtr(group_new_ptr);
        }
        delete []levelTree;
        return SUCCESS;
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    
    
}

StatusType PlayersManager::IncreaseLevel(int PlayerID, int LevelIncrease)
{
    player tmp_player(PlayerID,nullptr,0);
    if (!this->AVL_all_players_id.IsExists(tmp_player))
    {
        return FAILURE;
    }
    try
    {
        player* p = AVL_all_players_id.getDataPtr(tmp_player);
        group* group_ptr = p->getGroupInfoPtr()->getGroupPtr();
        level player_level(p->getPlayerLevel(), PlayerID, nullptr);
        level player_level_with_group_ptr(p->getPlayerLevel(), PlayerID, p->getGroupInfoPtr());
        p->increasePlayerLevel(LevelIncrease);
        level new_player_level(p->getPlayerLevel(), PlayerID, nullptr);
        level new_player_level_with_group_ptr(p->getPlayerLevel(), PlayerID, p->getGroupInfoPtr());
        this->AVL_all_levels.remove(player_level);
        this->AVL_all_levels.insert(new_player_level);
        group_ptr->removePlayerFromGroup(player_level_with_group_ptr);
        group_ptr->updatePlayersLevel(new_player_level_with_group_ptr);
        group_ptr->setNumOfPlayer();
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PlayersManager::GetHighestLevel(int GroupID, int *PlayerID)
{
    if (GroupID < 0)
    {
        if (this->num_of_players == 0)
        {
            *PlayerID = -1;
            return SUCCESS;
        }
        level max_player_level = this->AVL_all_levels.getMaxData();
        *PlayerID = max_player_level.getPlayerID();
        return SUCCESS;
    }
    
    group tmp_group(GroupID);
    if (!this->AVL_groups.IsExists(tmp_group))
    {
        return FAILURE;
    }
    else
    {
        tmp_group = this->AVL_groups.findData(tmp_group);
        if (tmp_group.getNumOfPlayers() == 0)
        {
            *PlayerID = -1;
            return SUCCESS;
        }
        level max_player_level = tmp_group.getMaxGroupPlayer();
        *PlayerID = max_player_level.getPlayerID();
        return SUCCESS;
    }
}

StatusType PlayersManager::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers)
{
    if(GroupID < 0)
    {
        int* players_arr = (int*)malloc(this->num_of_players*sizeof(int));
        level *levelTree = new level[this->num_of_players];
        this->AVL_all_levels.treeToArrayInorder(levelTree);
        for(int i=this->num_of_players-1;i>=0;i--)
        {
            players_arr[this->num_of_players-1-i]=levelTree[i].getPlayerID();
        }
        *numOfPlayers = this->num_of_players;
        *Players = players_arr;
        delete []levelTree;
        return SUCCESS;
    }
    group tmp_group(GroupID);
    if (!(this->AVL_groups.IsExists(tmp_group)))
    {
        return FAILURE;
    }
    group* group_new_ptr = this->AVL_groups.getDataPtr(tmp_group);
    int* players_arr = (int*)malloc(this->num_of_players*sizeof(int));
     level * levelTree = group_new_ptr->getLeveTreeToArray();
    for(int i=group_new_ptr->getNumOfPlayers()-1;i>=0;i--)
    {    
        players_arr[group_new_ptr->getNumOfPlayers()-1-i]=levelTree[i].getPlayerID();
    }
    *numOfPlayers = group_new_ptr->getNumOfPlayers();
    *Players = players_arr;
    delete []levelTree;
    return SUCCESS;
}

StatusType PlayersManager::GetGroupsHighestLevel(int numOfGroups, int **Players)
{
    if(numOfGroups > this->AVL_groups.getTreeSize())
    {
        return FAILURE;
    }
    int* players_arr = (int*)malloc(numOfGroups*sizeof(int));
    group *group_array = new group[this->AVL_groups.getTreeSize()];
    this->AVL_groups.treeToArrayInorder(group_array); 
    int i = 0;
    int j = 0;
    int counter_empty_groups = 0;
    while (i<numOfGroups)
    {
        if(group_array[j].getNumOfPlayers() > 0)
        {
            players_arr[i] = (group_array[j].getMaxGroupPlayer()).getPlayerID();
            i++;
        }
        else
        {
            counter_empty_groups++;
            if(numOfGroups > this->AVL_groups.getTreeSize()-counter_empty_groups)
            {
                delete []group_array;
                return FAILURE;
            }
        }
        j++;
    }
    *Players = players_arr;
    delete []group_array;
    return SUCCESS;  
}

void PlayersManager::Quit()
{
    this->AVL_all_levels.delete_tree();
    this->AVL_groups.delete_tree();
    this->AVL_all_players_id.delete_tree();   
}





