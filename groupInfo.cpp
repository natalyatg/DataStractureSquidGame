#include "groupInfo.h"

//constructor
groupInfo::groupInfo(group* group_nt):
        group_nt(group_nt)
        {}

//copy constructor
groupInfo::groupInfo(const groupInfo& groupInfo):
    group_nt(groupInfo.group_nt)
    {}

groupInfo& groupInfo::operator=(const groupInfo& groupInfo)
{
    if(this == &groupInfo)
    {
        return *this;
    }
    this->group_nt = groupInfo.group_nt;
    return *this;
}

group* groupInfo::getGroupPtr() const
{
    return this->group_nt;
}

void groupInfo::updateGroupPtr(group* new_group_ptr)
{
    this->group_nt = new_group_ptr;//need to delete the old pointer??
    
}

