#pragma once
#include <SFML/Graphics.hpp>
#include <Objeto.hpp>
#include <string>
#include <iostream>

class Bloque : public Objeto
{
private:
    sf::Sprite *sprite;
public:
    Bloque(std::string ruta){
        InicializarObjeto(1, 1, 16, 16, sf::Vector2f(0, 0));
        if (!cargarTexturas(ruta)){ /*Ah ocurrido un Error*/}
        sprite = getSpriteptr();
    }
    Bloque(std::string ruta, sf::Vector2f position){
        InicializarObjeto(1, 1, 16, 16, position);
        if (!cargarTexturas(ruta)){ /*Ah ocurrido un Error*/}
        sprite = getSpriteptr();
    }
    void updateFrame(int left, int top) override
    {
       std::cout<<"Hola, si existo, soy un bloque"<<std::endl;
    }
    ~Bloque() {delete sprite;}
};