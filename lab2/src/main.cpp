#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

#include "Entity.hpp"
#include "Item.hpp"
#include "Chest.hpp"
#include "Weapon.hpp"
#include "Player.hpp"
#include "Warrior.hpp"
#include "GameManager.hpp"

const std::string ADMIN_PASSWORD = "admin";

void gameLoop(std::vector<std::shared_ptr<Entity>>& gameWorld, std::shared_ptr<Character>& currentPlayer, GameManager& fileManager) {
    int choice;
    while (true) {
        std::cout << "\n=== ADVENTURE MENU ===\n";
        std::cout << "Player: " << currentPlayer->info() << "\n";
        std::cout << "----------------------\n";
        std::cout << "1. Explore surroundings\n";
        std::cout << "2. Interact with object\n";
        std::cout << "3. Rest (Heal)\n";
        std::cout << "4. Save Game (Player Status)\n";
        std::cout << "0. Logout\n";
        std::cout << "What will you do? ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: Enter a NUMBER!\n";
            continue;
        }

        if (choice == 1) {
            std::cout << "\n-- You look around --\n";
            if (gameWorld.empty()) {
                std::cout << "The area is completely empty and silent...\n";
            } else {
                for (size_t i = 0; i < gameWorld.size(); ++i) {
                    std::cout << "[" << i << "] " << gameWorld[i]->info() << "\n";
                }
            }
            fileManager.logAction(currentPlayer->name() + " explored the area.");
        } 
        else if (choice == 2) {
            if (gameWorld.empty()) {
                std::cout << "There is nothing to interact with!\n";
                continue;
            }
            std::cout << "Enter object number to interact: ";
            size_t idx;
            if (!(std::cin >> idx)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Error: Enter a NUMBER!\n";
                continue;
            }

            if (idx < gameWorld.size()) {
                std::cout << "\n>> You approach the " << gameWorld[idx]->name() << "...\n";
                gameWorld[idx]->interact();
                fileManager.logAction(currentPlayer->name() + " interacted with " + gameWorld[idx]->name());
            } else {
                std::cout << "Invalid object number!\n";
            }
        }
        else if (choice == 3) {
            currentPlayer->heal(20);
            std::cout << "You rested and recovered 20 HP.\n";
            fileManager.logAction(currentPlayer->name() + " rested.");
        }
        else if (choice == 4) {
            fileManager.savePlayer(currentPlayer);
            fileManager.logAction(currentPlayer->name() + " saved the game.");
        }
        else if (choice == 0) {
            std::cout << "Leaving the realm...\n";
            fileManager.savePlayer(currentPlayer);
            currentPlayer = nullptr; 
            break;
        }
    }
}

void userMenu(std::vector<std::shared_ptr<Entity>>& gameWorld, std::shared_ptr<Character>& currentPlayer, GameManager& fileManager) {
    currentPlayer = fileManager.loadPlayer();
    
    if (currentPlayer) {
        std::cout << "\n=== SAVED GAME FOUND ===\n";
        std::cout << "Welcome back, " << currentPlayer->name() << "!\n";
        std::cout << currentPlayer->info() << "\n\n";
        std::cout << "1. Continue adventure\n";
        std::cout << "2. Create a NEW character (Overwrites save)\n";
        std::cout << "Choice: ";
        int c;
        if (std::cin >> c && c == 1) {
            fileManager.logAction("User loaded saved character: " + currentPlayer->name());
            gameLoop(gameWorld, currentPlayer, fileManager);
            return;
        }
    }

    std::cout << "\nWelcome, traveler. Before entering the realm, you must define yourself.\n";
    int classChoice;
    std::string charName;

    std::cout << "\n=== CHARACTER CREATION ===\n";
    std::cout << "Enter your character's name: ";
    std::cin >> charName;

    std::cout << "Choose your Class:\n";
    std::cout << "1. Adventurer (Balanced stats)\n";
    std::cout << "2. Warrior (High HP, High Attack, Armor)\n";
    std::cout << "Choice: ";
    std::cin >> classChoice;

    if (classChoice == 1) {
        currentPlayer = std::make_shared<Player>(charName, 100, 15, 1);
        std::cout << "Adventurer " << charName << " is ready!\n";
    } else if (classChoice == 2) {
        currentPlayer = std::make_shared<Warrior>(charName, 150, 25, 1, 50);
        std::cout << "Warrior " << charName << " takes up their arms!\n";
    } else {
        std::cout << "Invalid class. Defaulting to Adventurer.\n";
        currentPlayer = std::make_shared<Player>(charName, 100, 15, 1);
    }

    if (currentPlayer) {
        fileManager.savePlayer(currentPlayer); 
        fileManager.logAction("User created new character: " + currentPlayer->name());
        gameLoop(gameWorld, currentPlayer, fileManager);
    }
}

void adminMenu(std::vector<std::shared_ptr<Entity>>& gameWorld, GameManager& fileManager) {
    int choice;
    while (true) {
        std::cout << "\n=== WORLD CREATOR MENU ===\n";
        std::cout << "1. Spawn an Item\n";
        std::cout << "2. Spawn a Weapon\n";
        std::cout << "3. Spawn a Treasure Chest\n";
        std::cout << "4. View World Entities\n";
        std::cout << "5. Save World to File\n";
        std::cout << "0. Logout to Main Menu\n";
        std::cout << "Command: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name; double weight; int value;
            std::cout << "Item Name: "; std::cin >> name;
            std::cout << "Weight: "; std::cin >> weight;
            std::cout << "Value: "; std::cin >> value;
            gameWorld.push_back(std::make_shared<Item>(name, weight, value));
            std::cout << name << " spawned in the world!\n";
        } 
        else if (choice == 2) {
            std::string name; double weight; int value, dmg;
            std::cout << "Weapon Name: "; std::cin >> name;
            std::cout << "Weight: "; std::cin >> weight;
            std::cout << "Value: "; std::cin >> value;
            std::cout << "Damage: "; std::cin >> dmg;
            gameWorld.push_back(std::make_shared<Weapon>(name, weight, value, dmg));
            std::cout << "Weapon " << name << " spawned!\n";
        }
        else if (choice == 3) {
            std::string name; int gold;
            std::cout << "Chest Name: "; std::cin >> name;
            std::cout << "Gold inside: "; std::cin >> gold;
            gameWorld.push_back(std::make_shared<Chest>(name, false, gold));
            std::cout << "Chest spawned!\n";
        }
        else if (choice == 4) {
            std::cout << "\n-- Entities in the world --\n";
            for (size_t i = 0; i < gameWorld.size(); ++i) {
                std::cout << "[" << i << "] " << gameWorld[i]->info() << "\n";
            }
        } 
        else if (choice == 5) {
            fileManager.saveWorld(gameWorld);
        } 
        else if (choice == 0) {
            break;
        }
    }
}

int main() {
    GameManager fileManager; 
    
    std::vector<std::shared_ptr<Entity>> gameWorld;
    fileManager.loadWorld(gameWorld); 
    
    std::shared_ptr<Character> currentPlayer = nullptr;

    int choice;
    while (true) {
        std::cout << "\n====================================\n";
        std::cout << "      WELCOME TO THE TEXT RPG       \n";
        std::cout << "====================================\n";
        std::cout << "1. Play Game (User Mode)\n";
        std::cout << "2. World Creator (Admin Mode)\n";
        std::cout << "0. Exit Game\n";
        std::cout << "Choose your path: ";
        
        try {
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw std::invalid_argument("Invalid input! Please enter a number.");
            }

            if (choice == 1) {
                userMenu(gameWorld, currentPlayer, fileManager);
            } else if (choice == 2) {
                std::string pass;
                std::cout << "Enter Creator password: ";
                std::cin >> pass;
                if (pass == ADMIN_PASSWORD) {
                    adminMenu(gameWorld, fileManager);
                } else {
                    std::cout << "Access Denied. Incorrect password!\n";
                }
            } else if (choice == 0) {
                std::cout << "Farewell, adventurer...\n";
                break;
            } else {
                std::cout << "Unknown option.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "System Error: " << e.what() << "\n";
        }
    }

    return 0;
}