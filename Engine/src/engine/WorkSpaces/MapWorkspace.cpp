#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "MapWorkspace.h"
#include <string>
#include <filesystem>
#include "engine/mainwindow.h"



char map_name_input[16];

void MapWorkspace::CreateNewMapPrompt(){

    ImGui::Begin("Create New Map");

    ImGui::InputText("Map Name", map_name_input, sizeof(map_name_input), ImGuiInputTextFlags_EnterReturnsTrue);

    if(ImGui::Button("Create")){
        CreateNewMapFolder(std::string(map_name_input));
        PopupHandler::ClearEvents();
        MainWindow::current_window = MapWindow(NodeGraph(), map_name_input);
    }
    ImGui::SameLine();
    if(ImGui::Button("Cancel")){
        PopupHandler::ClearEvents();
    }

    ImGui::SetWindowSize(ImVec2(300, 150));

    ImGui::End();

}

void MapWorkspace::CreateNewMapFolder(const std::string& map_name){
    std::string directory_path = "JSONS/Maps/" + map_name;
    std::filesystem::create_directory(directory_path);
}

void MapWorkspace::OpenWorkspaceWindow(){

    std::filesystem::path path = "JSONS/Maps";

    ImGui::Begin("Map Directories");

    int num = 0;

    // Check if the path exists and is a directory
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            // Check if the entry is a directory
            if (entry.is_directory()) {
                // Get the directory name and display it as a selectable menu item
                std::string directoryName = entry.path().filename().string();
                if (ImGui::Selectable(directoryName.c_str())) {
                    // Handle selection here
                    // You can store the selected directory path or perform any other desired action

                    //We, for now, just want to open up the workspace but we will communicate to the workspace what directory we are in
                    PopupHandler::ClearEvents();
                    MainWindow::current_window = MapWindow(NodeGraph(), directoryName);

                }
                num++;
            }
        }
    }

    //We're going to assume each directory takes up about 50 units of space:
    ImGui::SetWindowSize(ImVec2(100, 50 * num));

    ImGui::End();
}