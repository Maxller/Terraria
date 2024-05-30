#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <Personaje.hpp>
#include <vector>

class Juego
{
private:
    sf::RenderWindow window;
    sf::Event event;
    std::vector<Objeto *> components;
    bool isRunning, isKeyPress;
    Personaje *Guia;
    

public:
    Juego() : window(sf::VideoMode(800, 600), "Game Loop Example")
    {
        isRunning = true;
        isKeyPress = false;
        Guia = new Personaje("./assets/NPC_Guide.png", 0.06f, 0, 1, 26, 46, sf::Vector2f(220, 220));
        components.push_back(Guia);
    }

    void HandleEvent()
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                isRunning = false;
            }
        }
    }
    void Update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !isKeyPress)
        {
            Guia -> Mover(Personaje::Izquierda);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            Guia -> Mover(Personaje::Derecha);
            isKeyPress = true;
        }
        else 
        {
            Guia -> noMover();
            isKeyPress = false;
        }
    }

    void Render()
    {
        window.clear();
        for (auto *GameObject : components)
        {
            window.draw(GameObject->getSprite());
        }

        window.display();
    }

    bool IsRunning() { return isRunning; }

    ~Juego() { window.close(); }
};
