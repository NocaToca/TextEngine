#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include "imgui/imgui.h"

#endif

#define LINK_ATTACHMENT_DISTANCE 25.0f

class Node;

enum Direction{
    South,
    West,
    North,
    East,
    None
};


const float LINK_RADIUS = 5.0f;

//Links between nodes
class Link{
    public:
    std::string link_name; //The name of the link that will appear

    ImVec2 base_position; //Position of the linker circle that appears on the node
    Node* parent_node; //The main node that the link will be visible on
    Link* connected_node; //THe main node that the link conncets to

    std::vector<Link*> connections; //The links that connect to this node

    Direction placed_direction; //Used to process visuals

    Link(std::string link_name_, ImVec2 base_position_, Node* parent_node_, Link* connected_node_, Direction placed_direction_) :
        link_name(link_name_),
        base_position(base_position_),
        parent_node(parent_node_),
        connected_node(connected_node_),
        placed_direction(placed_direction_) {
    }

    Link(std::string link_name_){
        link_name = link_name_;
    }

    void Detach(Link* other_link) {
        // Remove the specified link from the connections vector
        connections.erase(std::remove(connections.begin(), connections.end(), other_link),
                      connections.end());
    }

    void Connect(Link* other_link){
        for(const auto& link : connections){
            if(&link == &other_link){
                return;
            }
        }
        connections.push_back(other_link);
    }

    void AttemptAttach(Link* other_link, bool override = false){
        if(other_link == this){
            return;
        }
        //We know that we can't connect on null ptr
        if(other_link != nullptr){
            //We tell the node we're attaching and set it:
            other_link->Connect(this);
            connected_node = other_link;
        } else {
            //If it is a null ptr, see if we're overriding:
            if(override){
                //If we are, tell the connections we're not connected to them anymore and then set our connection to nothing
                if(connected_node != nullptr){  
                    connected_node->Detach(this);
                }
                connected_node = nullptr;
            }
        }
    }

};



//Main node class made for holding base data
class Node {

    public:

    ImVec2 global_position;
    ImVec2 size; //Size should be ImVec2(100, 100)
    std::string label;

    

    std::vector<Link> links;

    Node(const ImVec2& global_position_, const ImVec2& size_, const std::string& label_)
        : global_position(global_position_), size(size_), label(label_) {
    }

    //Moves the node the specified amount
    void MoveNode(ImVec2 delta){
        ImVec2 new_position = ImVec2(global_position.x + delta.x, global_position.y + delta.y);
        global_position = new_position;
        //Then, we just have to do the same to each link:
        for(auto& link : links){
            link.base_position = ImVec2(link.base_position.x + delta.x, link.base_position.y + delta.y);
        }
    }

    //Essentially just creates a link to fit with the node
    void CreateAndAddLink(Direction direction_specifier = Direction::None){
        //First, we will see what side we want to create the link on
        /*
            General rule for rotation:
            North -> East -> West -> South -> North

            Unless it has a direction specificier, then we will prioritize the direction to be in that space
            Keep in mind a link can be on the North of the node and actually go south in game, as the link to the room does not
            determine what button it will be on
        */

       //We have to make sure we don't overload in a single direction - we should only have a max of 5 on each side
        //To do this, we will look at our nodes and see which one has the least
        int south = 0;
        int north = 0;
        int east = 0;
        int west = 0;

        for(const auto& link : links){
            if(link.placed_direction == Direction::North){
                north++;
            } else
            if(link.placed_direction == Direction::East){
                east++;
            } else
            if(link.placed_direction == Direction::South){
                south++;
            } else
            if(link.placed_direction == Direction::West){
                west++;
            }
        }

        int related_number = north;
       Direction chosen_direction = direction_specifier;
       if(chosen_direction == Direction::None){
            if(north > east){
                chosen_direction = Direction::East;
                related_number = east;
            } else
            if(north < east){
                chosen_direction = Direction::North;
                related_number = north;
            } else
            if(east > west){
                chosen_direction = Direction::West;
                related_number = west;
            } else
            if(west > south){
                chosen_direction = Direction::South;
                related_number = south;
            } else{
                chosen_direction = Direction::North;
                related_number = north;
            }
       }

        ImVec2 node_position = ImVec2(0,0);

       //Now, with our chosen direction and nodes, we have to update every node on the direction and add the node to that direction
       //We check to see if there are no nodes first so we don't have to move any
        if(related_number == 0 && (chosen_direction == Direction::North || chosen_direction == Direction::South)){
            node_position = ImVec2(global_position.x, 
                ((chosen_direction == Direction::North) ? global_position.y - size.y/2.5f : global_position.y + size.y/2.5f));
            links.push_back(Link("Link", node_position, this, nullptr, chosen_direction));
        } else
        if(related_number == 0){
            node_position = ImVec2(
                ((chosen_direction == Direction::East) ? global_position.x + size.x/2.5f : global_position.x - size.x/2.5f),
                global_position.y);
            links.push_back(Link("Link", node_position, this, nullptr, chosen_direction));
        } else {
            //Well, we have to edit the whole row anyway
            std::vector<Link> directional_links;

            // Let's grab the whole row
            int num = 0;
            for (const auto& link : links) {
                if (link.placed_direction == chosen_direction) {
                    directional_links.push_back(link);
                    num++;
                    if (num == 4) {
                        break;
                    }
                }
            }

            // Here, we'll create our new link
            directional_links.push_back(Link("Link", node_position, this, nullptr, chosen_direction));

            // Calculate spacing
            int spacing = (size.y - 20) / num; // Should be 100x100 square anyway

            // Edit positions
            if (chosen_direction == Direction::East || chosen_direction == Direction::West) {
                for (int i = 0; i < num; i++) {
                    if (i == 0) {
                        directional_links[i].base_position = ImVec2(directional_links[i].base_position.x, (size.y - 10) + global_position.y);
                    } else {
                        directional_links[i].base_position = ImVec2(directional_links[i - 1].base_position.x, directional_links[i - 1].base_position.y + spacing);
                    }
                }
            } else if (chosen_direction == Direction::North || chosen_direction == Direction::South) {
                for (int i = 0; i < num; i++) {
                    if (i == 0) {
                        directional_links[i].base_position = ImVec2((size.x - 10) + global_position.x, directional_links[i].base_position.y);
                    } else {
                        directional_links[i].base_position = ImVec2(directional_links[i - 1].base_position.x + spacing, directional_links[i - 1].base_position.y);
                    }
                }
            }

            links.push_back(directional_links[num]);
        }
        printf("Added Link!");

    }

    void AddLink(Link link){
        links.push_back(link); //Just add a link to the list
    }

    Link& CheckIfLinkIsInSpace(ImVec2 clicked_position, ImVec2 viewport_center){
        for(auto& link : links){
            
            ImVec2 link_center = ImVec2(link.base_position.x - viewport_center.x, link.base_position.y - viewport_center.y);

            bool is_inside = sqrt(pow(link_center.x - clicked_position.x, 2) + pow(link_center.y - clicked_position.y, 2)) < LINK_RADIUS;

            //Now we can simply check if the node is inside the boundaries:
            if(is_inside){
                // printf("Center: (%f, %f)\n", base_position.x, base_position.y);
                return link;
            }
        }

        static Link null_link("null");
        return null_link;
    }

    Link* FindClosestLink(ImVec2 position){
        // printf("Looking for links!");
        Link* closest_link = nullptr;
        float closest_distance = LINK_ATTACHMENT_DISTANCE;
        for(auto& link : links){
            float distance = sqrt(pow
                (link.base_position.x - position.x, 2.0) 
                + pow
                (link.base_position.y - position.y, 2.0));
            if(distance < closest_distance){
                closest_distance = distance;
                closest_link = &link;
            }
            // printf("Closest Distance: %f", closest_distance);
        }

        return closest_link;
    }
    
};

//Now, the main class for managing and drawing the nodes. This is relative to 
//Each MapWorkspace instance we have open
class NodeGraph{

    public:
        void AddNode(const Node& node){
            nodes.push_back(node);
        }
        void ClearNodes(){
            nodes.clear();
        }
        void SetNodes(std::vector<Node> setting_nodes){
            nodes = setting_nodes;
        }

        Node* FindNodeInDistance(ImVec2 mouse_position, float distance){
            for(auto& node : nodes){
                //We add the size to distance:
                float true_distance = distance + node.size.x/2; //Remeber it should be a square
                if(sqrt(pow(mouse_position.x - node.global_position.x, 2.0) + 
                pow(mouse_position.y - node.global_position.y, 2.0)) < true_distance){
                    //We can assume this is going to be the closest node:
                    return &node;
                }
            }

            //We return the null node
            return nullptr;
        }

        //Basically we'll try to find the closest link and return null if none is found
        Link* FindLinkToAttachTo(Link* link, ImVec2 current_mouse_position /* Should be transformed before being inputted*/){
            //First we find the closest node:
            Node* potential_node = FindNodeInDistance(current_mouse_position, LINK_ATTACHMENT_DISTANCE);

            //First we check if the node is valid:
            if(potential_node != nullptr && potential_node != link->parent_node){
                //Then we find the closest link
                Link* closest_link = potential_node->FindClosestLink(current_mouse_position);
                return closest_link;
            }  

            //If we can't, we just fail:
            return nullptr;

        }

        void DisplayNodes(ImVec2 window_center, ImVec2 screen_size){
            //Displays each node to the screen
            for(const auto& node : nodes){
                //First, we grab the bottom left corner:
                ImVec2 bottom_left = ImVec2(node.global_position.x - node.size.x/2, node.global_position.y - node.size.y/2);
                //Then the top right
                ImVec2 top_right = ImVec2(node.global_position.x + node.size.x/2, node.global_position.y + node.size.y/2);

                //Now, we transfer it based off of the current viewport center:
                bottom_left = ImVec2(bottom_left.x - window_center.x, bottom_left.y - window_center.y);
                top_right = ImVec2(top_right.x - window_center.x, top_right.y - window_center.y);

                //Draw the rectangle first
                ImGui::GetWindowDrawList()->AddRectFilled(bottom_left, top_right, ImColor(125,125,125));

                // Label test
                ImVec2 label_size = ImGui::CalcTextSize(node.label.c_str());
                ImVec2 label_position((bottom_left.x + (node.size.x) * 0.5f) - label_size.x * 0.5f,
                                    (bottom_left.y + (node.size.y) * 0.5f) - label_size.y * 0.5f);


                ImGui::SetCursorPos(label_position);
                ImGui::Text(node.label.c_str());

                DisplayLinks(window_center, node);
            }
        }

        void DisplayLinks(ImVec2 window_center, Node node){
            //We'll do the pathfinding on the links later. For now we just want to have the circles drawn
            for(const auto& link : node.links){
                //Since this is a circle, we will be able to do things a bit differently
                ImVec2 circle_center = ImVec2(link.base_position.x - window_center.x, link.base_position.y - window_center.y);

                ImU32 circle_rim_color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

                ImU32 circle_inner_color = ImGui::ColorConvertFloat4ToU32(ImVec4(0.05f, 0.05f, 0.05f, 1.0f));

                int segments = 24;
                float thickness = 1.0f;

                bool connected = link.connected_node != nullptr;
                bool has_connection = link.connections.size() != 0;

                if(connected || has_connection){
                    circle_rim_color = ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
                }

                ImGui::GetWindowDrawList()->AddCircleFilled(circle_center, 5.0f, circle_inner_color, segments);
                ImGui::GetWindowDrawList()->AddCircle(circle_center, 5.0f, circle_rim_color, segments, thickness);

                //Then we just draw the connection
                if(connected){
                    // Draw the horizontal line
                    ImGui::GetWindowDrawList()->AddLine(ImVec2(link.base_position.x, link.base_position.y), 
                    ImVec2(link.connected_node->base_position.x, link.base_position.y), 
                    ImGui::GetColorU32(ImVec4(0.0f,1.0f,0.0f, 1.0f)), 10.0f);

                    // Draw the vertical line
                    ImGui::GetWindowDrawList()->AddLine(ImVec2(link.connected_node->base_position.x, link.base_position.y), 
                    link.connected_node->base_position, 
                    ImGui::GetColorU32(ImVec4(0.0f,1.0f,0.0f, 1.0f)), 10.0f);
                }

            }
        }

        void RemoveNode(const std::string& label){
    
            for(auto node = nodes.begin(); node != nodes.end(); ++node){
                if(node->label == label){
                    nodes.erase(node);
                    return;
                }
            }
        }

        //Returns the first node found in the space
        Node& GetNodeInSpace(ImVec2 base_position, ImVec2 window_center){
            //First, we have to transform the position
            ImVec2 workspace_position = ImVec2(base_position.x - window_center.x, base_position.y - window_center.y);

            for(auto& node : nodes){
                ImVec2 bottom_left = ImVec2(node.global_position.x - node.size.x/2, node.global_position.y - node.size.y/2);
                //Then the top right
                ImVec2 top_right = ImVec2(node.global_position.x + node.size.x/2, node.global_position.y + node.size.y/2);

                //Now, we transfer it based off of the current viewport center:
                bottom_left = ImVec2(bottom_left.x - window_center.x, bottom_left.y - window_center.y);
                top_right = ImVec2(top_right.x - window_center.x, top_right.y - window_center.y);

                //Now we can simply check if the node is inside the boundaries:
                if(
                    base_position.x < top_right.x && base_position.x > bottom_left.x
                    &&
                    base_position.y < top_right.y && base_position.y > bottom_left.y
                ){
                    // printf("Center: (%f, %f)\n", base_position.x, base_position.y);
                    return node;
                }
            }

            static Node null_node(ImVec2(0, 0), ImVec2(0, 0), "null");
            return null_node;
        }
        std::vector<Node> nodes;

};