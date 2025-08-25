#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {

    // --- Load config_low_level.json from project root ---
    std::ifstream file(std::string(CONFIG_DIR) + "/config_low_level.json");
    if (!file.is_open()) {
        std::cerr << "Error opening config_low_level.json in " << CONFIG_DIR << std::endl;
        return -1;
    }

    json config;
    file >> config;

    // --- Extract values from JSON ---
    int width = config["window"]["width"];
    int height = config["window"]["height"];
    std::string title = config["window"]["title"];
    std::string glsl_version = config["rendering"]["glsl_version"];
    bool vsync = config["rendering"]["vsync"];
    auto clear_color = config["rendering"]["clear_color"];
    std::string style = config["imgui"]["style"];

    // --- Initialize GLFW ---
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) return -1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(vsync ? 1 : 0);

    // --- Initialize ImGui ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // --- Style ---
    if (style == "Dark") ImGui::StyleColorsDark();
    else if (style == "Light") ImGui::StyleColorsLight();
    else ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    bool show_demo_window = true;

    // --- Main loop ---
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // --- Cleanup ---
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}