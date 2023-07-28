#pragma once
#include <string>
#include <memory>

class Weapon {
private:
    std::string m_name;
    int m_damage;
    int m_bonusDamage;
public:
    Weapon(std::string name, int damage, int bonusDamage);
    std::string GetName();
    int GetDamage();
    int GedBonusDamage();
};