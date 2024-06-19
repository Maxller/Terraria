#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

enum class CollisionSide {
    None,
    Top,
    Bottom,
    Left,
    Right,
    OverX,
    OverY
};

class Objeto
{
private:
    sf::RectangleShape hitBox;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Sprite sprite;
    

protected: 
    int currentFrame;
    int numFrames; // Número total de frames en la animación
    int frameWidth;
    int frameHeight;
    sf::Sprite* GetSpritePtr(){
        return &sprite;
    }
    void InicializarObjeto (int currentFrame ,int numFrames, int frameWidth, int frameHeight, sf::Vector2f position){
        this -> currentFrame = currentFrame;
        this -> numFrames = numFrames; 
        this -> frameWidth = frameWidth;
        this -> frameHeight = frameHeight;
        this -> position = position;
    }
    bool CargarTexturas (std::string ruta){
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

    virtual void UpdateFrame(int, int) = 0;
public:
    Objeto (){}

    sf::FloatRect GetBounds() {
        return hitBox.getGlobalBounds();
    }

    void SetPopsicion(int deltaX, int deltaY){
        sf::Vector2f newPosition(deltaX, deltaY);
        position = newPosition;
        hitBox.setPosition(position);
        this->sprite.setPosition(newPosition); 
    }

    void ChangePopsicion(int deltaX, int deltaY){
        sf::Vector2f deltaPosition(deltaX, deltaY); 
        position += deltaPosition;
        hitBox.setPosition(position);
        this->sprite.setPosition(position); 
    }
    
    sf::Sprite GetSprite(){
        return this -> sprite;
    }

// Función para detectar colisiones y el lado de la colisión
    CollisionSide CheckCollisionSide(Objeto* obj) {
    sf::FloatRect bounds1 = this -> GetBounds();
    sf::FloatRect bounds2 = obj -> GetBounds();

    float deltaX = bounds1.left + bounds1.width / 2 - (bounds2.left + bounds2.width / 2);
    float deltaY = bounds1.top + bounds1.height / 2 - (bounds2.top + bounds2.height / 2);
    float intersectX = std::abs(deltaX) - (bounds1.width / 2 + bounds2.width / 2);
    float intersectY = std::abs(deltaY) - (bounds1.height / 2 + bounds2.height / 2);
    
        if(intersectY == 15 && intersectX < 0){
            if(deltaY < 0){
                return CollisionSide::Bottom;
            } else {
                return CollisionSide::Top;
            }
        } else if(intersectX == 0){
            if(deltaY > 0){
                return CollisionSide::Left;
            } else {
                return CollisionSide::Right;
            }
        } else if (intersectY < 0 ){
            std::cout << "INTER   X: " << intersectX << ", Y:" << intersectY << std::endl;
            return CollisionSide::OverY;
        } 


    return CollisionSide::None;
}

    ~Objeto(){}
};




