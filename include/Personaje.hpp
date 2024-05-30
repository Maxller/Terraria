#pragma once
#include <SFML/Graphics.hpp>
#include <Objeto.hpp>
#include <string>

class Personaje : public Objeto
{
private:
    sf::Sprite *sprite;
    bool inmovil;
    sf::Clock clock;
    float frameTime;
    int direccion;

public:
    static const int Derecha = -1, Izquierda = 1;
    Personaje(std::string Ruta, float frameTime, int currentFrame, int numFrames, int frameWidth, int frameHeight, sf::Vector2f position)
    {
        direccion = Izquierda;
        this->frameTime = frameTime;
        InicializarObjeto(frameTime, currentFrame, numFrames, frameWidth, frameHeight, position);
        if (!cargarTexturas(Ruta))
        { /*Ah ocurrido un Error*/
        }
        sprite = getSpriteptr();
        noMover();
    }

    void updateFrame(int left, int top) override
    {
        sprite->setTextureRect(sf::IntRect(left + ((currentFrame % numFrames) * frameWidth + (1 * (currentFrame % numFrames))), top, frameWidth, frameHeight));
    }
    void Mover(/*Direccion, Velocidad*/ int Direccion)
    {
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            if (inmovil)
            {
                numFrames = 15;
                currentFrame = 0;
                frameHeight += 2;
                frameWidth += 6;
                inmovil = false;
            }
            if (direccion != Direccion) {sprite->move(Direccion * frameWidth * -1, 0);
                direccion = Direccion;
            }
            sprite->setScale(direccion, 1);
            updateFrame(31, 2);
            currentFrame++;
            sprite->move(Direccion * -6, 0);
            clock.restart();
        }
    }
    void noMover()
    {   
        numFrames = 1;
        currentFrame = 0;
        frameHeight = 46;
        frameWidth = 26;
        inmovil = true;
        updateFrame(2, 2);
    }
    ~Personaje() {}
};
