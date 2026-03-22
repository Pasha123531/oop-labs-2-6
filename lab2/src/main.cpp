#include <iostream>
#include <utility>
#include "Entity.hpp"
#include "Item.hpp"
#include "Weapon.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Warrior.hpp"
#include "Chest.hpp"

int main() {
    try {
        std::cout << "=== ENTITY ===\n";
        Entity entity("BaseObject");
        std::cout << entity << std::endl;

        std::cout << "\n=== ITEM ===\n";
        Item sword("Iron Sword", 3.5, 100);
        Item shield("Steel Shield", 5.0, 150);

        std::cout << sword << std::endl;
        std::cout << shield << std::endl;

        std::cout << "\n=== WEAPON ===\n";
        Weapon axe("Battle Axe", 6.5, 250, 45);
        std::cout << axe << std::endl;

        std::cout << "\n=== CHARACTER ===\n";
        Character hero("Hero", 120, 25);
        std::cout << hero << std::endl;

        std::cout << "\n=== PLAYER ===\n";
        Player player("PlayerOne", 100, 20, 5);
        std::cout << player << std::endl;

        std::cout << "\n=== WARRIOR ===\n";
        Warrior warrior("StrongWarrior", 150, 35, 10, 50);
        std::cout << warrior << std::endl;

        std::cout << "\n=== COPY & MOVE ===\n";
        Warrior copyWarrior = warrior;
        std::cout << "Copied: " << copyWarrior << std::endl;

        Warrior movedWarrior = std::move(copyWarrior);
        std::cout << "Moved: " << movedWarrior << std::endl;

        std::cout << "\n=== CHEST (HAS-A) ===\n";
        Chest chest("TreasureChest", false, 200);
        chest.putItem(axe);

        std::cout << chest << std::endl;

        Item taken = chest.takeItem();
        std::cout << "Taken item: " << taken << std::endl;

        std::cout << "\n=== OPERATORS ===\n";
        Item combined = sword + shield;
        std::cout << "Combined item: " << combined << std::endl;

        Character team = hero + Character("Mage", 80, 40);
        std::cout << "Combined character: " << team << std::endl;

        if (!hero) {
            std::cout << "Hero is dead\n";
        }

        if (!Item("Empty", 1.0, 0)) {
            std::cout << "Empty item detected\n";
        }

        std::cout << "\n=== COUNTERS ===\n";
        std::cout << "Items: " << Item::getObjectCount() << std::endl;
        std::cout << "Characters: " << Character::getObjectCount() << std::endl;
        std::cout << "Chests: " << Chest::getObjectCount() << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}