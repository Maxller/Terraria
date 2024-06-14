#pragma once
#include <SFML/Graphics.hpp>
#include <Objeto.hpp>
#include <string>


class Bloque : public Objeto
{
private:
    sf::Sprite *sprite;
public:
    Bloque(std::string ruta){
        InicializarObjeto(1, 1, 15, 15, sf::Vector2f(0, 0));
        if (!cargarTexturas(ruta)){ /*Ah ocurrido un Error*/}
        sprite = getSpriteptr();
    }
    Bloque(std::string ruta, sf::Vector2f position){
        InicializarObjeto(1, 1, 15, 15, position);
        if (!cargarTexturas(ruta)){ /*Ah ocurrido un Error*/}
        sprite = getSpriteptr();
    }
    void updateFrame(int left, int top) override
    {
       //do nothing
    }
    ~Bloque() {delete sprite;}
};