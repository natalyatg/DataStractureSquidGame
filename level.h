#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
class groupInfo;

class level {
private:
    int player_level;
    int player_id;
    std::shared_ptr<groupInfo> group_info_ptr;
public:
    level(int player_level, int player_id, std::shared_ptr<groupInfo> group_info_ptr);
    level();
    ~level() = default;
    level(const level& level);
    level& operator=(const level& level);
    bool operator<(const level& level) const;
    bool operator==(const level& level) const;
    std::shared_ptr<groupInfo> getGroupInfoPtr();
    int getPlayerID() const;
};

#endif
