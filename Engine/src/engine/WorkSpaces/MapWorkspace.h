//This class basically just handles whatever the user does while inside any and all map workspaces. There will
//be able to have multiple map workspaces open at anytime, but we're currently only going to have it so only one can
//be
#include <string>

class MapWorkspace{
    public:
    static void CreateNewMapPrompt();
    static void CreateNewMapFolder(const std::string& map_name);

    static void OpenWorkspaceWindow();
};
