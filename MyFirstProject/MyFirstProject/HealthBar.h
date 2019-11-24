#pragma once
#include "JSON.h"
class HealthBar
{
public:
	//creates Healthbar
	HealthBar();
	//Health Value
	HealthBar(float health);
	//Destroys Healthbar
	~HealthBar();

	//Displays Health
	void DisplayHealth();

	//getters
	float GetHealth() const; 
	//setter
	float SetHealth(float health);


private:
	float m_Health = 5.f;
};
//sends Healthbar to json file 
inline void to_json(nlohmann::json& j, const HealthBar& bar)
{
	j["Health"] = bar.GetHealth();
}
inline void from_json(const nlohmann::json& j, HealthBar& bar)
{
	bar.SetHealth(j["Health"]);
}

