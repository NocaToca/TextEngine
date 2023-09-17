//The interface class basically just provides functionality between our game and the user
//It's job is managing what happens when a button is class and sending information over to the display
//Using the interface, it is really easy to assign different functions to buttons and display different information
//on windows depnding on what is desired!
#include <functional>
#include <string>

#define Event_void static ButtonEvent
#define Label static std::string

    typedef std::function<void()> ButtonEvent;

    class ButtonManager{

        private: 
        //Events
        //Row 1
        Event_void button_one_event; //Default button is Q
        Event_void button_two_event; //Default button is W
        Event_void button_three_event; //Default button is E
        Event_void button_four_event; //Default button is R
        Event_void button_five_event; //Default button is T
        Event_void button_six_event; //Default button is Y

        //Row 2
        Event_void button_seven_event; //Default button is A
        Event_void button_eight_event; //Default button is S
        Event_void button_nine_event; //Default button is D
        Event_void button_ten_event; //Default button is F
        Event_void button_eleven_event; //Default button is G
        Event_void button_twelve_event; //Default button is H

        //Row 3
        Event_void button_thirteen_event; //Default button is Z
        Event_void button_fourteen_event; //Default button is X
        Event_void button_fifteen_event; //Default button is C
        Event_void button_sixteen_event; //Default button is V
        Event_void button_seventeen_event; //Default button is B
        Event_void button_eighteen_event; //Default button is N

        //Labels
        Label button_one_label;
        Label button_two_label;
        Label button_three_label;
        Label button_four_label;
        Label button_five_label;
        Label button_six_label;
        Label button_seven_label;
        Label button_eight_label;
        Label button_nine_label;
        Label button_ten_label;
        Label button_eleven_label;
        Label button_twelve_label;
        Label button_thirteen_label;
        Label button_fourteen_label;
        Label button_fifteen_label;
        Label button_sixteen_label;
        Label button_seventeen_label;
        Label button_eighteen_label;

        public:
        //Functionality calls
        static void SetButtonFunctionality(ButtonEvent event, int number);
        
        inline static void SetButtonOneFunctionality(ButtonEvent event);
        inline static void SetButtonTwoFunctionality(ButtonEvent event);
        inline static void SetButtonThreeFunctionality(ButtonEvent event);
        inline static void SetButtonFourFunctionality(ButtonEvent event);
        inline static void SetButtonFiveFunctionality(ButtonEvent event);
        inline static void SetButtonSixFunctionality(ButtonEvent event);
        inline static void SetButtonSevenFunctionality(ButtonEvent event);
        inline static void SetButtonEightFunctionality(ButtonEvent event);
        inline static void SetButtonNineFunctionality(ButtonEvent event);
        inline static void SetButtonTenFunctionality(ButtonEvent event);
        inline static void SetButtonElevenFunctionality(ButtonEvent event);
        inline static void SetButtonTwelveFunctionality(ButtonEvent event);
        inline static void SetButtonThirteenFunctionality(ButtonEvent event);
        inline static void SetButtonFourteenFunctionality(ButtonEvent event);
        inline static void SetButtonFifteenFunctionality(ButtonEvent event);
        inline static void SetButtonSixteenFunctionality(ButtonEvent event);
        inline static void SetButtonSeventeenFunctionality(ButtonEvent event);
        inline static void SetButtonEighteenFunctionality(ButtonEvent event);
        
        static void CallButton(int button_number);

        //Label calls
        inline static void SetLabelOne(char* label);
        inline static void SetLabelTwo(char* label);
        inline static void SetLabelThree(char* label);
        inline static void SetLabelFour(char* label);
        inline static void SetLabelFive(char* label);
        inline static void SetLabelSix(char* label);
        inline static void SetLabelSeven(char* label);
        inline static void SetLabelEight(char* label);
        inline static void SetLabelNine(char* label);
        inline static void SetLabelTen(char* label);
        inline static void SetLabelEleven(char* label);
        inline static void SetLabelTwelve(char* label);
        inline static void SetLabelThirteen(char* label);
        inline static void SetLabelFourteen(char* label);
        inline static void SetLabelFifteen(char* label);
        inline static void SetLabelSixteen(char* label);
        inline static void SetLabelSeventeen(char* label);
        inline static void SetLabelEighteen(char* label);

        static void SetLabel(char* label, int number);
        static const char* GetLabel(int number);
        


    };

