#include <functional>
#ifndef POPUPHANDLER_H
#define POPUPHANDLER_H
#include "imgui/imgui.h"
#endif

typedef std::function<void()> WindowEvents;

class PopupHandler{
    public:
    static bool active;
    static WindowEvents null_event;
    static void ClearEvents(){
        main_events = null_event;
        active = false;
    }
    static void ChangeEvent(WindowEvents other_event){
        main_events = other_event;
        active = true;
        
    }
    static void CallEvents(){
        //Events need to be child functions so we can set things correctly
        if(active){
            main_events();
        }
    }
    private:
    static WindowEvents main_events;
};