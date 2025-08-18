# ImGuiProjects Template
![C++20](https://img.shields.io/badge/C++-20-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Platform](https://img.shields.io/badge/platform-windows-blue)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
## 🎯 Purpose

This project is a base template for projects using **Dear ImGui + GLFW + OpenGL**, ready for configuration via JSON.  
It is designed as a starting point for development on **Windows with CLion (CMake)**.

Ideal for interface prototypes, debug tools, or simple 2D/3D games.

## 🛠 Requirements

- Windows 10/11

- CLion + CMake 3.16+

- MinGW Compiler (GCC 13+)

### Included libraries:

| Library       | Purpose                     | Type         |
|---------------|----------------------------|-------------|
| ImGui         | GUI framework              | header + cpp|
| GLFW          | Window/input management    | static lib  |
| nlohmann/json | JSON parsing               | header-only |

## 🚀 Running the demo

- Open the project in CLion.

- Make sure config.json is in the root of the project.

- Build and run → the default ImGui demo window will appear.

- Edit config.json to change parameters like window size, background color, style, vsync.

## 📁 Folder structure

       imguiProjects/
       ├─ main.cpp
       ├─ CMakeLists.txt
       ├─ config.json
       ├─ assets/ 
       └─ external/
           ├─ imgui/
           ├─ glfw/
           └─ json/

## 🧩 Creating a new project
- ### Create a branch or copy the template
    - Option 1: Create a Git branch based on the template commit:
        - ```
          git checkout -b my_new_project

    - Option 2: Copy the entire folder to a new location.

- ### Adjust main.cpp

  - Replace the ImGui demo with your own elements or gameplay:

    - ``` 
        // Before 
        ImGui::ShowDemoWindow(&show_demo_window);

    - ```
        // After
        ImGui::Begin("My Window");
        ImGui::Text("Hello, world!");
        ImGui::End();
    

- ### Configuration via JSON

  -   Keep config.json for mutable parameters:
      - ``` 
        {
            "window": {
                 "width": 1280,
                 "height": 720,
                 "title": "My Project"
            },
            "rendering": {
                 "glsl_version": "#version 130",
                 "vsync": true,
                 "clear_color": [0.45, 0.55, 0.60, 1.00]
            },
            "imgui": {
                 "style": "Dark"
            }
        }



      -  You can add extra fields if needed, e.g., HUD colors, difficulty level, etc.

- ### Add assets

  - Create folders for game resources:

    - assets/images/
    - assets/sounds/

  - Load resources using paths relative to the project root.

- ### Test and build

  - Run the project in CLion to verify functionality.

  - If using Git, commit changes incrementally.

## ✅ Best practices

- Use config.json for mutable parameters to avoid recompiling for minor changes.

- Keep external/ only for third-party dependencies.

- Organize your project in modules (e.g., Game.h, HUD.h).

- Remove the ImGui demo in the initial commit, leaving only the boilerplate.
