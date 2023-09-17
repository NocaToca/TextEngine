#include "Game/texthandler.h"
#include "Game/rooms.h"
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>


std::string TextHandler::starting_room = std::string("main_room");
std::string TextHandler::current_room = TextHandler::starting_room;

Room TextHandler::current_room_information = Room();
int TextHandler::current_char = 0;

//Now we must load the current room
void TextHandler::RequestLoad(const std::string& file_name){
    std::ifstream file("Rooms/" + file_name + ".json");
    if(!file.is_open()){
        throw std::invalid_argument("Unknown Room Name");
        return;
    }

    //Storing the file into the json object
    nlohmann::json json_data; 
    file >> json_data;
    
    //Now we can extract the data from the JSON object
    std::string room_name = json_data["name"];
    std::string description = json_data["description"];

    //just have to update the current room and it's information
    current_room = room_name;
    current_room_information = Room(room_name, description);
    current_room_information.ParseJSON(json_data);

    current_char = 0;

    file.close();
}


std::string TextHandler::PullDescription(bool scroll_text){

    if(current_room_information.name == ""){
        RequestLoad(current_room);
    }

    if(scroll_text){
        //Make sure the current char doesn't go above the desired amount
        current_char = (current_room_information.description.length() >= current_char) ? current_room_information.description.length() : current_char;
        return current_room_information.description.substr(0, current_char++);
    } else {
        return current_room_information.description;
    }
}
