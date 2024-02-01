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
            }

        }

        ImGui::SFML::Update(window, clock.restart());


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
        window.setTitle("Demu- Graphics API: " + std::string(window.getSystemHandle() ? "OpenGL" : "DirectX"));

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

