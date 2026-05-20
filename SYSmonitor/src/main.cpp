#include <iostream>
#include "SFML/Graphics.hpp"


int mai() {
    const unsigned int width = 1920;
    const unsigned int height = 1080;
    const unsigned int frames = 120;

    // Create the main window with fixed resolution
    sf::RenderWindow window(sf::VideoMode({ width, height }), "Sample");
    // Limit framerate to avoid 100% CPU usage and unstable timing
    window.setFramerateLimit(frames);

    sf::CircleShape circle({ 50 });
    // Set origin to center so positioning uses the circle's center instead of top-left
    circle.setOrigin(circle.getGeometricCenter());
    // SFML uses a coordinate system where (0,0) is top-left
    circle.setPosition({ width / 2.f, height / 2.f });

    while (window.isOpen()) {
        // Process events
        // Important: Event polling is required, otherwise the window will freeze
        while (const std::optional event = window.pollEvent()) {
            // Close window: exit and when pressing escape
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keypressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keypressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
        }
        // Clear screen
        window.clear(sf::Color::Black);

        //draw
        window.draw(circle);

        //display
        window.display();
    }
    return 0;
}
