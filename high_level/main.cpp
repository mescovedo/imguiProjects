#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

int main() {
    // --- Load config_low_level.json ---
    std::ifstream file(std::string(CONFIG_DIR) + "/config_high_level.json");
    if (!file.is_open()) {
        std::cerr << "Error opening config_high_level.json\n";
        return -1;
    }

    json config;
    file >> config;

    // --- Extract window & rendering settings ---
    int width = config["window"]["width"];
    int height = config["window"]["height"];
    std::string title = config["window"]["title"];
    int fps = config["rendering"]["fps"];
    auto clear_color = config["rendering"]["clear_color"];
    std::string style = config["imgui"]["style"];

    // --- Create SFML window ---
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    window.setFramerateLimit(fps);

    // Color conversion for SFML 2.6.x
    sf::Color bgColor(
        static_cast<sf::Uint8>(clear_color[0].get<float>() * 255),
        static_cast<sf::Uint8>(clear_color[1].get<float>() * 255),
        static_cast<sf::Uint8>(clear_color[2].get<float>() * 255)
    );

    // --- Initialize ImGui-SFML ---
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // --- Set ImGui style ---
    if (style == "Dark") ImGui::StyleColorsDark();
    else if (style == "Light") ImGui::StyleColorsLight();
    else ImGui::StyleColorsClassic();

    // Initialization for ImGui-SFML 2.6.x
    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui-SFML\n";
        return -1;
    }

    // --- Main loop ---
    sf::Clock deltaClock;
    while (window.isOpen()) {
        // Event handling for SFML 2.6.x
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // --- Start ImGui frame ---
        ImGui::SFML::Update(window, deltaClock.restart());

        // --- Show ImGui demo window ---
        static bool show_demo = true;
        if (show_demo)
            ImGui::ShowDemoWindow(&show_demo);

        // --- Render SFML + ImGui ---
        window.clear(bgColor);
        ImGui::SFML::Render(window);
        window.display();
    }

    // --- Cleanup ---
    ImGui::SFML::Shutdown();
    ImGui::DestroyContext();

    return 0;
}