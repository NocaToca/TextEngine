#include "engine/DefaultWindow.h"
#include "engine/MapWindow.h"
#include "engine/PopupHandler.h"

#include <functional>
#include <variant>

#ifndef CONTROLLER_H
#define CONTROLLER_H
 
#include "imgui/imgui.h"

#endif


class Controller{

    public:
        static void CallLinkEditWindow(Node& node);
        static void CallNodeInformationWindow(Node& node);
        static bool buffer_input; //Buffer input a frame to account for button presses
        static void CallLinkCreateWindow(Node& node);

    private:
        friend struct ControllerVisitor;
        static bool node_displayed;

};

typedef std::function<void()> Action;

//Handles our different controls based off of our different operations
struct ControllerVisitor {
    
    public:
    ImGuiIO& imgui_IO;
    static Action queued_action;


    ControllerVisitor(ImGuiIO& imgui_IO_) : imgui_IO(imgui_IO_){
        
    }

    void PopEvents();

    void HandleLinkAttachment(Link* current_link, MapWindow& map_window);

    void ShowCreateNodeMenu(MapWindow& map_window);

    void operator()(DefaultWindow& default_window){
        // Handle DefaultWindow

    }

    void operator()(MapWindow& map_window) {

        if(PopupHandler::active){
            return;
        }

        //Okay, let's try to reimagine our controller because it is getting complicated with the ifs and elses
        /*
            At the moment we have the following actions:
                -Right Click
                -Left Click
                -Left Hold
                -Middle hold

            Each of these do different things:
                Right Click:
                    Opens up Create a Node menu
                Left Click:
                    If on a Node:
                        Opens up the node information window
                    else:
                        Closes all pop-ups
                Left Hold:
                    If on a Node:
                        If on a Link:
                            Starts the link attachment process
                        else:
                            Moves the node around the screen
                    else:
                        Also closes all pop-ups
                Middle Hold:
                    Moves viewport center
            
            So what is an easy way to structure the control code to not only make it easy to understand but easy to add upon?
            Well, it's a bit difficult because a hold is a click, so we will have to see which one is actually being done
            To do this we will have an active() function that will activate once the controller has determined what action is actually being done, and
            is set by the most recent input.
        */
       //Let's set up our bools
       //We don't actually have to do this, but it will make reading it easier
       bool right_click = imgui_IO.MouseClicked[ImGuiMouseButton_Right];
       bool left_double_click = imgui_IO.MouseDoubleClicked[ImGuiMouseButton_Left]; //This is made to ensure the user wants to interact with the node
       bool left_hold = imgui_IO.MouseDown[ImGuiMouseButton_Left]; 
       bool middle_hold = imgui_IO.MouseDown[ImGuiMouseButton_Middle];
       bool left_click = imgui_IO.MouseClicked[ImGuiMouseButton_Left];
       bool left_release = imgui_IO.MouseReleased[ImGuiMouseButton_Left];

        Action base_action = [](){};
        //Let's set our action to "null"
       Action action = base_action;


        //Let's define our different actions!
        static Action left_hold_action = [this, &map_window](){
            if(selected_link == nullptr){
                Node& containing_node = map_window.main_node_graph.GetNodeInSpace(ImVec2(imgui_IO.MousePos.x, imgui_IO.MousePos.y), map_window.viewport_center);
                if(containing_node.label.compare("null") != 0){
                    containing_node.MoveNode(imgui_IO.MouseDelta);
                }
            } else {
                // printf("Drawing link :D\n");
                HandleLinkAttachment(selected_link, map_window);
            }
        };

        static Action right_click_action = [this, &map_window](){
            ShowCreateNodeMenu(map_window);
        };

        static Action left_double_click_action = [this, &map_window](){
            Node& containing_node = map_window.main_node_graph.GetNodeInSpace(ImVec2(imgui_IO.MouseClickedPos->x, imgui_IO.MouseClickedPos->y), map_window.viewport_center);
            if(containing_node.label.compare("null") != 0){
                Controller::CallNodeInformationWindow(containing_node);
            }
        };

        static Action left_click_action = [this, &map_window](){
            Node& containing_node = map_window.main_node_graph.GetNodeInSpace(ImVec2(imgui_IO.MousePos.x, imgui_IO.MousePos.y), map_window.viewport_center);
            if(containing_node.label.compare("null") != 0){
                Link& link = containing_node.CheckIfLinkIsInSpace(ImVec2(imgui_IO.MouseClickedPos->x, imgui_IO.MouseClickedPos->y), map_window.viewport_center);
                if(link.link_name.compare("null") != 0){
                    selected_link = &link;
                } else {
                    PopupHandler::ClearEvents();
                    Controller::CallNodeInformationWindow(containing_node);
                }
            } else {
                PopupHandler::ClearEvents();
            }
        };

        static Action middle_hold_action = [this, &map_window](){
            ImVec2 mouse_delta = imgui_IO.MouseDelta; //We have the change, so we just add it to the center:
            map_window.viewport_center = ImVec2(map_window.viewport_center.x - mouse_delta.x, map_window.viewport_center.y - mouse_delta.y);
        };

        static Action left_release_action = [this, &map_window](){
            selected_link = nullptr;
        };

       //Next we have to actually set up the action
       //Right click
        if(right_click){
            action = right_click_action;
        } //Important not to use ifs so we have a heirachy of actions 

        //Left hold
        if(left_hold){
            action = left_hold_action;
        }

        //Left (double) click
        if(left_double_click){
            action = left_double_click_action;
        }

        if(left_click){
            action = left_click_action;
        }

        if(middle_hold){
            action = middle_hold_action;
        }

        if(left_release){
            action = left_release_action;
        }

        //Now we queue the action and, if the action stays true, we'll play it next frame
        if(action.target<void()>() == queued_action.target<void()>()){
            queued_action();
        } else {
            //We ignore it || action.target<void()>() == base_action.target<void()>()
        }

        queued_action = action;
    }
    static Link* selected_link;
};

//Old control code
// Inside the ImGui frame loop
        // if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        //     double currentTime = ImGui::GetTime();
        //     if (double_click && (currentTime - lastClickTime) < 0.1f) {
        //         // Double-click action
        //         double_click = false;
        //         lastClickTime = 0.0;
        //         // Perform your desired action here
        //     } else {
        //         double_click = true;
        //         lastClickTime = currentTime;
        //     }
        // }

        // // Handle MapWindow
        // if(imgui_IO.MouseDown[ImGuiMouseButton_Middle]){
        //     ImVec2 mouse_delta = imgui_IO.MouseDelta; //We have the change, so we just add it to the center:
        //     map_window.viewport_center = ImVec2(map_window.viewport_center.x - mouse_delta.x, map_window.viewport_center.y - mouse_delta.y);
        // } else 
        // if(Controller::node_displayed && imgui_IO.MouseClicked[ImGuiMouseButton_Left]){
        //     PopEvents();
        //     Controller::node_displayed = false;
        // } else
        // if(imgui_IO.MouseDown[ImGuiMouseButton_Left]){
        //     if(selected_link == nullptr){
        //         Node& containing_node = map_window.main_node_graph.GetNodeInSpace(ImVec2(imgui_IO.MousePos.x, imgui_IO.MousePos.y), map_window.viewport_center);
        //         containing_node.MoveNode(imgui_IO.MouseDelta);
        //     } else {
        //         HandleLinkAttachment(selected_link);
        //     }
        // } else
        // if(double_click){
        //     Node& containing_node = map_window.main_node_graph.GetNodeInSpace(ImVec2(imgui_IO.MouseClickedPos->x, imgui_IO.MouseClickedPos->y), map_window.viewport_center);
        //     if(containing_node.label.compare("null") != 0){

        //         Link& clicked_on_link = containing_node.CheckIfLinkIsInSpace(ImVec2(imgui_IO.MouseClickedPos->x, imgui_IO.MouseClickedPos->y), map_window.viewport_center);
        //         if(clicked_on_link.link_name.compare("null") == 0){
        //             Controller::CallNodeInformationWindow(containing_node);
        //         } else {
        //             selected_link = &clicked_on_link;
        //         } 

        //     } else {
        //         PopEvents();
        //     }
        //     double_click = false;
        // } else
        // if(imgui_IO.MouseClicked[ImGuiMouseButton_Right]){
        //     ShowCreateNodeMenu(map_window);
        // } else {
        //     selected_link = nullptr;
        // }