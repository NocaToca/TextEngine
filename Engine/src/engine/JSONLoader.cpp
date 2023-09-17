#include "mainwindow.h"
#include "JSONLoader.h"
#include "imgui/imgui.h"

#include "nlohmann/json.hpp"

#include <fstream>

using json = nlohmann::json;

void JSONLoader::SaveAllNodes(std::vector<Node> nodes, std::string name_space){
    for(const auto& node: nodes){
        printf("Saving a node...\n");
        SaveNode(node, name_space);
    }
}

std::vector<Node> JSONLoader::LoadAllNodes(std::string name_space){
    std::vector<Node> nodes;

    std::string directory_path = "JSONS/Maps/" + name_space;
    std::filesystem::directory_iterator end_itr;

    for(std::filesystem::directory_iterator itr(directory_path); itr != end_itr; ++itr){
        if(std::filesystem::is_regular_file(itr->path())){
            std::string file_path = itr->path().string();
            std::string file_name = itr->path().filename().string();

            if(file_name.find(".json") != std::string::npos){
                Node node_loaded = LoadNode(file_path);
                nodes.push_back(node_loaded);
            }
        }
    }

    return nodes;
}

Node JSONLoader::LoadNode(std::string file_path){

    std::ifstream json_file(file_path);

    if(!json_file){
        printf("File does not exist!");
    }

    json json_data = json::parse(json_file);

    //Let's start extracting for the node
    std::string node_name = json_data["name"];
    ImVec2 global_position = ImVec2(json_data["global_position"]["x"], json_data["global_position"]["y"]);
    ImVec2 size = ImVec2(json_data["size"]["x"], json_data["size"]["y"]);

    Node node = Node(global_position, size, node_name);

    json links_data = json_data["links"];
    for(const auto& link : links_data){
        std::string link_name = link["link_name"];
        ImVec2 position = ImVec2(link["base_position"]["x"], link["base_position"]["y"]);

        Node* parent_node = &node;
        Link* connected_node = nullptr; //We'll have to deal with saving connections another time; it'll have to be saved and then scanned through once all the nodes have been loaded into the space

        Direction link_direction = link["placed_direction"];

        Link constructed_link = Link(link_name, position, parent_node, connected_node, link_direction);
        node.AddLink(constructed_link);
    }

    return node;
}

void JSONLoader::SaveNode(Node node, std::string name_space){
    json json_data;

    // try{
    //     //Let's set the data
    //     json_data["name"] = node.label;
    // }catch(std::bad_alloc bad_alloc){
    //     printf("Name");
    // }
    // try{
    //     json_data["global_position"]["x"] = node.global_position.x;
    //     json_data["global_position"]["y"] = node.global_position.y;
    // }catch(std::bad_alloc bad_alloc){
    //     printf("Position");
    // }
    // try{
    //     json_data["size"]["x"] = node.size.x;
    //     json_data["size"]["y"] = node.size.y;
    // }catch(std::bad_alloc bad_alloc){
    //     printf("Size");
    // }

    // int num = 0;
    // json link_data_json = json::array();
    // for (const auto& link : node.links) {
    //     json link_data;
    //     try{
    //         link_data["link_name"] = link.link_name;
            
    //     }catch(std::bad_alloc bad_alloc){
    //     printf("\n " + num);
    //         printf("Link Name");
    //     }
    //     try{
    //         link_data["base_position"]["x"] = link.base_position.x;
    //         link_data["base_position"]["y"] = link.base_position.y;
    //     }catch(std::bad_alloc bad_alloc){
    //     printf("\n " + num);
    //         printf("Link Position");
    //     }
    //     try{
    //         link_data["parent_node"] = node.label;
    //     }catch(std::bad_alloc bad_alloc){
    //         printf("\n %d", num);
    //         printf("Label");
    //     }
    //     try{
    //         link_data["connected_node"] = "nullptr";
    //     }catch(std::bad_alloc bad_alloc){
    //     printf("\n " + num);
    //         printf("Connected Node");  
    //     }
        
    //     try{
    //         link_data["placed_direction"] = link.placed_direction;
    //     }catch(std::bad_alloc bad_alloc){
    //     printf("\n " + num);
    //         printf("Placed direction");
    //     }

    //     try{
    //         link_data_json.push_back(link_data);

    //     }catch(std::bad_alloc bad_alloc){
    //     printf("\n " + num);
    //         printf("Vector push??");
    //     }
    //     num++;
    // }

    // json_data["links"] = link_data_json;
    
    // try{
    //     std::string file_path = "JSONS/Maps/";
    //     file_path.append(name_space);
    //     file_path.append("/");
    //     file_path.append(node.label);
    //     file_path.append(".json");

    //     std::ofstream json_file(file_path, std::ofstream::out | std::ofstream::trunc);
    //     if(json_file.is_open()){
    //         json_file << std::setw(4) << json_data <<std::endl;
    //         json_file.close();
    //     }
    // }catch(std::bad_alloc bad_alloc){
    //     printf("Something in the files");
    // }
    // Let's set the data
    json_data["name"] = node.label;
    json_data["global_position"]["x"] = node.global_position.x;
    json_data["global_position"]["y"] = node.global_position.y;
    json_data["size"]["x"] = node.size.x;
    json_data["size"]["y"] = node.size.y;

    json link_data_json = json::array();
    for (const auto& link : node.links) {
        json link_data;
        link_data["link_name"] = link.link_name;
        link_data["base_position"]["x"] = link.base_position.x;
        link_data["base_position"]["y"] = link.base_position.y;
        link_data["parent_node"] = node.label;
        link_data["connected_node"] = "nullptr";
        link_data["placed_direction"] = link.placed_direction;

        link_data_json.push_back(link_data);
    }

    json_data["links"] = link_data_json;

    std::string file_path = "JSONS/Maps/";
    file_path.append(name_space);
    file_path.append("/");
    file_path.append(node.label);
    file_path.append(".json");

    std::ofstream json_file(file_path, std::ofstream::out | std::ofstream::trunc);
    if(json_file.is_open()){
        json_file << std::setw(4) << json_data <<std::endl;
        json_file.close();
    }
}

