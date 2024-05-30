#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Objeto
{
private:
    sf::RectangleShape hitBox;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Sprite sprite;
    float frameTime; // Tiempo entre cada frame en segundos
    

protected: 
    int currentFrame;
    int numFrames; // Número total de frames en la animación
    int frameWidth;
    int frameHeight;
    sf::Sprite* getSpriteptr(){
        return & this -> sprite;
    }
    void InicializarObjeto (float frameTime ,int currentFrame ,int numFrames, int frameWidth, int frameHeight, sf::Vector2f position){
        this -> frameTime = frameTime; 
        this -> currentFrame = currentFrame;
        this -> numFrames = numFrames; 
        this -> frameWidth = frameWidth;
        this -> frameHeight = frameHeight;
        this -> position = position;
    }
    bool cargarTexturas (std::string ruta){
        hitBox.setSize(sf::Vector2f(frameHeight, frameWidth));
        hitBox.setPosition(position); // Posición inicial cuadro

        // Cargar la imagen desde un archivo
        
        if (!texture.loadFromFile(ruta))
        {
            return false;
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position); // Posición inicial sprite
        return true;
    }


    virtual void updateFrame(int, int) = 0;

    

public:
    Objeto (){}
        
    sf::Sprite getSprite(){
        return this -> sprite;
    }

    ~Objeto(){}
};


