#include "mainwindow.h"
#include "engine/WorkSpaces/MapWorkspace.h"

#include <string>
#include <filesystem>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "JSONLoader.h"

const ImGuiWindowFlags main_window = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

Action ControllerVisitor::queued_action =  [](){};
Link* ControllerVisitor::selected_link = nullptr;

WindowType MainWindow::current_window = DefaultWindow();

bool Controller::node_displayed = false;

void WindowVisitor::operator()(DefaultWindow& default_window){
    // Handle DefaultWindow
    default_window.DisplayMainWindow(SCR_WIDTH, SCR_HEIGHT);
    // ...
}

void WindowVisitor::operator()(MapWindow& map_window) {
    // Handle MapWindow
    map_window.DisplayMainWindow(SCR_WIDTH, SCR_HEIGHT);
    // ...
}

void ShowMainToolBar(){
    // Toolbar options
        if (ImGui::BeginMenuBar()){
            if (ImGui::BeginMenu("Settings")){
                if (ImGui::MenuItem("Save")){
                    // Handle "Settings" option selected
                    
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Map")){
                if(ImGui::MenuItem("Open")){
                    PopupHandler::ChangeEvent([](){
                        MapWorkspace::OpenWorkspaceWindow();
                    });
                }
                if(ImGui::MenuItem("Create")){
                    PopupHandler::ChangeEvent( [](){
                        MapWorkspace::CreateNewMapPrompt();
                    });
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
}


void DefaultWindow::DisplayMainWindow(int scr_width, int scr_height){
     ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::Begin("Toolbar Window", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        ShowMainToolBar();

        // Window content
        ImGui::Text("Hello! Welcome to the base engine. To get started, head to a workspace by either opening or creating a map!");

        ImGui::SetWindowSize(ImVec2(scr_width, scr_height));

        ImGui::End();
}

MapWindow::MapWindow(NodeGraph graph, std::string name_space){
    main_node_graph = graph;

    main_node_graph.SetNodes(JSONLoader::LoadAllNodes(name_space));

    this->name_space = name_space;

    viewport_center = ImVec2(0,0);
}

WindowEvents draw_queue = [](){

};

void MapWindow::DisplayMainWindow(int scr_width, int scr_height){
    ImGui::SetNextWindowPos(ImVec2(0,0));

    ImGui::Begin("Map Editor", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    if (ImGui::BeginMenuBar()){
            if (ImGui::BeginMenu("Settings")){
                if (ImGui::MenuItem("Save")){
                    // Handle "Settings" option selected
                    printf("Saving!");
                    JSONLoader::SaveAllNodes(main_node_graph.nodes, name_space);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Map")){
                if(ImGui::MenuItem("Open")){
                    PopupHandler::ChangeEvent( [](){
                        MapWorkspace::OpenWorkspaceWindow();
                    });
                }
                if(ImGui::MenuItem("Create")){
                    PopupHandler::ChangeEvent( [](){
                        MapWorkspace::CreateNewMapPrompt();
                    });
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

    ImGui::BeginChild("Node Window", ImVec2(scr_width, scr_height), false);

    //Call the node graph to draw it's nodes
    main_node_graph.DisplayNodes(viewport_center, ImVec2(SCR_WIDTH, SCR_HEIGHT));
    draw_queue(); //Handles drawing to the main workspace, generally used to display link stuff
    draw_queue = [](){}; //Then we just pop the draw queue

    ImGui::EndChild();

    ImGui::SetWindowSize(ImVec2(scr_width, scr_height));

    

    ImGui::End();
}

WindowEvents PopupHandler::null_event = [](){};
bool PopupHandler::active = false;

void Controller::CallLinkCreateWindow(Node& node){
    ImGui::Begin("Create Link");
    ImGui::Text("Please select the orientation for the link to appear on!");
    if(ImGui::Button("North")){
        node.CreateAndAddLink(Direction::North);
        PopupHandler::ClearEvents();
    }
    ImGui::SameLine();
    if(ImGui::Button("East")){
        node.CreateAndAddLink(Direction::East);
        PopupHandler::ClearEvents();
    }
    ImGui::SameLine();
    if(ImGui::Button("South")){
        node.CreateAndAddLink(Direction::South);
        PopupHandler::ClearEvents();
    }
    ImGui::SameLine();
    if(ImGui::Button("West")){
        node.CreateAndAddLink(Direction::West);
        PopupHandler::ClearEvents();
    }
    ImGui::SetWindowSize(ImVec2(500, 300));
    ImGui::End();
}

//Popup function
void Controller::CallLinkEditWindow(Node& node){
    ImGui::Begin("Link Edit");

    if(ImGui::Button("Create")){
        PopupHandler::ChangeEvent( [&node](){
            CallLinkCreateWindow(node);
        });
    }
    ImGui::SameLine();
    if(ImGui::Button("Cancel")){
        CallNodeInformationWindow(node);
    }

    ImGui::SetWindowSize(ImVec2(500, 300));

    ImGui::End();
}

bool Controller::buffer_input = false;

//Popup function
void Controller::CallNodeInformationWindow(Node& node){
    PopupHandler::active = true; //Depricated?
    PopupHandler::ChangeEvent( [&node](){
        ImGui::Begin("Node Information");
        PopupHandler::active = ImGui::IsWindowFocused();

        //First let's display the name:
        std::string display_name = "Name: ";
        display_name.append(node.label);
        ImGui::Text(display_name.c_str());
        ImGui::SameLine();
        if(ImGui::Button("Change")){
            //To be implemented
        }

        //We *could* display the size and position, but thats dead information
        //We do, however, want to display the links
        std::string display_links_num = "Links: ";
        int number_of_links = node.links.size();
        
        display_links_num.append(std::to_string(number_of_links));
        ImGui::Text(display_links_num.c_str());

        ImGui::SameLine();
        if(ImGui::Button("Edit")){
            Controller::buffer_input = true;
            PopupHandler::ChangeEvent( [&node](){CallLinkEditWindow(node);});
        }

        ImGui::SetWindowSize(ImVec2(300, 500));

        ImGui::End();

        node_displayed = true;
    });
}

void ControllerVisitor::PopEvents(){
    PopupHandler::ClearEvents();
}

char text_input[16];

void ControllerVisitor::ShowCreateNodeMenu(MapWindow& map_window){
    PopupHandler::ClearEvents();
    ImVec2 cursor_position = ImGui::GetMousePos();

    PopupHandler::ChangeEvent( [cursor_position, &map_window](){
        ImGui::Begin("Create Menu");
        ImGui::SetWindowPos(cursor_position);

        if(ImGui::Button("Create", ImVec2 (60, 50))){
            PopupHandler::ChangeEvent( [cursor_position, &map_window](){
                ImGui::Begin("Create Node");
                ImGui::SetWindowPos(cursor_position);


                ImGui::InputText("Node Name", text_input, sizeof(text_input), ImGuiInputTextFlags_EnterReturnsTrue);

                if(ImGui::Button("Create")){
                    map_window.main_node_graph.AddNode(Node(ImVec2(cursor_position.x - map_window.viewport_center.x, cursor_position.y - map_window.viewport_center.y), ImVec2(100, 100), text_input));
                    PopupHandler::ClearEvents();
                }
                ImGui::SameLine();
                if(ImGui::Button("Cancel")){
                    PopupHandler::ClearEvents();
                }

                ImGui::SetWindowSize(ImVec2(300, 150));

                ImGui::End();

            });
        }

        ImGui::SetWindowSize(ImVec2(100, 100));
        ImGui::End();
    });
}


void ControllerVisitor::HandleLinkAttachment(Link* selected_link, MapWindow& map_window){
    ImVec2 link_position = selected_link->base_position;
    ImVec2 mouse_position = imgui_IO.MousePos;

    selected_link->AttemptAttach(map_window.main_node_graph.FindLinkToAttachTo(selected_link, mouse_position), true);

    //Now we essentially just tell our window to draw the lines - for now at least.
    draw_queue = [link_position, mouse_position, selected_link](){
        // Get the ImGui draw list
        ImDrawList* draw_list = ImGui::GetWindowDrawList();


        if(selected_link->connected_node == nullptr){
            // Draw the horizontal line
            draw_list->AddLine(ImVec2(link_position.x, link_position.y), ImVec2(mouse_position.x, link_position.y), ImGui::GetColorU32(ImVec4(0.0f,1.0f,0.0f, 1.0f)), 10.0f);

            // Draw the vertical line
            draw_list->AddLine(ImVec2(mouse_position.x, link_position.y), mouse_position, ImGui::GetColorU32(ImVec4(0.0f,1.0f,0.0f, 1.0f)), 10.0f);
        }
        
    };
}