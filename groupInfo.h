#ifndef GROUPINFO_H
#define GROUPINFO_H

#include "group.h"
#include <memory>


class groupInfo{
private:
    group* group_nt;

public:
    groupInfo(group* group_nt);
    groupInfo(const groupInfo& group_nt);
    groupInfo& operator=(const groupInfo& group_nt);
    ~groupInfo() = default; 
    group* getGroupPtr() const;
    void updateGroupPtr(group* new_group_ptr);
};

#endif