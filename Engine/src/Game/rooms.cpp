#include <variant>
#include "Game/rooms.h"
#include <nlohmann/json.hpp>
#include <string>
#include <Game/interface.h>
#include <helper.hpp>



#define JSON nlohmann::json

void Room::SetButtonOneFunctionality(Functionality functionality) {
    button_one = functionality;
}

void Room::SetButtonTwoFunctionality(Functionality functionality) {
    button_two = functionality;
}

void Room::SetButtonThreeFunctionality(Functionality functionality) {
    button_three = functionality;
}

void Room::SetButtonFourFunctionality(Functionality functionality) {
    button_four = functionality;
}

void Room::SetButtonFiveFunctionality(Functionality functionality) {
    button_five = functionality;
}

void Room::SetButtonSixFunctionality(Functionality functionality) {
    button_six = functionality;
}

void Room::SetButtonSevenFunctionality(Functionality functionality) {
    button_seven = functionality;
}

void Room::SetButtonEightFunctionality(Functionality functionality) {
    button_eight = functionality;
}

void Room::SetButtonNineFunctionality(Functionality functionality) {
    button_nine = functionality;
}

void Room::SetButtonTenFunctionality(Functionality functionality) {
    button_ten = functionality;
}

void Room::SetButtonElevenFunctionality(Functionality functionality) {
    button_eleven = functionality;
}

void Room::SetButtonTwelveFunctionality(Functionality functionality) {
    button_twelve = functionality;
}

void Room::SetButtonThirteenFunctionality(Functionality functionality) {
    button_thirteen = functionality;
}

void Room::SetButtonFourteenFunctionality(Functionality functionality) {
    button_fourteen = functionality;
}

void Room::SetButtonFifteenFunctionality(Functionality functionality) {
    button_fifteen = functionality;
}

void Room::SetButtonSixteenFunctionality(Functionality functionality) {
    button_sixteen = functionality;
}

void Room::SetButtonSeventeenFunctionality(Functionality functionality) {
    button_seventeen = functionality;
}

void Room::SetButtonEighteenFunctionality(Functionality functionality) {
    button_eighteen = functionality;
}

void Room::SetButtonFunctionality(Functionality functionality, int number) {
    switch (number) {
        case 1: SetButtonOneFunctionality(functionality); break;
        case 2: SetButtonTwoFunctionality(functionality); break;
        case 3: SetButtonThreeFunctionality(functionality); break;
        case 4: SetButtonFourFunctionality(functionality); break;
        case 5: SetButtonFiveFunctionality(functionality); break;
        case 6: SetButtonSixFunctionality(functionality); break;
        case 7: SetButtonSevenFunctionality(functionality); break;
        case 8: SetButtonEightFunctionality(functionality); break;
        case 9: SetButtonNineFunctionality(functionality); break;
        case 10: SetButtonTenFunctionality(functionality); break;
        case 11: SetButtonElevenFunctionality(functionality); break;
        case 12: SetButtonTwelveFunctionality(functionality); break;
        case 13: SetButtonThirteenFunctionality(functionality); break;
        case 14: SetButtonFourteenFunctionality(functionality); break;
        case 15: SetButtonFifteenFunctionality(functionality); break;
        case 16: SetButtonSixteenFunctionality(functionality); break;
        case 17: SetButtonSeventeenFunctionality(functionality); break;
        case 18: SetButtonEighteenFunctionality(functionality); break;
        default: throw std::invalid_argument("Invalid button number");
    }
}

void Room::LoadRoom() {
    // Code for loading the room
}

void Room::ParseJSON(const JSON json) {
    // Code for parsing JSON data and initializing the room

    //We already have the name and description, which is required for each room
    if(json.contains("room")){
        //We know that there is a room, but are there multiple?
        if(json["room"].is_array()){
            //There are multiple!
        } else {
            //It's a singular room

            //We're gonna pull the button number and then set it to move to the room when pressed
            std::string entrance = json["room"]["entrance"];
            int room_number = PullRoomNumber(entrance);

            std::string file_name = json["room"]["file_name"];

            //Now we just construct the functionality
            Functionality functionality = Path();

            ButtonEvent new_event = [file_name](){
                TextHandler::RequestLoad(file_name);
            };

            ButtonManager::SetButtonFunctionality(new_event, room_number);
        }
    }
}

int Room::PullRoomNumber(const std::string& string){

    std::string cmp = to_lower(string);

    if(cmp.compare("1") == 0){
        return 1;
    } else 
    if(cmp.compare("2") == 0){
        return 2;
    } else 
    if(cmp.compare("3") == 0){
        return 3;
    } else 
    if(cmp.compare("4") == 0){
        return 4;
    } else 
    if(cmp.compare("5") == 0){
        return 5;
    } else 
    if(cmp.compare("6") == 0){
        return 6;
    } else 
    if(cmp.compare("7") == 0){
        return 7;
    } else 
    if(cmp.compare("8") == 0){
        return 8;
    } else 
    if(cmp.compare("9") == 0){
        return 9;
    } else 
    if(cmp.compare("10") == 0){
        return 10;
    } else 
    if(cmp.compare("11") == 0){
        return 11;
    } else 
    if(cmp.compare("12") == 0){
        return 12;
    } else 
    if(cmp.compare("13") == 0){
        return 13;
    } else 
    if(cmp.compare("14") == 0){
        return 14;
    } else 
    if(cmp.compare("15") == 0){
        return 15;
    } else 
    if(cmp.compare("16") == 0){
        return 16;
    } else 
    if(cmp.compare("17") == 0){
        return 17;
    } else 
    if(cmp.compare("18") == 0){
        return 18;
    }

    throw std::invalid_argument("Button number is invalid");
}
