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
    const int width = 1200;
    const int heigth = 900;
    int contMoveCameraX, contMoveCameraY;
    sf::Clock clock;

    void SetComponents()
    {
        std::vector<std::vector<Bloque *>> camaraAux = camara->GetCamara(); 
        components.clear();
        int contX = 0, contY = 0;
        for (auto array : camaraAux)
        {
            for (Bloque* bloque : array)
            {   
                if (bloque != nullptr)
                {
                    bloque -> SetPopsicion(contY, contX);
                    components.push_back(bloque);
                }
                contY += 16;
            }
            contX += 16;
            contY = 0;
        }
    }

public:
    Juego() : window(sf::VideoMode(1200, 900), "TierraAria"), mundo()
    {
        contMoveCameraX = 0;
        contMoveCameraY = 0;
        isRunning = true;
        sf::Texture texture;
        
        
        menu = new Menu(width, heigth);
        switch (menu->DisplayMenu(window))
        {
        case 1:
            mundo.CrearMundo(300, 500, "Hola mundo");
            if (texture.loadFromFile("./assets/image/Splash_9_0.png"))
            {
                //agregar un splashart de carga
                sf::Sprite sprite = sf::Sprite(texture);
                sprite.setPosition(0,0);
                sf::Text loading;
                sf::Font font;
                if (!font.loadFromFile("./assets/font/Andy.ttf"))
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
            mundo.LoadBlocksInWorld();
            camara = new Camara((width / 16) + 2, (heigth / 16) + 2);
            camara->CargarCamara(&mundo);
            SetComponents();
            Guia = new Personaje("./assets/image/NPC_Guide.png", 0.2f,1,1,26,46,sf::Vector2f((width/2)-13,(heigth/2) - 46));
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
        bool mover = true;
        bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::A), right = sf::Keyboard::isKeyPressed(sf::Keyboard::D), up = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        if (left)
            Direccion = Camara::IZQUIERDA;
        else if (right)
            Direccion = Camara::DERECHA;
        else if (up)
            Direccion = Camara::ABAJO;
        
        if (Guia->CheckIfIsFalling(camara)){
            Guia -> Caer();
            Direccion = Camara::ARRIBA;
        }else if(Direccion == 0){
            Guia -> Detener();    
        }

        //Mueve la camara
        if (Direccion != 0)
        {
            if (contMoveCameraX < 16 && contMoveCameraX > -16 && contMoveCameraY < 16 && contMoveCameraY > -16)
            {
                
                if (Direccion == 1 || Direccion == -1){
                    if (Guia -> Mover(Direccion, camara)){
                        mover = false;
                        contMoveCameraX += Direccion;
                    }
                }
                else if (Direccion == 2 || Direccion == -2){
                    if (Direccion == 2)
                    {
                        Guia->Saltar();
                    }
                    contMoveCameraY += Direccion / 2;
                }
                if (mover){
                    for (auto *GameObject : components)
                        if (Direccion == 1 || Direccion == -1)
                            GameObject->ChangePopsicion(Direccion, 0);
                        else if (Direccion == 2 || Direccion == -2)
                            GameObject->ChangePopsicion(0, Direccion / 2);
                }
            }
            else
            {
                camara->MoverCamara(Direccion);
                SetComponents();
                if (Direccion == 1 || Direccion == -1)
                    contMoveCameraX = 0;
                else if (Direccion == 2 || Direccion == -2){
                    if (Direccion == 2)
                    {
                        Guia->Saltar();
                    }
                    contMoveCameraY = 0;
                }
                for (auto *GameObject : components)
                    if (Direccion == 1 || Direccion == -1)
                        GameObject->ChangePopsicion(0, contMoveCameraY);
                    else if (Direccion == 2 || Direccion == -2)
                        GameObject->ChangePopsicion(contMoveCameraX, 0);
            }
        }
    }

    void Render()
    {
        window.clear();
        window.draw(Guia->GetSprite());
        for (auto *GameObject : components)
            window.draw(GameObject->GetSprite());
        window.display();
    }

    bool IsRunning() { return isRunning; }

    ~Juego() { 
        for (auto component : components)
        {
            delete component;
        }
        
        delete Guia;
        delete menu;
        delete camara;
        window.close(); 
        
    }
};
