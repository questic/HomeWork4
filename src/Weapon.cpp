#include "Weapon.h"

Weapon::Weapon(std::string name, int damage, int bonusDamage) : m_name(name), m_damage(damage), m_bonusDamage(bonusDamage) {

}

std::string Weapon::GetName() {
    return m_name;
}

int Weapon::GetDamage() {
    return m_damage;
}

int Weapon::GedBonusDamage() {
    return m_bonusDamage;
}