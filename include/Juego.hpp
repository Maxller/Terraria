#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <Personaje.hpp>
#include <vector>
#include <Menu.hpp>
#include <Mundo.hpp>
#include <Camara.hpp>
#include <Bloque.hpp>


class Juego
{
private:
    sf::RenderWindow window;
    sf::Event event;
    std::vector<Objeto *> components;
    bool isRunning;
    Personaje *Guia;
    Menu *menu;
    Mundo mundo;
    Camara *camara;
    const int width = 800;
    const int heigth = 600;
    int contMoveCameraX, contMoveCameraY;
    sf::Clock clock;

    void setComponents()
    {
        std::vector<std::vector<Bloque *>> camaraAux = camara->getCamara(); 
        components.clear();
        int contX = 0, contY = 0;
        for (auto array : camaraAux)
        {
            for (Bloque* bloque : array)
            {   
                if (bloque != nullptr)
                {
                    bloque -> setPopsicion(contY, contX);
                    components.push_back(bloque);
                }
                contY += 16;
            }
            contX += 16;
            contY = 0;
        }
    }

public:
    Juego() : window(sf::VideoMode(800, 600), "TierraAria"), mundo()
    {
        contMoveCameraX = 0;
        contMoveCameraY = 0;
        isRunning = true;
        sf::Texture texture;
        
        
        menu = new Menu(width, heigth);
        switch (menu->displayMenu(window))
        {
        case 1:
            mundo.CrearMundo(300, 500, "Hola mundo");
            if (texture.loadFromFile("./assets/Splash_9_0.png"))
            {
                //agregar un splashart de carga
                sf::Sprite sprite = sf::Sprite(texture);
                sprite.setPosition(0,0);
                sf::Text loading;
                sf::Font font;
                if (!font.loadFromFile("./assets/Andy.ttf"))
                {
                    std::cerr << "Error loading font\n";
                } else loading.setFont(font);
                loading.setString("Cargando...");
                loading.setCharacterSize(100);
                loading.setFillColor(sf::Color::White);
                loading.setPosition((width / 2) - (loading.getGlobalBounds().width / 2), (heigth / 2) - (loading.getGlobalBounds().height / 2));
                window.clear();
                window.draw(sprite);
                window.draw(loading);
                window.display();
            }
            mundo.loadBlocksInWorld();
            camara = new Camara((width / 16) + 2, (heigth / 16) + 2);
            camara->cargarCamara(&mundo);
            setComponents();
            Guia = new Personaje("./assets/NPC_Guide.png", 0.2f,1,1,26,46,sf::Vector2f((width/2)-13,(heigth/2) - 46));
            break;
        case 2:
            // No hay opciones jeje

            std::cout << "adios no sirvo" << std::endl;
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
        int Direccion = 0;
        bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::A), right = sf::Keyboard::isKeyPressed(sf::Keyboard::D), up = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        

        if (left)
            Direccion = Camara::Izquierda;
        else if (right)
            Direccion = Camara::Derecha;
        else if (up)
            Direccion = Camara::Abajo;
        
        if (Guia->isFalling(camara)){
            Guia -> Caer();

            Direccion = Camara::Arriba;
        }else if(Direccion == 0){
            Guia -> noMover();    
        }

        //Mueve la camara
        if (Direccion != 0)
        {
            if (contMoveCameraX < 16 && contMoveCameraX > -16 && contMoveCameraY < 16 && contMoveCameraY > -16)
            {
                
                if (Direccion == 1 || Direccion == -1){
                    Guia -> Mover(Direccion);
                    contMoveCameraX += Direccion;
                }
                else if (Direccion == 2 || Direccion == -2)
                    if (Direccion == 2)
                    {
                        Guia->Saltar();
                    }
                    contMoveCameraY += Direccion / 2;
                for (auto *GameObject : components)
                    if (Direccion == 1 || Direccion == -1)
                        GameObject->deltaPopsicion(Direccion, 0);
                    else if (Direccion == 2 || Direccion == -2)
                        GameObject->deltaPopsicion(0, Direccion / 2);
            }
            else
            {
                camara->moverCamara(Direccion);
                setComponents();
                if (Direccion == 1 || Direccion == -1)
                    contMoveCameraX = 0;
                else if (Direccion == 2 || Direccion == -2)
                    if (Direccion == 2)
                    {
                        Guia->Saltar();
                    }
                    contMoveCameraY = 0;
                for (auto *GameObject : components)
                    if (Direccion == 1 || Direccion == -1)
                        GameObject->deltaPopsicion(0, contMoveCameraY);
                    else if (Direccion == 2 || Direccion == -2)
                        GameObject->deltaPopsicion(contMoveCameraX, 0);
            }
        }
    }

    void Render()
    {
        window.clear();
        window.draw(Guia->getSprite());
        for (auto *GameObject : components)
            window.draw(GameObject->getSprite());
        window.display();
    }

    bool IsRunning() { return isRunning; }

    ~Juego() { 
        delete Guia;
        delete menu;
        delete camara;
        window.close(); 
        
    }
};
