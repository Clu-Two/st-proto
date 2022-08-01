#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui-SFML.h" // SFML ImGui includes
#include "imgui.h"
#include "imgui_internal.h"
#include "..\sqlite3\sqlite3.h"

#include <stdio.h>
#include <iostream>
#include <set>
#include <cstdio>
#include <cmath>   
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

#include "windows.h"

#include "destinations.h"
#include "fleet.h"

// All Preparations
// Load all Assets
// Load Database
// Load Save Game


class Index
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
};

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
//enum ShipDetails_char
//{
//	NAME,
//	CLASS,
//	LOCATION,
//	DESTINATION
//};
//enum ShipDetails_int
//{
//	HEALTH,
//	FUEL,
//	SPEED,
//	DISTANCE,
//	CARGO
//};
//ImGuiWindowFlags fixed = /*ImGuiWindowFlags_NoTitleBar*/ ImGuiWindowFlags_NoCollapse /*| ImGuiWindowFlags_NoSavedSettings*/ /*| ImGuiWindowFlags_NoResize*/ | ImGuiWindowFlags_NoMove /*| ImGuiWindowFlags_MenuBar*/ | ImGuiWindowFlags_AlwaysAutoResize;
//class GUI
//{
//public:
//	enum ShipDetails_char
//	{
//		NAME,
//		CLASS,
//		LOCATION,
//		DESTINATION
//	};
//	enum ShipDetails_int
//	{
//		HEALTH,
//		FUEL,
//		SPEED,
//		DISTANCE,
//		CARGO
//	};
//
//	void details_panel(const char* shipDetails_char[4], int shipDetails_int[5], /*const char* state[2],*/ sf::Texture* ship_image);
//	int planner_panel(const char* shipDetails_char[4], int shipDetails_int[5], /*const char* state[2],*/ sf::Texture* ship_image, int ship_index, int station_index, std::vector<stationStats> stations_vec, std::vector<shipStats> active, sf::Texture* station_image);
//
//	//void details_panel(const char* shipDetails_char[4], int shipDetails_int[5], /*const char* state[2],*/ sf::Texture* ship_image)
//	//{
//	//	ImGui::SetNextWindowPos(ImVec2(0, 0), NULL);
//	//	ImGui::SetNextWindowSize(ImVec2(450, 540), NULL);
//	//	ImGui::Begin(shipDetails_char[NAME], NULL, fixed);
//	//	ImGui::Text("Class: %s",shipDetails_char[CLASS]);
//	//	ImGui::Text("Location: %s", shipDetails_char[LOCATION]);
//	//	ImGui::Text("Health: %d", shipDetails_int[HEALTH]);
//	//	ImGui::Text("Fuel: %d",shipDetails_int[FUEL]);
//	//	ImGui::Text("Speed: %d",shipDetails_int[SPEED]);
//	//	ImGui::Text("Cargo: %d",shipDetails_int[CARGO]);
//	//	ImGui::Text("Destination: %s", shipDetails_char[DESTINATION]);
//	//	ImGui::Text("Distance: %d",shipDetails_int[DISTANCE]);
//	//	//ImGui::Text(state);
//	//	ImGui::Image(*ship_image, ImVec2(350, 350));
//	//	ImGui::End();
//	//}
//	//int planner_panel(const char* shipDetails_char[4], int shipDetails_int[5], /*const char* state[2],*/ sf::Texture* ship_image, int ship_index, int station_index, std::vector<stationStats> stations_vec, std::vector<shipStats> active, sf::Texture* station_image)
//	//{
//	//	int flightPlan_x = 450; int flightPlan_y = 540; ImVec2 flightPlane_Size(flightPlan_x, flightPlan_y);
//	//	ImGui::SetNextWindowPos(ImVec2(450, 0), NULL);
//	//	ImGui::SetNextWindowSize(flightPlane_Size, NULL);
//	//	ImGui::Begin("FLIGHT PLANNER", NULL, fixed);
//	//	ImGui::Text("LOCATION: %s", shipDetails_char[LOCATION]);
//	//	ImGui::Text("DESTINATION:", shipDetails_char[DESTINATION]);
//	//	ImGui::Text("DISTANCE: %d", stations_vec.at(station_index).adjacents->at(0).second); //ImGui::SameLine();
//
//	//	if (ImGui::BeginCombo("##", stations_vec.at(indexO.selectedShip).destinationBuffer, NULL))
//	//	{
//	//		for (int selectable = 0; selectable < 3; selectable++)
//	//		{
//	//			if (ImGui::Selectable(stations_vec.at(selectable).name))
//	//			{
//	//				indexO.selectedStation = selectable;
//	//				active.at(indexO.selectedShip).destination = stations_vec.at(selectable).name;
//	//				stations_vec.at(indexO.selectedShip).destinationBuffer = stations_vec.at(selectable).name;
//	//				active.at(indexO.selectedShip).target_distance += stations_vec.at(indexO.selectedStation).adjacents->at(0).second;
//
//	//			}
//	//		}
//	//		ImGui::EndCombo();
//	//	}
//	//	//ImGui::SameLine();
//
//	//	// Center LAUNCH Button
//	//	// Get Window Size, Set LAUNCH Button Size, Calculate Diffferent divide by 2
//
//	//	int window_x = ImGui::GetCurrentWindow()->Size.x;
//	//	ImVec2 launch_ButtonSize(60, 20);
//	//	ImGui::Spacing(); ImGui::SameLine((window_x - launch_ButtonSize.x) / 2);
//	//	if (ImGui::Button("LAUNCH", launch_ButtonSize))
//	//	{
//	//		printf("LAUNCHED %s \n", active.at(indexO.selectedShip).name);
//	//		active.at(indexO.selectedShip).docked = false;
//	//		active.at(indexO.selectedShip).statusIndex = 1;
//	//	}
//	//	ImGui::Spacing(); ImGui::SameLine((window_x - 400) / 2); // 300 Image x
//	//	ImGui::Image(*station_image, ImVec2(400, 400));
//	//	ImGui::End();
//	//	return active.at(indexO.selectedShip).target_distance;
//	//}
//
//};

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

