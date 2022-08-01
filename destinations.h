#pragma once
#include <vector>

enum station_index : int
{
	None,
	Io,
	Phobos,
	Titan
};

class stationStats
{

public:
	static const int numberOf_stations = 3;
	static const int links = 2;
	int station_id = 0;
	const char* name = { "N/A" };
	int bays = 4;
	int fuelPrice = 1;
	const char* destinationBuffer = { "N/A" };
	std::vector<std::pair<int, int>> adjacents[links];

	stationStats(const char* n, int i, int fpr, int b)
	{
		name = n;
		station_id = i;
		fuelPrice = fpr;
		bays = b;
	}
};



