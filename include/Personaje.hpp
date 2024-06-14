#pragma once
#include <SFML/Graphics.hpp>
#include <Objeto.hpp>
#include <string>

class Personaje : public Objeto
{
private:
    sf::Sprite *sprite;
    bool inmovil, saltando, cayendo;
    sf::Clock clock;
    float frameTime;
    int direccion;
    std::vector<std::vector<Bloque *>> entorno;

public:
    static const int Derecha = -1, Izquierda = 1;
    Personaje(std::string Ruta, float frameTime, int currentFrame, int numFrames, int frameWidth, int frameHeight, sf::Vector2f position)
    {
        direccion = Izquierda;
        this->frameTime = frameTime;
        InicializarObjeto(currentFrame, numFrames, frameWidth, frameHeight, position);
        if (!cargarTexturas(Ruta))
        { /*Ah ocurrido un Error*/
        }
        sprite = getSpriteptr();
        noMover();
    }

    void setEntorno(std::vector<std::vector<Bloque *>> camara){
        int width = camara[0].size();
        int heigth = camara.size();

        int entornoWidth = (width / 2) - 2;
        int entornoHeigth = (heigth / 2) - 3;

        std::vector<Bloque *> BlocksInArrary;
        // for (int y = posY; y < posY + height; y++)
        // {
        //     for (int x = posX; x < posX + width; x++)
        //     {
        //         BlocksInArrary.push_back(world->getBlockAt(x,y));
        //     }
        //     camara.push_back(BlocksInArrary);
        //     BlocksInArrary.clear();
            
        // }



    }
    void updateFrame(int left, int top) override
    {
        sprite->setTextureRect(sf::IntRect(left + ((currentFrame % numFrames) * frameWidth + (1 * (currentFrame % numFrames))), top, frameWidth, frameHeight));
    }
    void Mover(/*Direccion, Velocidad*/ int Direccion)
    {
        //if (clock.getElapsedTime().asSeconds() >= frameTime)
        //{
            if (inmovil && !saltando && !cayendo)
            {
                numFrames = 15;
                currentFrame = 0;
                frameHeight = 48;
                frameWidth += 6;
                inmovil = false;
            }
            if (direccion != Direccion)
            {
                sprite->move(Direccion * frameWidth * -1, 0);
                direccion = Direccion;
            }
            sprite->setScale(direccion, 1);
            if (cayendo)
            {
                Caer();
            }
            if (saltando)
            {
                Saltar();
            }
            if (!saltando && !cayendo)
            {
                updateFrame(31, 2);
                currentFrame++;
            }
        //    clock.restart();
        //}
    }
    void noMover()
    {
        numFrames = 1;
        currentFrame = 0;
        frameHeight = 46;
        frameWidth = 26;
        inmovil = true;
        if (!cayendo && !saltando)
            updateFrame(2, 2);
        if (!saltando)
            Caer();
        saltando = false;
    }
    void Saltar()
    {
        if (!cayendo)
        {
            numFrames = 1;
            currentFrame = 0;
            frameHeight = 46;
            frameWidth = 26;
            frameWidth = 30;
            saltando = true;
            // if (clock.getElapsedTime().asSeconds() >= frameTime)
            // {
            //     sprite->move(0, -6);
            updateFrame(528, 2);
            //     clock.restart();
            // }
        }
        else
            Caer();
    }
    void Saltar(int Direccion)
    {
        if (!cayendo)
        {
            numFrames = 1;
            currentFrame = 0;
            frameHeight = 46;
            frameWidth = 30;
            saltando = true;
            if (clock.getElapsedTime().asSeconds() >= frameTime)
            {
                if (direccion != Direccion)
                {
                    sprite->move(Direccion * -26, 0);
                    direccion = Direccion;
                }
                sprite->move(Direccion * -6, -6);
                updateFrame(528, 2);
                clock.restart();
            }
        }
    }
    void Caer()
    {

        cayendo = true;
        // if (checkCollisionSide())
        // {
        //     cayendo = false; // Modificar
        //     saltando = false;
        // } else 
        // // else if (clock.getElapsedTime().asSeconds() >= frameTime)
        // // {
        // //     sprite->move(0, 6);
        //     updateFrame(528, 2);
        // //     clock.restart();
        // // }
    }
    ~Personaje() {}
};
