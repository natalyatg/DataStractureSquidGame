#include "library1.h"
#include "PlayersManager.h"

void* Init() {
PlayersManager *DS = new PlayersManager();
return (void*)DS;
}

StatusType AddGroup(void *DS, int GroupID)
{
    if (DS == NULL || GroupID <= 0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> AddGroup(GroupID);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level)
{
    if (DS == NULL || GroupID <= 0 || PlayerID<=0 || Level < 0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> AddPlayer(PlayerID, GroupID, Level);
}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if (DS == NULL || PlayerID<=0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> RemovePlayer(PlayerID);
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID)
{
    if(DS == NULL || GroupID<=0 || ReplacementID<=0 || GroupID==ReplacementID)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> ReplaceGroup(GroupID, ReplacementID);
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if (DS==NULL || PlayerID <=0 || LevelIncrease <=0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> IncreaseLevel(PlayerID, LevelIncrease);
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID)
{
    if (DS==NULL || PlayerID == NULL || GroupID ==0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> GetHighestLevel(GroupID, PlayerID);
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers)
{
    if(DS == NULL || Players == NULL || numOfPlayers == NULL || GroupID==0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> GetAllPlayersByLevel(GroupID, Players, numOfPlayers);
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players)
{
     if(DS == NULL || Players == NULL || numOfGroups<1)
     {
         return INVALID_INPUT;
     }
    return((PlayersManager*)DS)-> GetGroupsHighestLevel(numOfGroups, Players);
}

void Quit(void** DS)
{
    //CarDealerShip *to_destroy = static_cast<CarDealerShip*>(*DS);
    PlayersManager* pm = (PlayersManager*)*DS;
    (pm)->Quit();
    delete pm;
    //((PlayersManager*)DS)->Quit();
    *DS = NULL;
}


