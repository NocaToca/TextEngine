#include <string>

class Node;

class JSONLoader{

    public:
        static Node LoadNode(std::string name_space);
        static void SaveNode(Node node, std::string name_space);
        static void SaveAllNodes(std::vector<Node> nodes, std::string name_space);
        static std::vector<Node> LoadAllNodes(std::string name_space);

};