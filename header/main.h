#pragma once

#include <stdio.h>
#include <vector>
#include <sstream>
#include <set>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

class index
{
public:
	int selectedShip = 0;
	int selectedStation = 0;
	int increment = 0;
	int marketRowStaging(int row_total, int increment)
	{
		row_total += increment;
		return row_total;
	}

}indexO;

struct Assets
{
	// Stations
	static const int station_count = 3;
	sf::Texture phobos, io,titan;
	sf::Texture stationDisplay[station_count] = {phobos, io, titan};
	sf::Texture* pstationDisplay = stationDisplay;

	// Ships
	static const int ship_count = 2;
	sf::Texture agamemnon, agrippa;
	sf::Texture shipDisplay[ship_count] = { agamemnon,agrippa };
	sf::Texture* pshipDisplay = shipDisplay;
	//void texture_loader(sf::Texture& tex, const char* texture_files)
	//{
	//	tex.loadFromFile(texture_files);
	//	std::cout << texture_files << std::endl;
	//}
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

} phobos, io, titan;


//struct Station 
//{
//	//Station(int vertex, std::set<int> adjacents) : vertex_number(vertex), adjacents(adjacents) {}
//	void Stations(std::vector<stationStats> &obj)
//	{
//		for (auto a = obj.begin(); a != obj.end(); a++)
//		{
//			std::cout << &a << std::endl;
//		}
//
//	}
//	std::set<stationStats> adjacents;
//};






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
	const char* location = {"Earth"};
	const char* destination = { "N/A" };
	bool docked = true;
	int target_distance = 0;

	int distance_cal(int target_distance, bool docked)
	{
		if (target_distance > 0 && !docked)
		{
			target_distance -= 0.5f;
			std::cout << target_distance << std::endl;
		}
		return target_distance;
	}

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

	int update(shipStats &active)
	{
		active.target_distance = distance_cal(active.target_distance, active.docked);

		return active.target_distance;
	}

	//const char* status[2] = { stateDocked, stateInFlight };
}/**agamemnon, *agrippa*/;

class shipsClass
{
public:
	//shipStats agamemnon, agrippa;
	//std::vector<shipStats> active = { agamemnon, agrippa };
};


//class star_graph
//{
//public:
//	std::vector<stationStats> stations = { phobos, morpheus, titan };
//	void addEdge(std::vector<stationStats> adj[], int u,stationStats stations)
//	{
//		adj[u].push_back(stations);
//		adj[v];
//	}
//	int n;
//
//};

struct market
{
	const char* name = { "N/A" };
		const char* id = { "N/A" };
		int weight = 0;
		int price = 0;
		int quantity = 0;
		int row_total = 0;
		int load_total = 0;
}market[5];


// Weighted Directed Graph
//struct Edge
//{
//	int source, destination, distance;
//};
//
//typedef std::pair<int, int> Pair;
//
//class Graph
//{
//public:
//	std::vector<std::vector<Pair>> adjList;
//	Graph(std::vector<Edge> const& edges, int n)
//	{
//		// resize the vector to hold `n` elements of type vector<Edge>
//		adjList.resize(n);
//
//		// add edges to the directed graph
//		for (auto& edge : edges)
//		{
//			int source = edge.source;
//			int destination = edge.destination;
//			int distance = edge.distance;
//
//			adjList[source].push_back(std::make_pair(destination, distance));
//		}
//	}
//};
//
//void printGraph(Graph const& graph, int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		// Function to print all neighboring vertices of a given vertex
//		for (Pair v : graph.adjList[i]) {
//			std::cout << "(" << i << ", " << v.first << ", " << v.second << ") ";
//		}
//		std::cout << std::endl;
//	}
//}

// Node Graph
// 
//struct Node
//{
//	bool noPass = false;
//	Node* origin = nullptr; // explorer node
//	std::vector<Node*> connections; // connected nodes
//
//};

//class Grid
//{
//public:
//	static const int SIZE = 5;
//	stationStats* spaceMap[SIZE][SIZE];
//	stationStats* start = nullptr;
//	stationStats* target = nullptr;
//	std::vector<stationStats*> path;
//	std::string spaceGrid =
//		"x x x x x"
//		"x 0 1 x x"
//		"x x 2 x x"
//		"x x x x x"
//		"x x x x x"
//		;
//	void nodeReader(std::vector<stationStats> &obj)
//	{
//		std::stringstream ss(spaceGrid, std::ios::in);
//		for (int i = 0; i < 3; i++)
//		{
//			for (int x = 0; x < SIZE; x++)
//			{
//				for (int y = 0; y < SIZE; y++)
//				{
//					char buffer;
//					stationStats* STATION = new stationStats();
//					ss >> buffer;
//					if (buffer == 'x')
//					{
//						STATION->noPass = true;
//					}
//					spaceMap[x][y] = &STATION[i];
//					std::cout << STATION << std::endl;
//				}
//			}
//		}
//
//		// Connect the Nodes
//		for (int x = 0; x < SIZE; x++)
//		{
//			for (int y = 0; y < SIZE; y++)
//			{
//				if ((x - 1) >= 0)
//				{
//					spaceMap[x][y]->connections.push_back(spaceMap[x - 1][y]);
//				}
//				if ((x + 1) <= SIZE -1)
//				{
//					spaceMap[x][y]->connections.push_back(spaceMap[x + 1][y]);
//				}
//				if ((y - 1) >= 0)
//				{
//					spaceMap[x][y]->connections.push_back(spaceMap[x][y - 1]);
//				}
//				if ((y + 1) <= SIZE -1)
//				{
//					spaceMap[x][y]->connections.push_back(spaceMap[x][y + 1]);
//				}
//			}
//		}
//	}
//	//void displayMap()
//	//{
//	//	for (int x = 0; x < SIZE; x++)
//	//	{
//	//		for (int y = 0; y < SIZE; y++)
//	//		{
//	//			if (spaceMap[x][y]->noPass)
//	//			{
//	//				std::cout << char(254) << " ";
//	//
//	//			}
//	//			else
//	//			{
//	//				std::cout << "  ";
//	//			}
//	//		}
//	//		std::cout << std::endl;
//	//	}
//	//}
//
//};

