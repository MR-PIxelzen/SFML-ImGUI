#include <SFML/Graphics.hpp>
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

int main() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int width = desktopMode.width;
    unsigned int height = desktopMode.height;

    sf::RenderWindow window(sf::VideoMode(width, height), "Demu", sf::Style::Default);
    ImGui::SFML::Init(window);

    enum WindowMode {
        Windowed,
        Borderless,
        Fullscreen
    };

    WindowMode currentMode = Windowed;

    // ImGui initialization
    ImGui::CreateContext();
    ImGui::SFML::Init(window);

    // Main game loop
    sf::Clock clock;
    sf::Clock fpsClock;
    unsigned int frameCount = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event); // Process ImGui events

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && event.key.alt) {
                    switch (currentMode) {
                    case Windowed:
                        window.create(sf::VideoMode(width, height), "Window Title", sf::Style::None);
                        currentMode = Borderless;
                        break;
                    case Borderless:
                        window.create(sf::VideoMode(width, height), "Borderless", sf::Style::Fullscreen);
                        currentMode = Fullscreen;
                        break;
                    case Fullscreen:
                        window.create(sf::VideoMode(width, height), "Window Title", sf::Style::Default);
                        currentMode = Windowed;
                        break;
                    }
                }
                else if (event.key.code == sf::Keyboard::Space && event.key.control) {
                    // Resize the window to 1296 x 776 when Ctrl+Space is pressed
                    window.setSize(sf::Vector2u(1296, 776));
                }

            }

        }

        ImGui::SFML::Update(window, clock.restart());

        // ImGui window for displaying text
        if (currentMode == Windowed) {
            ImGui::BeginMainMenuBar();

            // Add menus here
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                    // Handle open action
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {
                    // Handle save action
                }
                if (ImGui::MenuItem("Exit", "Ctrl+Ait")) {
                    // Handle exit action
                    window.close(); // Close the window or implement your own exit logic
                }
                ImGui::EndMenu();
            }

            // "About" menu
            if (ImGui::BeginMenu("About")) {
                if (ImGui::MenuItem("About")) {
                    // Handle opening the about page
                    ImGui::OpenPopup("AboutPopup");
                }
                ImGui::EndMenu();
            }


            if (ImGui::BeginPopupModal("AboutPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("This is the about page!");
                if (ImGui::Button("OK", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            // Add more menus as needed


            ImGui::EndMainMenuBar();
        }

        // ImGui window for displaying text
        ImGui::Begin("Window Mode");
        // Display the graphics API information
        ImGui::Text("Graphics API: %s", window.getSystemHandle() ? "OpenGL" : "DirectX");
        // Calculate and display FPS
        frameCount++;
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            float fps = static_cast<float>(frameCount) / fpsClock.restart().asSeconds();
            ImGui::Text("FPS: %.2f", fps);
            frameCount = 0;
        }

        switch (currentMode) {
        case Windowed:
            ImGui::Text("Windowed Mode");
            break;
        case Borderless:
            ImGui::Text("Borderless Mode");
            break;
        case Fullscreen:
            ImGui::Text("Fullscreen Mode");
            break;
        }
        ImGui::End();





        // Update game logic here



        // Update window title based on graphics API
        window.setTitle("Demu- : " + std::string(window.getSystemHandle() ? "OpenGL" : "DirectX"));

        // Update game logic here

        // Clear the window

        // Clear the window
        window.clear(sf::Color::White);

        // Draw things on the window here

        // Render ImGui
        ImGui::SFML::Render(window);

        // Display the contents of the window
        window.display();
    }

    ImGui::SFML::Shutdown();
    ImGui::DestroyContext();

    return 0;
}

