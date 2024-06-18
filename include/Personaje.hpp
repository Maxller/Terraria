#pragma once
#include <SFML/Graphics.hpp>
#include <Objeto.hpp>
#include <string>
#include <Bloque.hpp>
#include <iostream>
#include <Camara.hpp>

class Personaje : public Objeto
{
private:
    sf::Sprite *sprite;
    bool inmovil, saltando, cayendo;
    sf::Clock clock;
    float frameTime;
    int direccion;

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

    std::vector<Bloque *> getEntorno(Camara* camara)
    {
        int width = camara->getWidth();
        int heigth = camara->getHeight();
        int entornoX = (width / 2) - 1;
        int entornoY = (heigth / 2) - 2;
        std::vector<Bloque *> BlocksInArrary;   
        for (int y = entornoY; y < entornoY + 4; y++)
        {
            for (int x = entornoX; x < entornoX + 2; x++)
            {
                Bloque *aux = camara->getBlockAt(x,y);
                if (aux != nullptr){
                    BlocksInArrary.push_back(aux);
                }
                
            }
        }
        return BlocksInArrary;
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
        if (!saltando && !cayendo)
        {
            updateFrame(31, 2);
            currentFrame++;
        }
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
        saltando = false;
        updateFrame(2,2);
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
        updateFrame(528, 2);   
    }
    
    bool isFalling(Camara* camara){
        if(!saltando){
            cayendo = true;
            std::vector<Bloque *> entorno = getEntorno(camara);
            for (Bloque* bloque : entorno) {
                if (checkCollisionSide(bloque) == CollisionSide::Bottom) {
                    std::cout<<"tengo un bloque en las patas"<<std::endl;
                    cayendo = false;
                    break;
                } 
            }
            return cayendo;        
        }
        return false;
    }


    
    ~Personaje() {}
};
