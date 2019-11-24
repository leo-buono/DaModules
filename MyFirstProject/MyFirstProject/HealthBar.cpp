#include "HealthBar.h"
#include <iostream>
#include <string>



HealthBar::HealthBar()
{

}

HealthBar::HealthBar(float health)
{
	m_Health = health;
}

HealthBar::~HealthBar()
{
}
void HealthBar::DisplayHealth()
{
	std::cout << "Health : " << std::to_string((m_Health * 100.f)) << "%" << std::endl;
}

float HealthBar::GetHealth() const
{
	return m_Health;
}

float HealthBar::SetHealth(float health)
{
	m_Health = health;
	return health;
}
