#pragma once

#include <SFML/System/Clock.hpp>
class shipStats
{
public:
	const char* name = { "N/A" };
	const char* newShip[100] = { "N/A" };
	const char* shipClass = { "N/A" };
	int health = 100;
	int fuel = 1000;
	int speed = 0;
	int cargo = 0;
	int cargoStage = 0;
	int cargoCap = 10;
	int index = 0;
	const char* stateDocked = { "Docked" };
	const char* stateInFlight = { "In Flight" };
	int statusIndex = 0;
	int bay = 0;
	const char* bayChar = "N/A";
	const char* status[2] = { "Docked", "In Flight" };
	const char* location = { "Earth" };
	const char* destination = { "N/A" };
	bool docked = true;
	int target_distance = 0;
	int* target_distancePointer = &target_distance;

	sf::Clock travel_delta;

	void distance_cal(sf::Clock travel_delta);
	/*int distance_cal(int target_distance, bool docked)
	{
		if (target_distance > 0 && !docked)
		{
			target_distance -= 0.5f;
			std::cout << target_distance << std::endl;
		}
		return target_distance;
	}*/

	int status_check(int statusIndex, int target_distance)
	{
		if (target_distance <= 0)
		{
			statusIndex = 0;
		}
		return statusIndex;
	}

	bool is_docked(bool docked, int statusIndex)
	{
		if (statusIndex == 0)
		{
			docked = true;
		}
		if (statusIndex == 1)
		{
			docked = false;
		}
		return docked;
	}

	void setVec()
	{
		shipStats agamemnon("North - Star", "Agamemnon", 1, 100, 400, 0, 0);
		shipStats agrippa("West Marina", "Agrippa", 2, 80, 200, 0, 0);
		std::vector<shipStats> active;
		active.push_back(agamemnon);
		active.push_back(agrippa);
	}

	//void update();

	//int update(shipStats &active)
	//{
	//	active.target_distance = distance_cal(active.target_distance, active.docked);
	//
	//	return active.target_distance;
	//}
	const char* shipDetails_char[4] = {name, shipClass, location, destination};
	int shipDetails_int[5] = {health, fuel, speed, *target_distancePointer, cargo};
	shipStats(const char* n, const char* c, int i, int h, int f, int ca, int ct)
	{
		name = n;
		shipClass = c;
		index = i;
		health = h;
		fuel = f;
		cargo = ca;
		cargo = ct;
	}
	~shipStats();
};