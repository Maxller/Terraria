#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <Personaje.hpp>
#include <vector>
#include <Menu.hpp>
#include <Mundo.hpp>

class Juego
{
private:
    sf::RenderWindow window;
    sf::Event event;
    std::vector<Objeto *> components;
    bool isRunning, isKeyPress;
    sf::Clock clock;
    Personaje *Guia;
    Menu* menu;
    Mundo mundo;
    const int width = 800;
    const int heigth = 600;

public:
    Juego() : window(sf::VideoMode(800, 600), "Game Loop Example"), mundo()
    {
        isRunning = true;
        isKeyPress = false;
        menu = new Menu(width, heigth);
        switch (menu->displayMenu(window))
        {
        case 1:
            mundo.CrearMundo(300, 500, "Hola mundo");
            Guia = new Personaje("./assets/NPC_Guide.png", 0.06f, 0, 1, 26, 46, sf::Vector2f(220, 220));
            components.push_back(Guia);
            break;
        case 2:
            // No hay opciones jeje

            std::cout<<"adios no sirvo"<<std::endl;
            break;
        case 0:
            isRunning = false;
            break;
        }
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
        if (clock.getElapsedTime().asSeconds() >= 0.3f)
        {
            bool saltar = sf::Keyboard::isKeyPressed(sf::Keyboard::Space), left = sf::Keyboard::isKeyPressed(sf::Keyboard::A), right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

            if (saltar)
            {
                if (left)
                {
                    Guia->Saltar(Personaje::Izquierda);
                }
                else if (right)
                {
                    Guia->Saltar(Personaje::Derecha);
                }
                else
                    Guia->Saltar();
            }
            else
            {
                Guia->Caer();
            }
            if (left)
            {
                Guia->Mover(Personaje::Izquierda);
            }
            else if (right)
            {
                Guia->Mover(Personaje::Derecha);
            }
            else if (!saltar)
            {
                Guia->noMover();
            }
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
