
#include "gui.h"

ImGuiWindowFlags fixed = /*ImGuiWindowFlags_NoTitleBar*/ ImGuiWindowFlags_NoCollapse /*| ImGuiWindowFlags_NoSavedSettings*/ /*| ImGuiWindowFlags_NoResize*/ | ImGuiWindowFlags_NoMove /*| ImGuiWindowFlags_MenuBar*/ | ImGuiWindowFlags_AlwaysAutoResize;

void GUI::SHIP_DETAILS(const char* shipDetails_char[4], int shipDetails_int[5], /*const char* state[2],*/ sf::Texture* ship_image)
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), NULL);
	ImGui::SetNextWindowSize(ImVec2(450, 540), NULL);
	ImGui::Begin(shipDetails_char[NAME], NULL, fixed);
	ImGui::Text("Class: %s", shipDetails_char[CLASS]);
	ImGui::Text("Location: %s", shipDetails_char[LOCATION]);
	ImGui::Text("Health: %d", shipDetails_int[HEALTH]);
	ImGui::Text("Fuel: %d", shipDetails_int[FUEL]);
	ImGui::Text("Speed: %d", shipDetails_int[SPEED]);
	ImGui::Text("Cargo: %d", shipDetails_int[CARGO]);
	ImGui::Text("Destination: %s", shipDetails_char[DESTINATION]);
	ImGui::Text("Distance: %d", shipDetails_int[DISTANCE]);
	//ImGui::Text(state);
	ImGui::Image(*ship_image, ImVec2(350, 350));
	ImGui::End();
}

int GUI::COURSE(const char* shipDetails_char[4], int shipDetails_int[5], /*const char* state[2],*/ sf::Texture* ship_image, int ship_index, int station_index, std::vector<stationStats> stations_vec, std::vector<shipStats> active, sf::Texture* station_image)
{
	int flightPlan_x = 450; int flightPlan_y = 540; ImVec2 flightPlane_Size(flightPlan_x, flightPlan_y);
	ImGui::SetNextWindowPos(ImVec2(450, 0), NULL);
	ImGui::SetNextWindowSize(flightPlane_Size, NULL);
	ImGui::Begin("FLIGHT PLANNER", NULL, fixed);
	ImGui::Text("LOCATION: %s", shipDetails_char[LOCATION]);
	ImGui::Text("DESTINATION:", shipDetails_char[DESTINATION]);
	ImGui::Text("DISTANCE: %d", stations_vec.at(station_index).adjacents->at(0).second); //ImGui::SameLine();

	if (ImGui::BeginCombo("##", stations_vec.at(ship_index).destinationBuffer, NULL))
	{
		for (int selectable = 0; selectable < 3; selectable++)
		{
			if (ImGui::Selectable(stations_vec.at(selectable).name))
			{
				station_index = selectable;
				active.at(ship_index).destination = stations_vec.at(selectable).name;
				stations_vec.at(ship_index).destinationBuffer = stations_vec.at(selectable).name;
				active.at(ship_index).target_distance += stations_vec.at(station_index).adjacents->at(0).second;

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
		printf("LAUNCHED %s \n", active.at(ship_index).name);
		active.at(ship_index).docked = false;
		active.at(ship_index).statusIndex = 1;
	}
	ImGui::Spacing(); ImGui::SameLine((window_x - 400) / 2); // 300 Image x
	ImGui::Image(*station_image, ImVec2(400, 400));
	ImGui::End();
	return active.at(ship_index).target_distance;
}

void GUI::MARKET(market* market, std::vector<shipStats> &active, int ship_index)
{
    // MARKET TABLE
    ImGui::SetNextWindowPos(ImVec2(900, 0), NULL);
    ImGui::SetNextWindowSize(ImVec2(1020, 540), NULL);
    ImGui::Begin("MARKET", NULL, NULL);
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
                ImGui::PushID(market[row].name);
                switch (column)
                {
                case 0:
                    ImGui::Text("%s", market[row].id);
                    break;
                case 1:
                    ImGui::Text("%d", market[row].weight);
                    break;
                case 2:
                    ImGui::Text("%d", market[row].price);
                    break;
                case 3:
                    ImGui::Text("%d", market[row].quantity);
                    break;
                case 4:

                    if (ImGui::Button("+10"))
                    {
                        market[row].increment = 10;
                        market[row].row_total = market[row].marketRowStaging(market[row].row_total, market[row].increment);
                        //market[row].load_total = market[row].row_total;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("+25"))
                    {
                        market[row].increment = 25;
                        market[row].row_total = market[row].marketRowStaging(market[row].row_total, market[row].increment);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("+50"))
                    {
                        market[row].increment = 50;
                        market[row].row_total = market[row].marketRowStaging(market[row].row_total, market[row].increment);
                        printf("%d", market[row].row_total);
                    }
                    market[row].increment = 0;

                    ImGui::SameLine();
                    ImGui::Text("%d", market[row].row_total);
                }
                ImGui::PopID();
            }
        }
        ImGui::EndTable();

        ImGui::Spacing(); // Requiremnt of SameLine Spacing argument.
        ImGui::SameLine(926); // ^
        if (ImGui::Button(" LOAD ALL "))
        {
            active.at(ship_index).cargo += active.at(ship_index).cargoStage;
            printf("%d", active.at(ship_index).cargo);
            // Reset Loader
            for (int i = 0; i < 5; i++)
            {
                active.at(ship_index).cargo += market[i].row_total;
                market[i].row_total = 0;
                market[i].load_total = 0;
            }
            active.at(ship_index).cargoStage = 0;
        }
    }
    ImGui::End();
}

void GUI::FLEET(std::vector<shipStats> &active, int ship_index)
{
    // ACTIVE FLEET TABLE
    ImGui::SetNextWindowPos(ImVec2(0, 540), NULL);
    ImGui::SetNextWindowSize(ImVec2(1920, 540), NULL);
    ImGui::Begin("ACTIVE FLEET", NULL, NULL);// begin window
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
                        ship_index = row;
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
                    active.at(row).distance_cal(active.at(row).travel_delta);
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
}