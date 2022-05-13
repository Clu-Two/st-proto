

#include "imgui-SFML.h" // SFML ImGui includes
#include "imgui.h"
#include "imgui_internal.h"
#include "..\sqlite3\sqlite3.h"

#include "windows.h"

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR) / sizeof(*(_ARR))))     // Size of a static C-style array. Don't use on pointers!
#define IMGUI_CDECL __cdecl

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

#include "main.h"

void MenuBar_File()
{
    ImGui::MenuItem("Save");
    ImGui::MenuItem("Load");
    ImGui::MenuItem("Open");
}
void File_MenuDrop()
{
    if (ImGui::BeginMenu("File"))
    {
        MenuBar_File();
        ImGui::EndMenu();
    }
}

int row_current = NULL;
//shipStats* agamemnon = new shipStats(), * agrippa = new shipStats();



int main(int argc, char** argv)
{

    bool open_queue = false;

    // Start SFML Window
    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "", sf::Style::None);
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    //sf::Color Transparent;
    float color[3] = { 0.f, 0.f, 0.f };

    ImGuiWindowFlags fixed = /*ImGuiWindowFlags_NoTitleBar*/ ImGuiWindowFlags_NoCollapse /*| ImGuiWindowFlags_NoSavedSettings*/ /*| ImGuiWindowFlags_NoResize*/ | ImGuiWindowFlags_NoMove /*| ImGuiWindowFlags_MenuBar*/ | ImGuiWindowFlags_AlwaysAutoResize;
    ImGuiWindowFlags child_grid = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
    ImGuiWindowFlags galaxy_map_format = /*ImGuiWindowFlags_NoTitleBar*/ ImGuiWindowFlags_NoCollapse /*| ImGuiWindowFlags_NoSavedSettings*/ /*| ImGuiWindowFlags_NoResize*/ | ImGuiWindowFlags_NoMove /*| ImGuiWindowFlags_MenuBar*/ | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImGuiWindowFlags notification_popup = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
    const char* windowTitle = "Star Trader";

    window.setTitle(windowTitle);
    window.resetGLStates();



    sf::Clock travel_clock;
    sf::Clock travel_delta;
    sf::Time light_seconds = sf::seconds(1);
    sf::Int32 travel_update = 1;
    //travel_update = sf::seconds(1);
    //sf::Clock Clock;
    sf::Clock deltaClock;

    static bool menu_items = false;
    static bool open_window = false;
    static bool launch_ship = false;
    static bool recall_ship = false;
    static bool selected = false;

    //static bool open_cargo_window = false;
    //ships_db ships_db_obj;
    //ships_list ships_list_obj;

    //shipStats* agamemnon = new shipStats(), * agrippa = new shipStats();
    //shipStats agamemnon, agrippa;

    // Objects

    // (x, y, w) —> edge from `x` to `y` having weight `w`
    //std::vector<Edge> edges = { {0, 1, 6},  {1, 0, 6}, {1, 2, 7}, {2, 1, 7}, {2, 0, 5}, {0, 2, 5}, {2, 3, 10}, {3, 2, 10} };

    // total number of nodes in the graph (labelled from 0 to )
    int n = 4;

    // construct graph
    //Graph graph(edges, n);

    // print adjacency list representation of a graph
    //printGraph(graph, n);

//SET OBJECTS

    Assets assets;
    //SET SHIP VARIABLES
//shipStats* agamemnon = new shipStats{ "North - Star", "Agamemnon", 1, 100, 400, 0, 0 };
shipStats agamemnon("North - Star", "Agamemnon", 1, 100, 400, 0, 0);
assets.pshipDisplay[0].loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\St\\St_space_gate\\x64\\Debug\\assets\\images\\agamemnon.png");
//shipStats* agrippa = new shipStats{"West Marina", "Agrippa", 2, 80, 200, 0, 0};
shipStats agrippa("West Marina", "Agrippa", 2, 80, 200, 0, 0);
assets.pshipDisplay[1].loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\St\\St_space_gate\\x64\\Debug\\assets\\images\\agrippa.png");
std::vector<shipStats> active;
active.push_back(agamemnon);
active.push_back(agrippa);


// SET STATION VARIABLES
stationStats io( "Io", 0, 2, 2);
stationStats phobos("Phobos", 1, 2, 1);
stationStats titan("Titan", 2, 4, 4);

assets.pstationDisplay[0].loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\St\\St_space_gate\\x64\\Debug\\assets\\images\\moon_phobos.png");
assets.pstationDisplay[1].loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\St\\St_space_gate\\x64\\Debug\\assets\\images\\moon_io.png");
assets.pstationDisplay[2].loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\St\\St_space_gate\\x64\\Debug\\assets\\images\\moon_titan.png");
//titan.photo->loadFromFile("assets\\images\\moon_titan.png");


// Graph
phobos.adjacents[0].push_back(std::make_pair(io.station_id, 10));
io.adjacents[0].push_back(std::make_pair(phobos.station_id, 30));
io.adjacents[1].push_back(std::make_pair(titan.station_id, 100));
titan.adjacents[0].push_back(std::make_pair(io.station_id, 50));


std::vector<stationStats> STATIONS = { phobos, io, titan };
std::vector<const char*> stationNames = { phobos.name, io.name, titan.name };
std::vector<int> stationID = { phobos.station_id, io.station_id, titan.station_id };
//Station StationO;
//StationO.Stations(STATIONS);
          
        //std::cout << STATIONS.at(1).adjacents[0].at(0).first << std::endl;
        //std::cout << STATIONS.at(1).adjacents[0].at(0).second << std::endl;
        //std::cout << STATIONS.at(1).adjacents[1].at(0).first << std::endl;
        //std::cout << STATIONS.at(1).adjacents[1].at(0).second << std::endl;

//for (int i = 0; i < assets.station_count; i++)
//{
//    assets.texture_loader(assets.pstationDisplay[i], assets.texture_files[i]);
//}


// MARKET DATA
market steel("STEEL", "##Steel", 100, 150, 700);
market radon("RADON", "##Steel", 1, 10, 1000);
market graphene("GRAPHENE", "##Steel", 10, 300, 200);
market fcells("F-CELLS", "##Steel", 1000, 800, 10);
market kryptonite("KRYPTONITE", "##Steel", 70, 90, 160);

market* marketO[5];
marketO[0] = &steel;
marketO[1] = &radon;
marketO[2] = &graphene;
marketO[3] = &fcells;
marketO[4] = &kryptonite;

//market[0].name = "STEEL";
//market[0].id = "##Steel";
//market[0].weight = 100;
//market[0].price = 150;
//market[0].quantity = 700;
//
//market[1].name = "RADON";
//market[1].id = "##Radon";
//market[1].weight = 1;
//market[1].price = 10;
//market[1].quantity = 1000;
////
//market[2].name = "GRAPHENE";
//market[2].id = "##Graphene";
//market[2].weight = 10;
//market[2].price = 300;
//market[2].quantity = 200;
////
//market[3].name = "F-CELLS";
//market[3].id = "##Fcells";
//market[3].weight = 1000;
//market[3].price = 800;
//market[3].quantity = 10;
////
//market[4].name = "KRYPTONITE";
//market[4].id = "##Kryptonite";
//market[4].weight = 70;
//market[4].price = 90;
//market[4].quantity = 160;


while (window.isOpen())
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    // Start IMGUI Window
    ImGui::SFML::Update(window, deltaClock.restart());
   
  
    // SHIP DETAIL WINDOW
    ImGui::SetNextWindowPos(ImVec2(0, 0), NULL);
    ImGui::SetNextWindowSize(ImVec2(450, 540), NULL);
    ImGui::Begin(active.at(indexO.selectedShip).name, NULL, fixed);
    ImGui::Text("Class: %s", active.at(indexO.selectedShip).shipClass);
    ImGui::Text("Cargo: %d", active.at(indexO.selectedShip).cargo);
    ImGui::Text("Health: %d", active.at(indexO.selectedShip).health);
    ImGui::Text("Fuel: %d", active.at(indexO.selectedShip).fuel);
    ImGui::Text("Speed: %d", active.at(indexO.selectedShip).speed);
    ImGui::Text("Location: %s", active.at(indexO.selectedShip).location);
    ImGui::Text("Destination: %s", active.at(indexO.selectedShip).destination);
    ImGui::Text("Distance: %d", active.at(indexO.selectedShip).target_distance);
    ImGui::Text("Status: %s", active.at(indexO.selectedShip).status[active.at(indexO.selectedShip).statusIndex]);
    ImGui::Image(assets.pshipDisplay[indexO.selectedShip], ImVec2(350, 350));
    ImGui::End();

    // FLIGHT PLANNER
    int flightPlan_x = 450;
    int flightPlan_y = 540;
    ImVec2 flightPlane_Size(flightPlan_x, flightPlan_y);
    ImGui::SetNextWindowPos(ImVec2(450, 0), NULL);
    ImGui::SetNextWindowSize(flightPlane_Size, NULL);
    ImGui::Begin("FLIGHT PLANNER", NULL, fixed);
    ImGui::Text("LOCATION: %s", active.at(indexO.selectedShip).location);
    ImGui::Text("DESTINATION:");
    ImGui::Text("DISTANCE: %d", STATIONS.at(indexO.selectedStation).adjacents->at(0).second); //ImGui::SameLine();

    if (ImGui::BeginCombo("##", STATIONS.at(indexO.selectedShip).destinationBuffer, NULL)) 
    {
        for (int selectable = 0; selectable < 3; selectable++)
        {
            if (ImGui::Selectable(STATIONS.at(selectable).name))
            {
                indexO.selectedStation = selectable;
                active.at(indexO.selectedShip).destination = STATIONS.at(selectable).name;
                STATIONS.at(indexO.selectedShip).destinationBuffer = STATIONS.at(selectable).name;
                active.at(indexO.selectedShip).target_distance += STATIONS.at(indexO.selectedStation).adjacents->at(0).second;
 
            }
        }
        ImGui::EndCombo();
    }
    //ImGui::SameLine();
  
    // Center LAUNCH Button
    // Get Window Size, Set LAUNCH Button Size, Calculate Diffferent divide by 2

    int window_x = ImGui::GetCurrentWindow()->Size.x;
    ImVec2 launch_ButtonSize(60, 20);
    ImGui::Spacing(); ImGui::SameLine((window_x - launch_ButtonSize.x) / 2);
    if (ImGui::Button("LAUNCH", launch_ButtonSize))
    {
        printf("LAUNCHED");
        active.at(indexO.selectedShip).docked = false;
        active.at(indexO.selectedShip).statusIndex = 1;
    }
    ImGui::Spacing(); ImGui::SameLine((window_x - 400) / 2); // 300 Image x
    ImGui::Image(assets.pstationDisplay[indexO.selectedStation], ImVec2(400, 400));
    ImGui::End();

    active.at(indexO.selectedShip).statusIndex = active.at(indexO.selectedShip).status_check(active.at(indexO.selectedShip).statusIndex, active.at(indexO.selectedShip).target_distance);
    active.at(indexO.selectedShip).docked = active.at(indexO.selectedShip).is_docked(active.at(indexO.selectedShip).docked, active.at(indexO.selectedShip).statusIndex);
    // MARKET TABLE
    ImGui::SetNextWindowPos(ImVec2(900, 0), NULL);
    ImGui::SetNextWindowSize(ImVec2(1020, 540), NULL);
    ImGui::Begin("MARKET", NULL, fixed);
    int marketData = 5;
    int commodities = 5;
    if (ImGui::BeginTable("COMMODITIES", marketData, ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupColumn("NAME", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("WEIGHT", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("PRICE", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("QUANTITY", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("LOAD", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableHeadersRow();
        for (int row = 0; row < commodities; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < marketData; column++)
            {
                if (!ImGui::TableSetColumnIndex(column) && column > 0)
                    continue;
                ImGui::PushID(marketO[row]->id);
                switch (column)
                {
                case 0:
                    ImGui::Text("%s", marketO[row]->name);
                    break;
                case 1:
                    ImGui::Text("%d", marketO[row]->weight);
                    break;
                case 2:
                    ImGui::Text("%d", marketO[row]->price);
                    break;
                case 3:
                    ImGui::Text("%d", marketO[row]->quantity);
                    break;
                case 4:

                    if (ImGui::Button("+10"))
                    {
                        indexO.increment = 10;
                        marketO[row]->row_total = indexO.marketRowStaging(marketO[row]->row_total, indexO.increment);
                        //marketO[row]->load_total = marketO[row]->row_total;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("+25"))
                    {
                        indexO.increment = 25;
                        marketO[row]->row_total = indexO.marketRowStaging(marketO[row]->row_total, indexO.increment);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("+50"))
                    {
                        indexO.increment = 50;
                        marketO[row]->row_total = indexO.marketRowStaging(marketO[row]->row_total, indexO.increment);
                        printf("%d", marketO[row]->row_total);
                    }
                    indexO.increment = 0;

                    ImGui::SameLine();
                    ImGui::Text("%d", marketO[row]->row_total);
                }
                ImGui::PopID();
            }
        }
            ImGui::EndTable();

            ImGui::Spacing(); // Requiremnt of SameLine Spacing argument.
            ImGui::SameLine(926); // ^
            if (ImGui::Button(" LOAD ALL "))
            {
                active.at(indexO.selectedShip).cargo += active.at(indexO.selectedShip).cargoStage;
                printf("%d", active.at(indexO.selectedShip).cargo);
                // Reset Loader
                for (int i = 0; i < 5; i++)
                {
                    active.at(indexO.selectedShip).cargo +=  marketO[i]->row_total;
                    marketO[i]->row_total = 0;
                    marketO[i]->load_total = 0;
                }
                active.at(indexO.selectedShip).cargoStage = 0;
            }

     }
    ImGui::End();

    // ACTIVE FLEET TABLE
    ImGui::SetNextWindowPos(ImVec2(0, 540), NULL);
    ImGui::SetNextWindowSize(ImVec2(1920, 540), NULL);
    ImGui::Begin("ACTIVE FLEET", NULL, fixed);// begin window
    if (ImGui::BeginTable("Ship Table", 8, ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupColumn("NAME", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("CARGO");
        ImGui::TableSetupColumn("HEALTH", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("FUEL");
        ImGui::TableSetupColumn("DISTANCE");
        ImGui::TableSetupColumn("SPEED", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("STATUS");
        ImGui::TableSetupColumn("CLASS", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableHeadersRow();
        for (int row = 0; row < 2; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 7; column++)
            {
                if (!ImGui::TableSetColumnIndex(column) && column > 0)
                    continue;
                ImGui::PushID(row);
                switch (column)
                {
                case 0:
                    if (ImGui::Selectable(active.at(row).name))
                    {
                        indexO.selectedShip = row;
                    }
                    break;
                case 1:
                    ImGui::Text("%d", active.at(row).cargo);
                    break;
                case 2:
                    ImGui::Text("%d", active.at(row).health);
                    break;
                case 3:
                    ImGui::Text("%d", active.at(row).fuel);
                    break;
                case 4:
                    ImGui::Text("%d", active.at(row).target_distance);
                    active.at(row).distance_cal(travel_delta);
                    break;
                case 5:
                    ImGui::Text("%d", active.at(row).speed);
                    break;
                case 6:
                    ImGui::Text("%s", active.at(row).status[0]); // Status not set
                    break;
                case 7:
                    ImGui::Text("%s", active.at(row).shipClass);
                    break;
                }
                ImGui::PopID();
            }
        }
            ImGui::EndTable();
    }
    ImGui::End();

       //sf::Time micro = sf::microseconds(10000);
       //sf::Time milli = sf::milliseconds(10);
       //sf::Time seconds = sf::seconds(1.0f);

    //if (Clock.getElapsedTime().asSeconds() >= 5.0f)
    //{
    //    ship_stats_obj.update(SLB[row_current]);
    //    Clock.restart();
    //}

    // Clocks
    if (travel_delta.getElapsedTime().asSeconds() >= 0.1f)
    {
        // ship.update(current);
        //active.at(indexO.selectedShip).update(active.at(indexO.selectedShip));
        //STATIONS.at(indexO.selectedStation).adjacents->at(0).second;
        //active.at(indexO.selectedShip).update();
        travel_delta.restart();
    }
    deltaClock.restart();


    window.clear();
    ImGui::SFML::Render(window); // Call this to render the gui you defined in your update
    window.display();
}
active.at(indexO.selectedShip).~shipStats();
ImGui::SFML::Shutdown(); // Call when you want to shutdown imgui

        return 0;
}

void shipStats::distance_cal(sf::Clock travel_delta)
{
    if (travel_delta.getElapsedTime().asSeconds() >= 0.1f)
    {
        if (target_distance > 0 && !docked)
        {
            target_distance -= 0.5f;
            std::cout << target_distance << std::endl;
        }
    }
    travel_delta.restart();
}

shipStats::~shipStats()
{
}