#include "Game/interface.h"
#include <iostream>


ButtonEvent ButtonManager::button_one_event = [](){
    printf("Button one pressed!\n");
};

ButtonEvent ButtonManager::button_two_event = [](){
    printf("Button two pressed!\n");
};

ButtonEvent ButtonManager::button_three_event = [](){
    printf("Button three pressed!\n");
};

ButtonEvent ButtonManager::button_four_event = [](){
    printf("Button four pressed!\n");
};

ButtonEvent ButtonManager::button_five_event = [](){
    printf("Button five pressed!\n");
};

ButtonEvent ButtonManager::button_six_event = []() {
    printf("Button six pressed!\n");
};

ButtonEvent ButtonManager::button_seven_event = []() {
    printf("Button seven pressed!\n");
};

ButtonEvent ButtonManager::button_eight_event = []() {
    printf("Button eight pressed!\n");
};

ButtonEvent ButtonManager::button_nine_event = []() {
    printf("Button nine pressed!\n");
};

ButtonEvent ButtonManager::button_ten_event = []() {
    printf("Button ten pressed!\n");
};

ButtonEvent ButtonManager::button_eleven_event = []() {
    printf("Button eleven pressed!\n");
};

ButtonEvent ButtonManager::button_twelve_event = []() {
    printf("Button twelve pressed!\n");
};

ButtonEvent ButtonManager::button_thirteen_event = []() {
    printf("Button thirteen pressed!\n");
};

ButtonEvent ButtonManager::button_fourteen_event = []() {
    printf("Button fourteen pressed!\n");
};

ButtonEvent ButtonManager::button_fifteen_event = []() {
    printf("Button fifteen pressed!\n");
};

ButtonEvent ButtonManager::button_sixteen_event = []() {
    printf("Button sixteen pressed!\n");
};

ButtonEvent ButtonManager::button_seventeen_event = []() {
    printf("Button seventeen pressed!\n");
};

ButtonEvent ButtonManager::button_eighteen_event = []() {
    printf("Button eighteen pressed!\n");
};

void ButtonManager::SetButtonOneFunctionality(ButtonEvent event){
    button_one_event = event;
}

void ButtonManager::SetButtonTwoFunctionality(ButtonEvent event) {
    button_two_event = event;
}

void ButtonManager::SetButtonThreeFunctionality(ButtonEvent event) {
    button_three_event = event;
}

void ButtonManager::SetButtonFourFunctionality(ButtonEvent event) {
    button_four_event = event;
}

void ButtonManager::SetButtonFiveFunctionality(ButtonEvent event) {
    button_five_event = event;
}

void ButtonManager::SetButtonSixFunctionality(ButtonEvent event) {
    button_six_event = event;
}

void ButtonManager::SetButtonSevenFunctionality(ButtonEvent event) {
    button_seven_event = event;
}

void ButtonManager::SetButtonEightFunctionality(ButtonEvent event) {
    button_eight_event = event;
}

void ButtonManager::SetButtonNineFunctionality(ButtonEvent event) {
    button_nine_event = event;
}

void ButtonManager::SetButtonTenFunctionality(ButtonEvent event) {
    button_ten_event = event;
}

void ButtonManager::SetButtonElevenFunctionality(ButtonEvent event) {
    button_eleven_event = event;
}

void ButtonManager::SetButtonTwelveFunctionality(ButtonEvent event) {
    button_twelve_event = event;
}

void ButtonManager::SetButtonThirteenFunctionality(ButtonEvent event) {
    button_thirteen_event = event;
}

void ButtonManager::SetButtonFourteenFunctionality(ButtonEvent event) {
    button_fourteen_event = event;
}

void ButtonManager::SetButtonFifteenFunctionality(ButtonEvent event) {
    button_fifteen_event = event;
}

void ButtonManager::SetButtonSixteenFunctionality(ButtonEvent event) {
    button_sixteen_event = event;
}

void ButtonManager::SetButtonSeventeenFunctionality(ButtonEvent event) {
    button_seventeen_event = event;
}

void ButtonManager::SetButtonEighteenFunctionality(ButtonEvent event) {
    button_eighteen_event = event;
}

void ButtonManager::SetButtonFunctionality(ButtonEvent event, int number) {
    switch (number) {
        case 1: SetButtonOneFunctionality(event); break;
        case 2: SetButtonTwoFunctionality(event); break;
        case 3: SetButtonThreeFunctionality(event); break;
        case 4: SetButtonFourFunctionality(event); break;
        case 5: SetButtonFiveFunctionality(event); break;
        case 6: SetButtonSixFunctionality(event); break;
        case 7: SetButtonSevenFunctionality(event); break;
        case 8: SetButtonEightFunctionality(event); break;
        case 9: SetButtonNineFunctionality(event); break;
        case 10: SetButtonTenFunctionality(event); break;
        case 11: SetButtonElevenFunctionality(event); break;
        case 12: SetButtonTwelveFunctionality(event); break;
        case 13: SetButtonThirteenFunctionality(event); break;
        case 14: SetButtonFourteenFunctionality(event); break;
        case 15: SetButtonFifteenFunctionality(event); break;
        case 16: SetButtonSixteenFunctionality(event); break;
        case 17: SetButtonSeventeenFunctionality(event); break;
        case 18: SetButtonEighteenFunctionality(event); break;
        default: throw std::invalid_argument("Unknown button number");
    }
}

void ButtonManager::CallButton(int number) {
    switch (number) {
        case 1: button_one_event(); break;
        case 2: button_two_event(); break;
        case 3: button_three_event(); break;
        case 4: button_four_event(); break;
        case 5: button_five_event(); break;
        case 6: button_six_event(); break;
        case 7: button_seven_event(); break;
        case 8: button_eight_event(); break;
        case 9: button_nine_event(); break;
        case 10: button_ten_event(); break;
        case 11: button_eleven_event(); break;
        case 12: button_twelve_event(); break;
        case 13: button_thirteen_event(); break;
        case 14: button_fourteen_event(); break;
        case 15: button_fifteen_event(); break;
        case 16: button_sixteen_event(); break;
        case 17: button_seventeen_event(); break;
        case 18: button_eighteen_event(); break;
        default: throw std::invalid_argument("Invalid button number");
    }
}

//Labels
std::string ButtonManager::button_one_label = std::string("Q");
std::string ButtonManager::button_two_label = std::string("W");
std::string ButtonManager::button_three_label = std::string("E");
std::string ButtonManager::button_four_label = std::string("R");
std::string ButtonManager::button_five_label = std::string("T");
std::string ButtonManager::button_six_label = std::string("Y");
std::string ButtonManager::button_seven_label = std::string("A");
std::string ButtonManager::button_eight_label = std::string("S");
std::string ButtonManager::button_nine_label = std::string("D");
std::string ButtonManager::button_ten_label = std::string("F");
std::string ButtonManager::button_eleven_label = std::string("G");
std::string ButtonManager::button_twelve_label = std::string("H");
std::string ButtonManager::button_thirteen_label = std::string("Z");
std::string ButtonManager::button_fourteen_label = std::string("X");
std::string ButtonManager::button_fifteen_label = std::string("C");
std::string ButtonManager::button_sixteen_label = std::string("V");
std::string ButtonManager::button_seventeen_label = std::string("B");
std::string ButtonManager::button_eighteen_label = std::string("N");

void ButtonManager::SetLabelOne(char* label) {
    button_one_label = label;
}

void ButtonManager::SetLabelTwo(char* label) {
    button_two_label = label;
}

void ButtonManager::SetLabelThree(char* label) {
    button_three_label = label;
}

void ButtonManager::SetLabelFour(char* label) {
    button_four_label = label;
}

void ButtonManager::SetLabelFive(char* label) {
    button_five_label = label;
}

void ButtonManager::SetLabelSix(char* label) {
    button_six_label = label;
}

void ButtonManager::SetLabelSeven(char* label) {
    button_seven_label = label;
}

void ButtonManager::SetLabelEight(char* label) {
    button_eight_label = label;
}

void ButtonManager::SetLabelNine(char* label) {
    button_nine_label = label;
}

void ButtonManager::SetLabelTen(char* label) {
    button_ten_label = label;
}

void ButtonManager::SetLabelEleven(char* label) {
    button_eleven_label = label;
}

void ButtonManager::SetLabelTwelve(char* label) {
    button_twelve_label = label;
}

void ButtonManager::SetLabelThirteen(char* label) {
    button_thirteen_label = label;
}

void ButtonManager::SetLabelFourteen(char* label) {
    button_fourteen_label = label;
}

void ButtonManager::SetLabelFifteen(char* label) {
    button_fifteen_label = label;
}

void ButtonManager::SetLabelSixteen(char* label) {
    button_sixteen_label = label;
}

void ButtonManager::SetLabelSeventeen(char* label) {
    button_seventeen_label = label;
}

void ButtonManager::SetLabelEighteen(char* label) {
    button_eighteen_label = label;
}

void ButtonManager::SetLabel(char* label, int number) {
    switch (number){
        case 1: SetLabelOne(label); break;
        case 2: SetLabelTwo(label); break;
        case 3: SetLabelThree(label); break;
        case 4: SetLabelFour(label); break;
        case 5: SetLabelFive(label); break;
        case 6: SetLabelSix(label); break;
        case 7: SetLabelSeven(label); break;
        case 8: SetLabelEight(label); break;
        case 9: SetLabelNine(label); break;
        case 10: SetLabelTen(label); break;
        case 11: SetLabelEleven(label); break;
        case 12: SetLabelTwelve(label); break;
        case 13: SetLabelThirteen(label); break;
        case 14: SetLabelFourteen(label); break;
        case 15: SetLabelFifteen(label); break;
        case 16: SetLabelSixteen(label); break;
        case 17: SetLabelSeventeen(label); break;
        case 18: SetLabelEighteen(label); break;
        default: throw std::invalid_argument("Invalid button number");
    }
}

const char* ButtonManager::GetLabel(int number) {
    switch (number){
        case 1: return button_one_label.c_str();
        case 2: return button_two_label.c_str();
        case 3: return button_three_label.c_str();
        case 4: return button_four_label.c_str();
        case 5: return button_five_label.c_str();
        case 6: return button_six_label.c_str();
        case 7: return button_seven_label.c_str();
        case 8: return button_eight_label.c_str();
        case 9: return button_nine_label.c_str();
        case 10: return button_ten_label.c_str();
        case 11: return button_eleven_label.c_str();
        case 12: return button_twelve_label.c_str();
        case 13: return button_thirteen_label.c_str();
        case 14: return button_fourteen_label.c_str();
        case 15: return button_fifteen_label.c_str();
        case 16: return button_sixteen_label.c_str();
        case 17: return button_seventeen_label.c_str();
        case 18: return button_eighteen_label.c_str();
        default: throw std::invalid_argument("Invalid button number");
    }
}
