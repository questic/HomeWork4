#pragma once
#include <string>
#include "Weapon.h"

class Enemy {
private:
    std::string m_name;
    int m_health;
    int m_maxHealth;
    int m_level;
    std::shared_ptr<Weapon> m_weapon;
public:
    Enemy(std::string name, int health, int maxHealth, int level, std::shared_ptr<Weapon> weapon);

    int Attack();
    int GetHealth();
    int GetMaxHealth();
    std::string GetName();
    int GetLevel();


    void SetHealth(int health);
    void TakeDamage(int damage);

    bool IsEnemyAlive();

};