#include <functional>
#include <variant>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include "imgui/imgui.h"

extern const ImGuiWindowFlags main_window;

#endif
#include "engine/Controller/Controller.h"


typedef std::variant<DefaultWindow, MapWindow> WindowType;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



class MainWindow{
    public:
    static WindowType current_window;

};


struct WindowVisitor {
    void operator()(DefaultWindow& default_window);

    void operator()(MapWindow& map_window);
};