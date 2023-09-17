#include <string>
#include <variant>
#include <functional>
#include "Game/texthandler.h"
#include <nlohmann/json.hpp>

#define JSON nlohmann::json

//Logic storage for moving between rooms
struct Path{
    
};

//Logic storage for character interactions within rooms
struct Interaction{

};

struct None{

};

typedef std::variant<Path, Interaction, None> Functionality;

//Rooms
class Room{
    public:
    std::string name;
    std::string description;

    void SetButtonOneFunctionality(Functionality functionality);
    void SetButtonTwoFunctionality(Functionality functionality);
    void SetButtonThreeFunctionality(Functionality functionality);
    void SetButtonFourFunctionality(Functionality functionality);
    void SetButtonFiveFunctionality(Functionality functionality);
    void SetButtonSixFunctionality(Functionality functionality);
    void SetButtonSevenFunctionality(Functionality functionality);
    void SetButtonEightFunctionality(Functionality functionality);
    void SetButtonNineFunctionality(Functionality functionality);
    void SetButtonTenFunctionality(Functionality functionality);
    void SetButtonElevenFunctionality(Functionality functionality);
    void SetButtonTwelveFunctionality(Functionality functionality);
    void SetButtonThirteenFunctionality(Functionality functionality);
    void SetButtonFourteenFunctionality(Functionality functionality);
    void SetButtonFifteenFunctionality(Functionality functionality);
    void SetButtonSixteenFunctionality(Functionality functionality);
    void SetButtonSeventeenFunctionality(Functionality functionality);
    void SetButtonEighteenFunctionality(Functionality functionality);
    void SetButtonFunctionality(Functionality functionality, int number);

    void LoadRoom(); //Communicates to the TextHandler and ButtonManager to tie correct text, button functions and events to display

    void ParseJSON(JSON json); //Parses the json data to create and initialize the room correctly


    private:
    //Button Functions
    Functionality button_one; //For Q
    Functionality button_two; //For W
    Functionality button_three; //For E
    Functionality button_four; //For R
    Functionality button_five; //For T
    Functionality button_six; //For Y
    Functionality button_seven; //For A
    Functionality button_eight; //For S
    Functionality button_nine; //For D
    Functionality button_ten; //For F
    Functionality button_eleven; //For G
    Functionality button_twelve; //For H
    Functionality button_thirteen; //For Z
    Functionality button_fourteen; //For X
    Functionality button_fifteen; //For C
    Functionality button_sixteen; //For V
    Functionality button_seventeen; //For B
    Functionality button_eighteen; //For N 

    int PullRoomNumber(const std::string& string);

    public:
    //Base constructor
    Room(const std::string& room_name = "", const std::string& room_description = "") : name(room_name), description(room_description){
        button_one = None();
        button_two = None();
        button_three = None();
        button_four = None();
        button_five = None();
        button_six = None();
        button_seven = None();
        button_eight = None();
        button_nine = None();
        button_ten = None();
        button_eleven = None();
        button_twelve = None();
        button_thirteen = None();
        button_fourteen = None();
        button_fifteen = None();
        button_sixteen = None();
        button_seventeen = None();
        button_eighteen = None();
    }
};
