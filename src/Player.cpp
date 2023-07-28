#include "Player.h"
#include "Utils.h"
#include <string>
#include <iostream>
#include <limits>

Player::Player(std::string name, int health, int maxHealth, int exp, int maxExp, int level, int potion, int gold, std::shared_ptr<Weapon> weapon) : m_name(name), m_health(health), m_maxHealth(maxHealth), m_exp(exp), m_maxExp(maxExp),
                                                                                                                                                    m_level(level), m_potion(potion), m_gold(gold), m_weapon(weapon) {

}

void Player::SetExp(int exp) {
    int levelExpRequired[] = { 0, 100, 200, 300, 400, 500 };

    m_exp += exp;
    std::cout << exp << " exp gained!" << std::endl;

    int maxLevel = sizeof(levelExpRequired) / sizeof(levelExpRequired[0]) - 1;

    while (m_level < maxLevel && m_exp >= levelExpRequired[m_level]) {
        m_exp -= levelExpRequired[m_level];
        UpLevel();
        m_level++;
    }

    if (m_level == maxLevel && m_exp >= levelExpRequired[m_level]) {
        m_exp = 0;
        UpLevel();
    }
}

void Player::UpLevel() {
    int dice;
    int choice;

    std::cout << "--------------------" << std::endl;
    std::cout << "You have reached level " << m_level << std::endl;
    std::cout << "--------------------" << std::endl;

    std::cout << "1. Gain +6 HP" << std::endl;
    std::cout << "2. Roll 1d10 +2 for new HP" << std::endl;
    std::cout << "Make a selection: " << std::endl;

    while (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::string message = "Enter a valid option";
        ClearBuffer(message);
    }

    switch (choice) {
        case 1: {
            m_maxHealth += 6;
            std::cout << "Calculating new HP." << std::endl;
            std::string message = "Press enter to continue.";
            ClearBuffer(message);
            break;
        }
        case 2: {
            std::string message = "Press enter to roll dice.";
            ClearBuffer(message);
            dice = (rand() % 10) + 1;
            std::cout << "You rolled a " << dice << " + 2." << std::endl;
            std::cout << "Press enter to continue." << std::endl;
            std::cin.get();
            m_maxHealth += (dice + 2);
            break;
        }

        default:
            break;
    }

    m_health = m_maxHealth;
    m_maxExp += 100;
}

bool Player::IsPlayerAlive() {
    return m_health > 0;
}

void Player::DamagePlayer(int damage) {
    m_health -= damage;
}

void Player::UsePotion() {
    if (m_potion == 0) {
        std::cout << "You are out of potions. Buy more at the store." << std::endl;
        return;
    }

    if (m_health == m_maxHealth) {
        std::cout << "You already have full health" << std::endl;
        return;
    }

    int healthGain = m_maxHealth / 4;
    m_potion -= 1;
    std::cout << "You drink a health potion." << std::endl;

    int newHealth = m_health + healthGain;
    m_health = (newHealth >= m_maxHealth ? m_maxHealth : newHealth);
}

void Player::SetPotion(int numberOfPotion) {
    std::cout << "You acquired " << numberOfPotion << (numberOfPotion == 1 ? " new potion." : " new potions.") << std::endl;
    m_potion += numberOfPotion;
}

void Player::PrintStats() {
    std::cout << "-------------------" << std::endl;
    std::cout << m_name << " Lvl: " << m_level << " (" << m_exp << " / " << m_maxExp << " ) XP" << std::endl;
    std::cout << "HP: " << m_health << " / " << m_maxHealth << std::endl;
    std::cout << "Weapon: " << m_weapon->GetName() << std::endl;
    std::cout << "Potions: " << m_potion << std::endl;;
    std::cout << "Gold: " << m_gold << std::endl;
    std::cout << "-------------------" << std::endl;
}

std::string Player::GetName() {
    return m_name;
}

int Player::Attack() {
    int weaponDamage = 0;
    weaponDamage = (rand()% m_weapon->GetDamage()) + m_weapon->GedBonusDamage();
    std::cout << "You attack with your " << m_weapon->GetName() << std::endl;
    std::cout << "It deals " << weaponDamage << " damage." << std::endl;
    return weaponDamage;
}

void Player::SetWeapon(std::shared_ptr<Weapon> weapon) {
    std::cout << "You purchased " << weapon->GetName() << std::endl;
    std::cout << "Its damage is (1d" << weapon->GetDamage() << " + " << weapon->GedBonusDamage() << ")" << std::endl;
    m_weapon = weapon;
}

void Player::SetGold(int gold) {
    m_gold += gold;
}

void Player::LootEnemy(std::shared_ptr<Enemy> enemy) {
    int enemyLevel = enemy->GetLevel();
    int dropedGold = (rand() % 5) + enemy->GetLevel();
    int dropedPotion;
    std::cout << "The " << enemy->GetName() << " dropped: " << dropedGold << " gold." << std::endl;

    if (m_level > enemyLevel) {
        SetExp(5);
        dropedPotion = (rand() % 30);
    }
    else {
        SetExp(20);
        dropedPotion = (rand() % 20);
    }

    if (dropedPotion == 0) {
        std::cout << "It also dropped a potion." << std::endl;
        m_potion += 1;
    }

    SetGold(dropedGold);

    std::cout << "Press Enter to continue.";
    std::cin.ignore();
    std::cin.get();
}

int Player::PlayerChoice() {
    PrintStats();

    std::cout << "1. Enter the Bugs Cave." << std::endl;
    std::cout << "2. Enter the Erros Cavern." << std::endl;
    std::cout << "3. Enter the UBDragon Lair." << std::endl;
    std::cout << "4. Enter the store." << std::endl;
    std::cout << "5. Drink Potion." << std::endl;
    std::cout << "0. Exit the game." << std::endl;

    int choice;

    while (!(std::cin >> choice) || ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5) && (choice != 0))) {
        std::cout << "Enter a valid option." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return choice;
}

void Player::EnterToDungeon(std::shared_ptr<Enemy> enemy) {
    std::cout << "A " << enemy->GetName() << " appears. Get ready to the battle." << std::endl;

    while (IsPlayerAlive() && enemy->IsEnemyAlive()) {
        int choice;

        PrintStats();
        std::cout << enemy->GetName() << " Lvl: " << enemy->GetLevel() << std::endl;
        std::cout << "HP: " << enemy->GetHealth() << " / " << enemy->GetMaxHealth() << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Drink Potion" << std::endl;
        std::cout << "0. Retreat to Town" << std::endl;
        std::cout << "Choose an option." << std::endl;

        while (!(std::cin >> choice) || (choice != 1 && choice != 2 && choice != 0)) {
            std::cout << "Enter valid option" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
            case 1:
                enemy->TakeDamage(Attack());
                if (enemy->IsEnemyAlive()) {
                    DamagePlayer(enemy->Attack());
                    break;
                }
                else {
                    LootEnemy(enemy);
                    break;
                }
            case 2:
                UsePotion();
                DamagePlayer(enemy->Attack());
                break;
            case 0:
                break;
            default:
                break;
        }

    }
}

void Player::EnterToStore() {
    PrintStats();
    std::cout << "Welcome to the store." << std::endl;

    bool isStoreActive = true;

    while (isStoreActive) {
        std::cout << "1. Potion" << std::endl;
        std::cout << "2. Sword" << std::endl;
        std::cout << "3. Axe" << std::endl;
        std::cout << "4. STACKOWERFLOWER" << std::endl;
        std::cout << "0. Leave the store." << std::endl;
        std::cout << "Make selection." << std::endl;

        int choice;

        while (!(std::cin >> choice) || (choice != 1 && choice != 2 && choice != 2 && choice != 4 && choice != 0)) {
            std::cout << "Enter a valid option" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << std::endl;

        int cost;

        switch (choice)
        {
            case 1:
                cost = 10;

                if (m_gold < cost) {
                    std::cout << "You dont have enought gold for that." << std::endl;
                }
                else {
                    m_gold -= cost;
                    SetPotion(1);
                }

                break;

            case 2:
                cost = 20;

                if (m_gold < cost) {
                    std::cout << "You dont have enought gold for that." << std::endl;
                }
                else {
                    std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>("Sword", 8, 4);
                    m_gold -= cost;
                    SetWeapon(weapon);
                }

                break;

            case 3:
                cost = 40;

                if (m_gold < cost) {
                    std::cout << "You dont have enought gold for that." << std::endl;
                }
                else {
                    std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>("Axe", 10, 6);
                    m_gold -= cost;
                    SetWeapon(weapon);
                }

            case 4:
                cost = 60;

                if (m_gold < cost) {
                    std::cout << "You dont have enought gold for that." << std::endl;
                }
                else {
                    std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>("STACKOWERFLOWER", 14, 8);
                    m_gold -= cost;
                    SetWeapon(weapon);
                }

                break;

            case 0:
                isStoreActive = false;
                std::cout << "You leave the store." << std::endl;
                break;

            default:
                break;
        }
    }
}



