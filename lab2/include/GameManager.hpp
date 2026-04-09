#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Entity.hpp"
#include "Character.hpp"

class GameManager {
private:
    std::string dataFile_;
    std::string playerFile_;
    std::string historyFile_;

public:
    GameManager();

    void logAction(const std::string& action);
    void saveWorld(const std::vector<std::shared_ptr<Entity>>& gameWorld);
    void loadWorld(std::vector<std::shared_ptr<Entity>>& gameWorld);
    void savePlayer(const std::shared_ptr<Character>& player);
    std::shared_ptr<Character> loadPlayer();
};