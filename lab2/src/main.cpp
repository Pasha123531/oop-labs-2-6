#include <iostream>
#include <vector>
#include <memory>
#include "Entity.hpp"
#include "Item.hpp"
#include "Weapon.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Warrior.hpp"
#include "Chest.hpp"

int main() {
    try {
        std::cout << "=== STATIC BINDING ===\n";

        Item item("Simple Item", 1.0, 10);
        std::cout << item.info() << std::endl; // compile-time binding

        std::cout << "\n=== DYNAMIC BINDING (POINTER) ===\n";

        std::vector<Entity*> entities;

        entities.push_back(new Item("Sword", 3.5, 100));
        entities.push_back(new Weapon("Axe", 5.0, 200, 40));
        entities.push_back(new Player("PlayerOne", 100, 20, 5));
        entities.push_back(new Warrior("Warrior", 150, 30, 10, 50));
        entities.push_back(new Chest("Treasure", false, 300));

        for (const auto& e : entities) {
            std::cout << e->info() << std::endl;
            e->interact(); // dynamic
        }

        std::cout << "\n=== DYNAMIC BINDING (REFERENCE) ===\n";

        Warrior warrior("StrongWarrior", 150, 35, 10, 50);
        Entity& ref = warrior;

        std::cout << ref.info() << std::endl;
        ref.interact(); // dynamic binding через reference

        std::cout << "\n=== COPY & MOVE ===\n";

        Warrior copy = warrior;
        Warrior moved = std::move(copy);

        std::cout << moved << std::endl;

        std::cout << "\n=== DAMAGE & HEAL DEMO ===\n";

        Warrior fighter("Fighter", 150, 35, 10, 50);
        Weapon battleAxe("Battle Axe", 6.5, 250, 40);

        std::cout << "Before battle: " << fighter.info() << std::endl;
        std::cout << "Weapon used: " << battleAxe.info() << std::endl;

        fighter.takeDamage(battleAxe.damage());
        std::cout << fighter.name() << " received "
          << battleAxe.damage() << " damage from "
          << battleAxe.name() << ".\n";
        std::cout << "After hit: " << fighter.info() << std::endl;

        fighter.heal(20);
        std::cout << fighter.name() << " healed 20 HP.\n";
        std::cout << "After healing: " << fighter.info() << std::endl;

        std::cout << "\n=== COMPOSITION (CHEST) ===\n";

        Chest chest("Chest", false, 200);
        chest.putItem(item);

        std::cout << chest << std::endl;
        chest.interact();

        std::cout << "\n=== OPERATORS ===\n";

        Item sword("Sword", 3.0, 100);
        Item shield("Shield", 5.0, 150);

        Item combined = sword + shield;
        std::cout << combined << std::endl;

        if (!Item("Empty", 1.0, 0)) {
            std::cout << "Empty item detected\n";
        }

        std::cout << "\n=== COUNTERS ===\n";

        std::cout << "Items: " << Item::getObjectCount() << std::endl;
        std::cout << "Characters: " << Character::getObjectCount() << std::endl;
        std::cout << "Chests: " << Chest::getObjectCount() << std::endl;

        for (auto e : entities) { // очищення пам'яті
            delete e;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}