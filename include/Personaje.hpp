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
    static const int DERECHA = -1, IZQUIERDA = 1;
    Personaje(std::string Ruta, float frameTime, int currentFrame, int numFrames, int frameWidth, int frameHeight, sf::Vector2f position)
    {
        direccion = IZQUIERDA;
        this->frameTime = frameTime;
        InicializarObjeto(currentFrame, numFrames, frameWidth, frameHeight, position);
        if (!CargarTexturas(Ruta))
        { /*Ah ocurrido un Error*/
        }
        sprite = GetSpritePtr();
        Detener();
    }

    std::vector<Bloque *> GetEntorno(Camara *camara)
    {
        int width = camara->GetWidth();
        int heigth = camara->GetHeight();
        int entornoX = (width / 2) - 1;
        int entornoY = (heigth / 2) - 2;
        std::vector<Bloque *> BlocksInArrary;
        for (int y = entornoY; y < entornoY + 4; y++)
        {
            for (int x = entornoX; x < entornoX + 2; x++)
            {
                Bloque *aux = camara->GetBlockAt(x, y);
                if (aux != nullptr)
                {
                    BlocksInArrary.push_back(aux);
                }
            }
        }
        return BlocksInArrary;
    }
    void UpdateFrame(int left, int top) override
    {
        sprite->setTextureRect(sf::IntRect(left + ((currentFrame % numFrames) * frameWidth + (1 * (currentFrame % numFrames))), top, frameWidth, frameHeight));
    }
    bool Mover(int Direccion, Camara *camara)
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
            std::vector<Bloque *> entorno = GetEntorno(camara);
            for (Bloque *bloque : entorno)
            {
                if(CheckCollisionSide(bloque) == CollisionSide::Left){
                    return false;
                }else if(CheckCollisionSide(bloque) == CollisionSide::Right){
                    return false;
                }
            }
            if (!saltando && !cayendo)
            {
                if (clock.getElapsedTime().asSeconds() >= frameTime)
                {
                    UpdateFrame(31, 2);
                    currentFrame++;
                    clock.restart();
                }
            }
            
        return true;
    }
    void Detener()
    {
        numFrames = 1;
        currentFrame = 0;
        frameHeight = 46;
        frameWidth = 26;
        inmovil = true;
        saltando = false;
        UpdateFrame(2, 2);
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
            UpdateFrame(528, 2);
        }
        else
            Caer();
    }
    
    void Caer()
    {
        cayendo = true;
        UpdateFrame(528, 2);
    }

    bool CheckIfIsFalling(Camara *camara)
    {
        if (!saltando)
        {
            cayendo = true;
            std::vector<Bloque *> entorno = GetEntorno(camara);
            for (Bloque *bloque : entorno)
            {
                if (CheckCollisionSide(bloque) == CollisionSide::Bottom)
                {
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
