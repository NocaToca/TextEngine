
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <variant>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Game/interface.h"
#include "Game/texthandler.h"
#include "engine/WorkSpaces/MapWorkspace.h"
#include "engine/mainwindow.h"



//Forward Declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Main GUI
void InitMainWindow();
void InitEnemyDisplayWindow();
void InitFriendlyDisplayWindow();
void InitButtonWindow();
void InitCharacterWindow();
void InitSystemWindow();
void InitMapWindow();
void CreateMainWindow();

//Main Engine GUI
void CreateEngineWindow();

//Main engine control
void HandleInputs();

// settings


const double target_frame_rate = 60.0;
const std::chrono::duration<double> target_frame_duration = std::chrono::duration<double>(1.0/target_frame_rate);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine Prototype", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    //Enable keyboard and gamepad input/output
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGui::StyleColorsDark();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        auto frame_start_time = std::chrono::high_resolution_clock::now();

        processInput(window);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //CreateMainWindow(); This is for the game, not for the engine, so we don't really need it at the moment
        CreateEngineWindow();

        //Handle pop-ups
        PopupHandler::CallEvents();
        HandleInputs();

        //Rendering and clearing previous frame
        ImGui::Render();
        int display_width, display_height;
        glfwGetFramebufferSize(window, &display_width,  &display_height);
        glViewport(0, 0, display_width, display_height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();


        std::this_thread::sleep_for(target_frame_duration - (std::chrono::high_resolution_clock::now() - frame_start_time));
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        PopupHandler::ClearEvents();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


ImVec2 GetScreenSize(float percent_x = 1.0f, float percent_y = 1.0f){
    return ImVec2(
        percent_x * ImGui::GetIO().DisplaySize.x,
        percent_y * ImGui::GetIO().DisplaySize.y
    );
}

//Map Window Settings
const float map_window_size_x = 0.25f;
const float map_window_size_y = 0.25f;

inline void InitMapWindow(){

    ImGui::BeginChild("Map Window", GetScreenSize(map_window_size_x, map_window_size_y), true);
    ImGui::Text("Map Window");
    ImGui::EndChild();

}

//Main Window Settings
const float main_window_size_x = 0.5f;
const float main_window_size_y = 0.7f;

inline void InitMainWindow(){

    ImGui::BeginChild("Main Window", GetScreenSize(main_window_size_x, main_window_size_y), true);

    //We have to set the main window to the description of the current room
    ImGui::Text(TextHandler::PullDescription().c_str());

    ImGui::EndChild();

}

//Enemy Display Window Settings
const float enemy_display_window_size_x = 0.25f;
const float enemy_display_window_size_y = 0.75f;

inline void InitEnemyDisplayWindow(){

    ImGui::BeginChild("Enemy Display Window", GetScreenSize(enemy_display_window_size_x, enemy_display_window_size_y), true);
    ImGui::Text("Enemy Display Window");
    ImGui::EndChild();

}

//Friendly Display Window Settings
const float friendly_display_window_size_x = 0.25f;
const float friendly_display_window_size_y = 0.5f;

inline void InitFriendlyDisplayWindow(){

    ImGui::BeginChild("Friendly Display Window", GetScreenSize(friendly_display_window_size_x, friendly_display_window_size_y), true);
    ImGui::Text("Friendly Display Window");
    ImGui::EndChild();

}

//Character Window Settings
const float character_window_size_x = 0.25f;
const float character_window_size_y = 0.25f;

inline void InitCharacterWindow(){

    ImGui::BeginChild("Character Window", GetScreenSize(character_window_size_x, character_window_size_y), true);
    ImGui::Text("Character Window");
    ImGui::EndChild();

}

//Button Window Settings
const float button_window_size_x = 0.5f;
const float button_window_size_y = 0.3f;

inline void InitButtonWindow(){

    ImGui::BeginChild("Button Window", GetScreenSize(button_window_size_x, button_window_size_y), true);

    const int rows = 3;
    const int columns = 6;

    //Here we do have to find the dimensions of the buttons
    int button_width = (button_window_size_x * SCR_WIDTH)/7;
    int button_height = (button_window_size_y * SCR_HEIGHT)/5;

    for(int row = 0; row < rows; ++row){
        ImGui::BeginGroup();

        for(int col = 0; col < columns; ++col){
            int button_number = row * columns + col + 1;

            if(col > 0){
                ImGui::SameLine();
            }

            const char* button_label = ButtonManager::GetLabel(button_number);

            if(ImGui::Button(button_label, ImVec2(button_width, button_height))){
                ButtonManager::CallButton(button_number);
            }
        }

        ImGui::EndGroup();

        if(row < rows - 1){
            ImGui::NewLine();
        }

    }

    ImGui::EndChild();

}

//System Window Settings
const float system_window_size_x = 0.25f;
const float system_window_size_y = 0.25f;

inline void InitSystemWindow(){

    ImGui::BeginChild("System Window", GetScreenSize(system_window_size_x, system_window_size_y), true);
    ImGui::Text("System Window");
    ImGui::EndChild();

}

void CreateMainWindow(){
    //Window init
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::Begin("My Window", nullptr, main_window);

    //Innit Cursor pos
    ImGui::SetCursorPos(ImVec2(0,0));

    InitMapWindow();

    //Update Cursor pos
    ImGui::SetCursorPos(ImVec2(map_window_size_x * SCR_WIDTH, 0));

    InitMainWindow();

    ImGui::SetCursorPos(ImVec2((map_window_size_x + main_window_size_x) * SCR_WIDTH, 0));

    InitEnemyDisplayWindow();

    //Reset Cursor position to buttom left of mapwindow
    ImGui::SetCursorPos(ImVec2(0, map_window_size_y * SCR_HEIGHT));

    InitFriendlyDisplayWindow();

    ImGui::SetCursorPos(ImVec2(0, (map_window_size_y + friendly_display_window_size_y) * SCR_HEIGHT));

    InitCharacterWindow();

    ImGui::SetCursorPos(ImVec2(map_window_size_x * SCR_WIDTH, main_window_size_y * SCR_HEIGHT));

    InitButtonWindow();

    ImGui::SetCursorPos(ImVec2((map_window_size_x + main_window_size_x) * SCR_WIDTH, enemy_display_window_size_y * SCR_HEIGHT));

    InitSystemWindow();

    ImGui::SetWindowSize(ImVec2(SCR_WIDTH, SCR_HEIGHT));

    ImGui::End();
}

/****************ENGINE********************/


//I left the above for future in-engine testing of the game, however for now consider it depricated. 
inline void CreateEngineWindow(){
    // Window initialization
    std::visit(WindowVisitor{}, MainWindow::current_window);

}

inline void HandleInputs(){
    std::visit(ControllerVisitor(ImGui::GetIO()), MainWindow::current_window);
}