#include "engine/NodeManagment/NodeGraph.h"
#include <string>

class MapWindow{
    public:
    std::string name_space;

    bool is_hovered = false;
    bool mouse_button_clicked = false;
    inline void DisplayMainWindow(int scr_width, int scr_height);
    MapWindow(NodeGraph graph, std::string name_space);
    ImVec2 viewport_center; //What the center of the viewport is

    NodeGraph main_node_graph;
};