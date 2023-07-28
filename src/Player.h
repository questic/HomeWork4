#pragma once
#include <string>
#include <memory>
#include "Weapon.h"
#include "Enemy.h"

class Player {
private:
    std::string m_name;
    int m_health;
    int m_maxHealth;
    int m_exp;
    int m_maxExp;
    int m_level;
    int m_potion;
    int m_gold;
    std::shared_ptr<Weapon> m_weapon;

public:
    Player(std::string name, int health, int maxHealth, int exp, int maxExp, int level, int potion, int gold, std::shared_ptr<Weapon> weapon);
    void SetExp(int exp);
    void UpLevel();
    void SetPotion(int numberOfPotion);
    void SetWeapon(std::shared_ptr<Weapon> weapon);
    void SetGold(int gold);

    std::string GetName();
    void PrintStats();

    int Attack();
    void UsePotion();
    void LootEnemy(std::shared_ptr<Enemy> enemy);
    bool IsPlayerAlive();
    void DamagePlayer(int damage);
    int PlayerChoice();
    void EnterToDungeon(std::shared_ptr<Enemy> enemy);
    void EnterToStore();


};



