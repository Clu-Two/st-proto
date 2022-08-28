#pragma once

#include "main.h"
#include "market.h"

class GUI
{
public:
	const char* station_index_match(int station_index)
	{
		const char* station_name = { "N/A" };
		if (station_index == 1)
		{
			station_name = { "Io" };
		}
		if (station_index == 2)
		{
			station_name = { "Phobos" };
		}
		if (station_index == 3)
		{
			station_name = { "Titan" };
		}

		return station_name;
	}
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

	void SHIP_DETAILS(std::vector<shipStats>& active, /*const char* state[2],*/ sf::Texture* ship_image, int selectedShip, std::string destination, int destination_distance);
	std::pair<std::string, int> ROUTE(const char* shipDetails_char[4], int shipDetails_int[5], /*const char* state[2],*/ sf::Texture* ship_image, int ship_index, int station_index, std::vector<stationStats> stations_vec, std::vector<shipStats> active, sf::Texture* station_image, const char* destinationBuffer);
	void MARKET(market* market, std::vector<shipStats> &active, int ship_index);
	int FLEET(std::vector<shipStats> &active, int ship_index);
};