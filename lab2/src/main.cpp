#include <iostream>
#include <utility>
#include "Item.hpp"
#include "Character.hpp"
#include "Chest.hpp"

int main() {
    try {
        std::cout << "=== ITEM ===\n";
        Item sword("Iron Sword", 3.5, 100);
        Item shield("Steel Shield", 5.0, 150);

        std::cout << "Sword: " << sword << std::endl;
        std::cout << "Shield: " << shield << std::endl;

        Item loot = sword + shield;
        std::cout << "Combined item: " << loot << std::endl;

        Item copiedItem = sword;
        std::cout << "Copied item: " << copiedItem << std::endl;

        Item movedItem = std::move(shield);
        std::cout << "Moved item: " << movedItem << std::endl;

        std::cout << "Item objects count: " << Item::getObjectCount() << std::endl;

        if (!Item("EmptyItem", 1.0, 0)) {
            std::cout << "Unary ! for Item works: item value is zero\n";
        }

        std::cout << "\n=== CHARACTER ===\n";
        Character hero("IronKnight", 120, 25);
        Character mage("FireMage", 80, 40);

        std::cout << "Hero: " << hero << std::endl;
        std::cout << "Mage: " << mage << std::endl;

        Character team = hero + mage;
        std::cout << "Combined character: " << team << std::endl;

        Character copiedHero = hero;
        std::cout << "Copied hero: " << copiedHero << std::endl;

        Character movedMage = std::move(mage);
        std::cout << "Moved character: " << movedMage << std::endl;

        hero.takeDamage(150);
        std::cout << "Hero after damage: " << hero << std::endl;

        if (!hero) {
            std::cout << "Unary ! for Character works: hero is dead\n";
        }

        std::cout << "Character objects count: " << Character::getObjectCount() << std::endl;

        std::cout << "\n=== CHEST ===\n";
        Chest chest1("TreasureChest", false, 200);
        Chest chest2("SecretChest", true, 300);

        chest1.putItem(sword);

        std::cout << "Chest1: " << chest1 << std::endl;
        std::cout << "Chest2: " << chest2 << std::endl;

        Chest mergedChest = chest1 + chest2;
        std::cout << "Merged chest: " << mergedChest << std::endl;

        Chest copiedChest = chest1;
        std::cout << "Copied chest: " << copiedChest << std::endl;

        Chest movedChest = std::move(chest2);
        std::cout << "Moved chest: " << movedChest << std::endl;

        if (!movedChest) {
            std::cout << "Unary ! for Chest works: chest is locked\n";
        }

        std::cout << "Chest objects count: " << Chest::getObjectCount() << std::endl;

        std::cout << "\n=== INPUT DEMO ===\n";
        Item userItem;
        std::cin >> userItem;
        std::cout << "You entered item: " << userItem << std::endl;

        Character userCharacter;
        std::cin >> userCharacter;
        std::cout << "You entered character: " << userCharacter << std::endl;

        Chest userChest;
        std::cin >> userChest;
        std::cout << "You entered chest: " << userChest << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}