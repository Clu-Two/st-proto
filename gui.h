#pragma once

#include "main.h"
#include "market.h"

class GUI
{

private:
	enum ShipDetails_char
	{
		NAME,
		CLASS,
		LOCATION,
		DESTINATION
	};
	enum ShipDetails_int
	{
		HEALTH,
		FUEL,
		SPEED,
		DISTANCE,
		CARGO
	};

public:

	void SHIP_DETAILS(const char* shipDetails_char[4], int shipDetails_int[5], /*const char* state[2],*/ sf::Texture* ship_image);
	int COURSE(const char* shipDetails_char[4], int shipDetails_int[5], /*const char* state[2],*/ sf::Texture* ship_image, int ship_index, int station_index, std::vector<stationStats> stations_vec, std::vector<shipStats> active, sf::Texture* station_image);
	void MARKET(market* market, std::vector<shipStats> &active, int ship_index);
	void FLEET(std::vector<shipStats> &active, int ship_index);
};