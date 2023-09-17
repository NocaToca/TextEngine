//This basically just does a bunch of the handling for the primary text displayed by the main screen
#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#include <string>
#include <variant>
#include <functional>
#include <nlohmann/json.hpp>

class Room;

class TextHandler{

    public:
    static std::string starting_room; //This is the room that the game will start on, default will almost always be the title screen
    static std::string current_room; //The current room that the player is in
    static void RequestLoad(const std::string& room_name);
    static std::string PullDescription(bool scroll_text = true);
    
    private:
    static Room current_room_information; //The information of the room retrieved from the JSON parse
    static int current_char;

};

#endif
