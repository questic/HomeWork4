#include "Player.h"
#include "Enemy.h"
#include <string>
#include <iostream>
#include <memory>


int main() {
    srand(time(NULL));

    std::string playerName{};
    std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>("Crutch", 6, 2);
    std::cout << "Welcome to the CPPLand. You are here to help the king Stroustrup and save the CPPLand." << std::endl;
    std::cout << "What is your name adventurer?" << std::endl;

    std::cin >> playerName;
    Player player(playerName, 20, 20, 0, 100, 1, 1, 10000, weapon);

    std::cout << "Welcome " << player.GetName() << " you are our las hope. Please defeat the UBDragon that has been terrorizing our land." << std::endl;
    std::cout << "You can find the UBDragon in its lair." << std::endl;
    std::cout << "But you will need to go through the lower level dungeons to level up before attempting to kill the UBDragon." << std::endl;
    std::cin.ignore();
    std::cout << "Press Enter to continue." << std::endl;
    std::cin.get();

    int choice = INT32_MAX;
    std::shared_ptr<Weapon> enemyWeapon{};
    std::shared_ptr<Enemy> enemy{};

    while (choice != 0) {
        choice = player.PlayerChoice();

        switch (choice)
        {
            case 1:
                enemyWeapon = std::make_shared<Weapon>("Bug Sword", 2, 1);
                enemy = std::make_shared<Enemy>("Bug", 10, 10, 1, enemyWeapon);
                player.EnterToDungeon(enemy);

                if (!player.IsPlayerAlive()) {
                    std::cout << "YOU DIED!" << std::endl;
                    choice = 0;
                }

                break;

            case 2:
                enemyWeapon = std::make_shared<Weapon>("Error Sword", 4, 1);
                enemy = std::make_shared<Enemy>("Error", 20, 20, 3, enemyWeapon);
                player.EnterToDungeon(enemy);

                if (!player.IsPlayerAlive()) {
                    std::cout << "YOU DIED!" << std::endl;
                    choice = 0;
                }

                break;

            case 3:
                enemyWeapon = std::make_shared<Weapon>("UBDragon Sword", 8, 2);
                enemy = std::make_shared<Enemy>("UBDragon", 50, 50, 5, enemyWeapon);
                player.EnterToDungeon(enemy);

                if (!player.IsPlayerAlive()) {
                    std::cout << "YOU DIED!" << std::endl;
                    choice = 0;
                }

                break;

            case 4:
                player.EnterToStore();
                break;

            case 5:
                player.UsePotion();
                break;

            case 0:
                std::cout << "See you next time." << std::endl;
                break;
            default:
                break;
        }
    }
}
