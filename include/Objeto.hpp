#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class CollisionSide {
    None,
    Top,
    Bottom,
    Left,
    Right
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
    sf::Sprite* getSpriteptr(){
        return &sprite;
    }
    void InicializarObjeto (int currentFrame ,int numFrames, int frameWidth, int frameHeight, sf::Vector2f position){
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

    sf::FloatRect getBounds() {
        return hitBox.getGlobalBounds();
    }

    void setPopsicion(int deltaX, int deltaY){
        sf::Vector2f newPosition(deltaX, deltaY);
        position = newPosition;
        hitBox.setPosition(position);
        this->sprite.setPosition(newPosition); 
    }

    void deltaPopsicion(int deltaX, int deltaY){
        sf::Vector2f deltaPosition(deltaX, deltaY); 
        position += deltaPosition;
        hitBox.setPosition(position);
        this->sprite.setPosition(position); 
    }
    
    sf::Sprite getSprite(){
        return this -> sprite;
    }

// Función para detectar colisiones y el lado de la colisión
    CollisionSide checkCollisionSide(Objeto& obj) {
    sf::FloatRect bounds1 = this -> getBounds();
    sf::FloatRect bounds2 = obj.getBounds();

    float deltaX = bounds1.left + bounds1.width / 2 - (bounds2.left + bounds2.width / 2);
    float deltaY = bounds1.top + bounds1.height / 2 - (bounds2.top + bounds2.height / 2);

    float intersectX = std::abs(deltaX) - (bounds1.width / 2 + bounds2.width / 2);
    float intersectY = std::abs(deltaY) - (bounds1.height / 2 + bounds2.height / 2);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                return CollisionSide::Left;
            } else {
                return CollisionSide::Right;
            }
        } else {
            if (deltaY > 0.0f) {
                return CollisionSide::Top;
            } else {
                return CollisionSide::Bottom;
            }
        }
    }

    return CollisionSide::None;
}

    ~Objeto(){}
};




