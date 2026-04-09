#include "GameManager.hpp"
#include "Item.hpp"
#include "Chest.hpp"
#include "Weapon.hpp"
#include "Player.hpp"
#include "Warrior.hpp"
#include <fstream>
#include <iostream>

GameManager::GameManager() {
    dataFile_ = "game_data.txt";
    playerFile_ = "player_data.txt";
    historyFile_ = "user_history.txt";
}

void GameManager::logAction(const std::string& action) {
    std::ofstream out(historyFile_, std::ios::app);
    if (out.is_open()) {
        out << action << "\n";
        out.close();
    }
}

void GameManager::loadWorld(std::vector<std::shared_ptr<Entity>>& gameWorld) {
    std::ifstream in(dataFile_);
    if (!in.is_open()) return;

    gameWorld.clear();
    std::string type, name;
    
    while (in >> type >> name) {
        if (type == "Item") {
            double weight; int value;
            in >> weight >> value;
            gameWorld.push_back(std::make_shared<Item>(name, weight, value));
        } 
        else if (type == "Weapon") {
            double weight; int value; int dmg;
            in >> weight >> value >> dmg;
            gameWorld.push_back(std::make_shared<Weapon>(name, weight, value, dmg));
        } 
        else if (type == "Chest") {
            bool locked; int gold;
            in >> locked >> gold;
            gameWorld.push_back(std::make_shared<Chest>(name, locked, gold));
        }
    }
    in.close();
}

void GameManager::saveWorld(const std::vector<std::shared_ptr<Entity>>& gameWorld) {
    std::ofstream out(dataFile_);
    if (!out.is_open()) return;

    for (const auto& entity : gameWorld) {
        if (auto chest = std::dynamic_pointer_cast<Chest>(entity)) {
            out << "Chest " << chest->name() << " " << chest->locked() << " " << chest->gold() << "\n";
        } 
        else if (auto weapon = std::dynamic_pointer_cast<Weapon>(entity)) {
            out << "Weapon " << weapon->name() << " " << weapon->weight() << " " << weapon->value() << " " << weapon->damage() << "\n"; 
        } 
        else if (auto item = std::dynamic_pointer_cast<Item>(entity)) {
            out << "Item " << item->name() << " " << item->weight() << " " << item->value() << "\n";
        }
    }
    out.close();
    std::cout << "World saved successfully!\n";
}

void GameManager::savePlayer(const std::shared_ptr<Character>& player) {
    if (!player) return;
    std::ofstream out(playerFile_);
    
    if (auto warrior = std::dynamic_pointer_cast<Warrior>(player)) {
        out << "Warrior " << warrior->name() << " " << warrior->hp() << " " << warrior->attack() << " " << warrior->level() << " " << 50 << "\n";
    } 
    else if (auto p = std::dynamic_pointer_cast<Player>(player)) {
        out << "Player " << p->name() << " " << p->hp() << " " << p->attack() << " " << p->level() << "\n";
    }
    out.close();
    std::cout << "Player progress saved!\n";
}

std::shared_ptr<Character> GameManager::loadPlayer() {
    std::ifstream in(playerFile_);
    if (!in.is_open()) return nullptr;

    std::string type, name;
    int hp, attack, level, armor;
    
    if (in >> type >> name >> hp >> attack >> level) {
        if (type == "Warrior") {
            in >> armor;
            return std::make_shared<Warrior>(name, hp, attack, level, armor);
        } else if (type == "Player") {
            return std::make_shared<Player>(name, hp, attack, level);
        }
    }
    return nullptr;
}