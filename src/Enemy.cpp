#include "Enemy.h"
#include <string>
#include <iostream>

Enemy::Enemy(std::string name, int health, int maxHealth, int level, std::shared_ptr<Weapon> weapon) :
        m_name(name), m_health(health), m_maxHealth(maxHealth), m_level(level), m_weapon(weapon) {

}

int Enemy::Attack() {
    int damage = 0;

    damage = (rand() % m_weapon->GetDamage() + m_weapon->GedBonusDamage());
    std::cout << m_name << " attacks you with a " << m_weapon->GetName() << std::endl;
    std::cout << "It deals " << damage << " damage." << std::endl;

    return damage;
}

int Enemy::GetHealth() {
    return m_health;
}

int Enemy::GetMaxHealth() {
    return m_maxHealth;
}

std::string Enemy::GetName() {
    return m_name;
}

int Enemy::GetLevel() {
    return m_level;
}

void Enemy::TakeDamage(int damage) {
    m_health -= damage;
}

bool Enemy::IsEnemyAlive() {
    return m_health > 0;
}

