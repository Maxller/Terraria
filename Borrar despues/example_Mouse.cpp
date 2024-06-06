// main.cpp

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Mouse Example");

    // Ejecutar el bucle principal
    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            // Cerrar la ventana si se recibe el evento de cerrar
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Manejar eventos de ratón
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Botón izquierdo presionado en (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "Botón derecho presionado en (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Botón izquierdo liberado en (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "Botón derecho liberado en (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
                }
            // } else if (event.type == sf::Event::MouseMoved) {
            //   std::cout << "Ratón movido a (" << event.mouseMove.x << ", " << event.mouseMove.y << ")\n";
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    std::cout << "Rueda del ratón (vertical) desplazada " << event.mouseWheelScroll.delta << " en (" 
                              << event.mouseWheelScroll.x << ", " << event.mouseWheelScroll.y << ")\n";
                }
            }
        }

        // Limpiar la ventana con un color
        window.clear(sf::Color::Black);

        // Dibujar cosas aquí

        // Mostrar lo que se ha dibujado en la ventana
        window.display();
    }

    return 0;
}
