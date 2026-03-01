#include <iostream>
#include "Item.hpp"
#include "Character.hpp"
#include "Chest.hpp"

int main() {

    // --- ITEM ---
    Item sword("Iron Sword", 3.5, 100);
    std::cout << sword.info() << std::endl;

    // --- CHARACTER ---
    Character hero("IronKnight", 120, 25);
    std::cout << hero.info() << std::endl;

    // персонаж отримує урон
    hero.takeDamage(30);
    std::cout << "After damage: " << hero.info() << std::endl;

    // лікування
    hero.heal(15);
    std::cout << "After heal: " << hero.info() << std::endl;

    // --- CHEST ---
    Chest chest("Treasure Chest", false, 200);
    std::cout << chest.info() << std::endl;

    chest.putItem(sword);
    std::cout << chest.info() << std::endl;
 
    return 0;
}